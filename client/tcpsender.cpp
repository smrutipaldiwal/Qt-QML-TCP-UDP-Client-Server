#include "tcpsender.h"
#include "protocol.h"
#include <cstring>

// 127.0.0.1 means this computer. For two computers, put the server's LAN IP here.
static const QString SERVER_ADDRESS = QStringLiteral("127.0.0.1");

TcpSender::TcpSender(QObject *parent)
    : QObject(parent), m_socket(new QTcpSocket(this))
{
    // 'this' makes the socket a child of this worker. It moves with the worker
    // to the TCP thread and is deleted automatically with the worker.
    // Do not connect the socket here: the worker has not moved threads yet.
    connect(m_socket, &QTcpSocket::errorOccurred, this,
            [this](QAbstractSocket::SocketError) {
                emit errorOccurred("TCP: " + m_socket->errorString());
            });
}

bool TcpSender::ensureConnected()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState)
        return true; // Reuse the existing connection.

    m_socket->abort(); // Reset a failed/unfinished connection before retrying.
    m_socket->connectToHost(SERVER_ADDRESS, 4001);

    // Keep this beginner version close to your original code: wait at most
    // one second in the WORKER thread. The GUI thread remains responsive.
    if (!m_socket->waitForConnected(1000)) {
        emit errorOccurred("Cannot connect: " + m_socket->errorString());
        m_socket->abort();
        return false;
    }
    return true;
}

void TcpSender::sendAdd(int id, double lat, double longitude, const QString &comment)
{
    sendRecord(Protocol::CMD_ADD, id, lat, longitude, comment);
}

void TcpSender::sendUpdate(int id, double lat, double longitude, const QString &comment)
{
    sendRecord(Protocol::CMD_UPDATE, id, lat, longitude, comment);
}

void TcpSender::sendRecord(quint8 command, int id, double lat,
                           double longitude, const QString &comment)
{
    // ADD and UPDATE differ only in cmdID, so packet construction is shared.
    // ClientController validates the values before emitting its request signal.
    AddDataCmd cmd{}; // {} initializes every field (including the text) to zero.
    cmd.cmdID = command;
    cmd.UniqueID = static_cast<quint32>(id);
    cmd.lat = static_cast<float>(lat);
    cmd.longitude = static_cast<float>(longitude);

    const QByteArray text = comment.toUtf8();
    // Defensive size check also protects calls made outside ClientController.
    if (text.size() >= static_cast<int>(sizeof(cmd.comment))) {
        emit errorOccurred("Comment must fit in 49 UTF-8 bytes.");
        return;
    }
    std::memcpy(cmd.comment, text.constData(), text.size());
    // The remaining bytes are already zero, so the text is zero-terminated.

    // QByteArray copies the struct's bytes; it does not keep a pointer to cmd.
    sendPacket(QByteArray(reinterpret_cast<const char *>(&cmd), sizeof(cmd)));
}

void TcpSender::sendDelete(int id)
{
    DeleteDataCmd cmd{};
    cmd.cmdID = Protocol::CMD_DELETE;
    cmd.UniqueID = static_cast<quint32>(id);
    sendPacket(QByteArray(reinterpret_cast<const char *>(&cmd), sizeof(cmd)));
}

void TcpSender::sendPacket(const QByteArray &packet)
{
    if (!ensureConnected())
        return;

    // write() queues bytes for TCP. It does NOT mean the server accepted them.
    if (m_socket->write(packet) != packet.size()) {
        emit errorOccurred("Could not queue the complete TCP command.");
        m_socket->abort(); // Do not continue a stream containing a partial command.
    }
    // No flush() needed: Qt sends queued bytes when its event loop runs again.
}

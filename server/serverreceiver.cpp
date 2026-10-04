#include "serverreceiver.h"
#include "protocol.h" // Needed for command IDs and packet sizes (missing originally).
#include <QDebug>

ServerReceiver::ServerReceiver(QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this))
{
    connect(m_server, &QTcpServer::newConnection,
            this, &ServerReceiver::onNewConnection);
}

void ServerReceiver::start()
{
    // The worker and its child server have moved to the receiver thread by now.
    if (!m_server->listen(QHostAddress::AnyIPv4, 4001)) {
        qCritical() << "TCP listen failed:" << m_server->errorString();
        emit listenFailed();
        return;
    }
    qInfo() << "Listening on TCP 4001";
}

void ServerReceiver::onNewConnection()
{
    // Several clients may have connected before this slot gets a turn to run.
    while (m_server->hasPendingConnections()) {
        QTcpSocket *socket = m_server->nextPendingConnection();
        m_buffers.insert(socket, QByteArray());
        connect(socket, &QTcpSocket::readyRead, this, &ServerReceiver::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &ServerReceiver::onDisconnected);
        qInfo() << "Client connected:" << socket->peerAddress().toString();
    }
}

void ServerReceiver::onReadyRead()
{
    // sender() identifies which client's socket emitted readyRead.
    // qobject_cast safely checks/converts that QObject to a QTcpSocket pointer.
    auto *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;

    QByteArray &buffer = m_buffers[socket]; // & edits the stored buffer, not a copy.
    buffer.append(socket->readAll());

    // TCP does NOT preserve message boundaries. This loop extracts every
    // complete command and leaves any incomplete final command for next time.
    while (!buffer.isEmpty()) {
        const quint8 id = static_cast<quint8>(buffer.at(0));
        int size = 0;
        if (id == Protocol::CMD_ADD || id == Protocol::CMD_UPDATE)
            size = sizeof(AddDataCmd);
        else if (id == Protocol::CMD_DELETE)
            size = sizeof(DeleteDataCmd);
        else {
            // No length header exists for an unknown command, so we cannot
            // safely locate the next packet. Close only this client's connection.
            qWarning() << "Unknown command ID:" << id;
            socket->abort();
            return; // abort() may emit disconnected and erase this buffer.
        }

        if (buffer.size() < size)
            return; // Not enough bytes yet; Qt calls us again when more arrive.

        const QByteArray packet = buffer.left(size);
        buffer.remove(0, size);
        emit commandReceived(packet); // Queued delivery to the UDP sender thread.
    }
}

void ServerReceiver::onDisconnected()
{
    auto *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;
    m_buffers.remove(socket);
    socket->deleteLater(); // Delete safely after the current event is handled.
    qInfo() << "Client disconnected.";
}

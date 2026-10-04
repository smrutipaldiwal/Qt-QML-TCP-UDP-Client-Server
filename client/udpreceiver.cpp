#include "udpreceiver.h"
#include "protocol.h"
#include <QNetworkDatagram>
#include <cstring>

UdpReceiver::UdpReceiver(QObject *parent)
    : QObject(parent), m_socket(new QUdpSocket(this))
{
    connect(m_socket, &QUdpSocket::readyRead,
            this, &UdpReceiver::readPendingDatagrams);
}

void UdpReceiver::start()
{
    // Sharing allows multiple local clients to listen, subject to OS rules.
    if (!m_socket->bind(QHostAddress::AnyIPv4, 4002,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        emit errorOccurred("UDP bind failed: " + m_socket->errorString());
    }
}

void UdpReceiver::readPendingDatagrams()
{
    // readyRead may represent SEVERAL waiting messages. Drain all of them.
    // This loop stops when the queue is empty; it does not wait for new data.
    while (m_socket->hasPendingDatagrams()) {
        const QNetworkDatagram incoming = m_socket->receiveDatagram();
        if (!incoming.isValid()) {
            emit errorOccurred("UDP read failed: " + m_socket->errorString());
            break;
        }
        const QByteArray data = incoming.data();
        if (data.isEmpty())
            continue; // Ignore this message and check the next one.

        const quint8 id = static_cast<quint8>(data.at(0));
        if (id == Protocol::CMD_ADD || id == Protocol::CMD_UPDATE) {
            if (data.size() != static_cast<int>(sizeof(AddDataResp)))
                continue; // Never copy an incomplete or oversized packet.

            AddDataResp response{};
            std::memcpy(&response, data.constData(), sizeof(response));
            // Read only within the 50-byte field, even if a packet has no '\0'.
            const QByteArray text(response.comment, sizeof(response.comment));
            const auto end = text.indexOf('\0');
            const QString comment = QString::fromUtf8(end < 0 ? text : text.left(end));
            emit addResponseReceived(response.respID, response.Ack,
                                     response.UniqueID, response.lat,
                                     response.longitude, comment);
        } else if (id == Protocol::CMD_DELETE) {
            if (data.size() != static_cast<int>(sizeof(DeleteDataResp)))
                continue;

            DeleteDataResp response{};
            std::memcpy(&response, data.constData(), sizeof(response));
            emit deleteResponseReceived(response.respID, response.Ack, response.UniqueID);
        }
        // Unknown response IDs are ignored: UDP has separate message boundaries.
    }
}

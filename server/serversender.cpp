#include "serversender.h"
#include <QDebug>
#include <cmath>
#include <cstring>

ServerSender::ServerSender(QObject *parent)
    : QObject(parent), m_udpSocket(new QUdpSocket(this))
{
}

void ServerSender::processCommand(const QByteArray &data)
{
    if (data.isEmpty())
        return;

    const quint8 id = static_cast<quint8>(data.at(0));
    if (id == Protocol::CMD_ADD || id == Protocol::CMD_UPDATE) {
        if (data.size() != static_cast<int>(sizeof(AddDataCmd)))
            return;

        AddDataCmd cmd{};
        // Copy bytes into a real struct; avoid casting the byte buffer to a struct*.
        std::memcpy(&cmd, data.constData(), sizeof(cmd));
        const bool exists = m_records.contains(cmd.UniqueID);
        const bool valid = std::isfinite(cmd.lat) && std::isfinite(cmd.longitude)
                           && std::memchr(cmd.comment, '\0', sizeof(cmd.comment));
        // ADD must use a new ID; UPDATE must use an existing ID.
        const bool allowed = valid && (id == Protocol::CMD_ADD ? !exists : exists);
        if (allowed)
            m_records.insert(cmd.UniqueID, cmd);

        // Build one response regardless of success/failure; only ACK differs.
        AddDataResp response{};
        response.respID = id;
        response.Ack = allowed ? Protocol::ACK_SUCCESS : Protocol::ACK_FAIL;
        response.UniqueID = cmd.UniqueID;
        response.lat = cmd.lat;
        response.longitude = cmd.longitude;
        std::memcpy(response.comment, cmd.comment, sizeof(response.comment));
        broadcast(QByteArray(reinterpret_cast<const char *>(&response), sizeof(response)));
        qInfo() << (id == Protocol::CMD_ADD ? "ADD" : "UPDATE")
                << cmd.UniqueID << (allowed ? "accepted" : "rejected");
    } else if (id == Protocol::CMD_DELETE) {
        if (data.size() != static_cast<int>(sizeof(DeleteDataCmd)))
            return;

        DeleteDataCmd cmd{};
        std::memcpy(&cmd, data.constData(), sizeof(cmd));
        // remove() returns the number removed: 0 means the ID was not found.
        const bool removed = m_records.remove(cmd.UniqueID) > 0;
        DeleteDataResp response{};
        response.respID = id;
        response.Ack = removed ? Protocol::ACK_SUCCESS : Protocol::ACK_FAIL;
        response.UniqueID = cmd.UniqueID;
        broadcast(QByteArray(reinterpret_cast<const char *>(&response), sizeof(response)));
        qInfo() << "DELETE" << cmd.UniqueID << (removed ? "accepted" : "rejected");
    }
}

void ServerSender::broadcast(const QByteArray &packet)
{
    // Broadcast to listening clients on the local network, as the task requires.
    // A successful write is not a guarantee that every client receives the UDP.
    if (m_udpSocket->writeDatagram(packet, QHostAddress::Broadcast,
                                   4002) != packet.size()) {
        qWarning() << "UDP broadcast failed:" << m_udpSocket->errorString();
    }
}

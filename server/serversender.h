#ifndef SERVERSENDER_H
#define SERVERSENDER_H

#include <QObject>
#include <QUdpSocket>
#include <QHash>
#include "protocol.h"

// Only this worker touches the server's records, so no mutex is needed here.
// The TCP worker sends it copied commands through a queued connection.
class ServerSender : public QObject
{
    Q_OBJECT
public:
    explicit ServerSender(QObject *parent = nullptr);

public slots:
    void processCommand(const QByteArray &data);

private:
    void broadcast(const QByteArray &packet);
    QUdpSocket *m_udpSocket;
    QHash<quint32, AddDataCmd> m_records; // ID -> latest accepted record.
};
#endif

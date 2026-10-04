#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QObject>
#include <QTcpSocket>

// Worker object: its slots run in the TCP thread when called through
// the queued signal connections in main.cpp.
class TcpSender : public QObject
{
    Q_OBJECT // Enables Qt's signals, slots and runtime object information.
public:
    explicit TcpSender(QObject *parent = nullptr);

public slots:
    void sendAdd(int uniqueID, double lat, double longitude, const QString &comment);
    void sendUpdate(int uniqueID, double lat, double longitude, const QString &comment);
    void sendDelete(int uniqueID);

signals:
    void errorOccurred(const QString &message);

private:
    bool ensureConnected();
    void sendRecord(quint8 command, int uniqueID, double lat,
                    double longitude, const QString &comment);
    void sendPacket(const QByteArray &packet);
    QTcpSocket *m_socket;
};
#endif

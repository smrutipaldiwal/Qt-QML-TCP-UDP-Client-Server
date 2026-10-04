#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>

// Receives broadcasts in the UDP thread; never changes the GUI directly.
class UdpReceiver : public QObject
{
    Q_OBJECT
public:
    explicit UdpReceiver(QObject *parent = nullptr);

public slots:
    void start(); // Bind port 4002 after the worker thread starts.

signals:
    void errorOccurred(const QString &message);
    void addResponseReceived(quint8 respID, quint8 ack, quint32 uniqueID,
                             float lat, float longitude, const QString &comment);
    void deleteResponseReceived(quint8 respID, quint8 ack, quint32 uniqueID);

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *m_socket;
};
#endif

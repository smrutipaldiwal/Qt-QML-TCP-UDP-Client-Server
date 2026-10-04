#ifndef SERVERRECEIVER_H
#define SERVERRECEIVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include <QByteArray>

// TCP worker: accepts clients and splits each byte stream into commands.
class ServerReceiver : public QObject
{
    Q_OBJECT
public:
    explicit ServerReceiver(QObject *parent = nullptr);

public slots:
    void start();

signals:
    void commandReceived(const QByteArray &data);
    void listenFailed();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpServer *m_server;
    // Each client needs its OWN buffer so their bytes never get mixed together.
    QHash<QTcpSocket *, QByteArray> m_buffers;
};
#endif

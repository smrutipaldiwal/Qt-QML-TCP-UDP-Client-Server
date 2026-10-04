#include <QCoreApplication>
#include <QThread>
#include "serverreceiver.h"
#include "serversender.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv); // Console event loop; no GUI needed.
    QThread receiverThread;
    QThread senderThread;
    auto *receiver = new ServerReceiver;
    auto *sender = new ServerSender;
    receiver->moveToThread(&receiverThread);
    sender->moveToThread(&senderThread);

    QObject::connect(&receiverThread, &QThread::finished, receiver, &QObject::deleteLater);
    QObject::connect(&senderThread, &QThread::finished, sender, &QObject::deleteLater);
    QObject::connect(&receiverThread, &QThread::started, receiver, &ServerReceiver::start);
    QObject::connect(receiver, &ServerReceiver::commandReceived,
                     sender, &ServerSender::processCommand, Qt::QueuedConnection);
    QObject::connect(receiver, &ServerReceiver::listenFailed, &app,
                     [] { QCoreApplication::exit(1); }, Qt::QueuedConnection);

    senderThread.start();
    receiverThread.start();
    const int result = app.exec();

    // Runs on normal event-loop exit, including a failed listen(). Force-stopping
    // the process in Qt Creator / with Ctrl+C may bypass C++ cleanup entirely.
    receiverThread.quit();
    senderThread.quit();
    receiverThread.wait();
    senderThread.wait();
    return result;
}

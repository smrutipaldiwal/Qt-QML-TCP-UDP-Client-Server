#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include "clientcontroller.h"
#include "tcpsender.h"
#include "udpreceiver.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    ClientController controller; // Stays in the GUI thread with the QML engine.
    QThread tcpThread;
    QThread udpThread;

    // Workers have no parent, which allows moveToThread(). Their child sockets
    // move with them. A QThread controls a thread; the worker does the work.
    auto *tcpSender = new TcpSender;
    auto *udpReceiver = new UdpReceiver;
    tcpSender->moveToThread(&tcpThread);
    udpReceiver->moveToThread(&udpThread);

    // Delete workers in their own threads when those threads finish.
    // QObject also deletes each worker's child socket, closing the socket.
    QObject::connect(&tcpThread, &QThread::finished, tcpSender, &QObject::deleteLater);
    QObject::connect(&udpThread, &QThread::finished, udpReceiver, &QObject::deleteLater);

    // QueuedConnection posts a call to the RECEIVER's event loop. The GUI does
    // not run the socket operation itself and does not wait for it to finish.
    QObject::connect(&controller, &ClientController::sendAddRequest,
                     tcpSender, &TcpSender::sendAdd, Qt::QueuedConnection);
    QObject::connect(&controller, &ClientController::sendUpdateRequest,
                     tcpSender, &TcpSender::sendUpdate, Qt::QueuedConnection);
    QObject::connect(&controller, &ClientController::sendDeleteRequest,
                     tcpSender, &TcpSender::sendDelete, Qt::QueuedConnection);
    QObject::connect(udpReceiver, &UdpReceiver::addResponseReceived,
                     &controller, &ClientController::onAddResponse, Qt::QueuedConnection);
    QObject::connect(udpReceiver, &UdpReceiver::deleteResponseReceived,
                     &controller, &ClientController::onDeleteResponse, Qt::QueuedConnection);
    QObject::connect(tcpSender, &TcpSender::errorOccurred,
                     &controller, &ClientController::setStatus, Qt::QueuedConnection);
    QObject::connect(udpReceiver, &UdpReceiver::errorOccurred,
                     &controller, &ClientController::setStatus, Qt::QueuedConnection);

    udpThread.start();
    tcpThread.start();
    // At startup ONLY, wait for the UDP bind attempt before exposing the GUI.
    // The receiver runs start() in its own thread; main waits for it to return.
    // This avoids sending a command before the client has tried to listen.
    QMetaObject::invokeMethod(udpReceiver, "start", Qt::BlockingQueuedConnection);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("clientController", &controller);
    // engine.load(QUrl(QStringLiteral("C:/Users/smrut/Documents/client/Main.qml")));
    engine.load(QUrl::fromLocalFile(
        QStringLiteral("C:/Users/smrut/Documents/client/Main.qml")));

    // exec() processes clicks, queued signals and other events until exit.
    // If QML loading failed, skip exec(), but STILL clean up both threads.
    const int result = engine.rootObjects().isEmpty() ? -1 : app.exec();

    tcpThread.quit(); // Ask the worker event loops to stop.
    udpThread.quit();
    tcpThread.wait(); // Wait until they stop BEFORE destroying QThread objects.
    udpThread.wait();
    return result;
}

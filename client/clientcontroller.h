#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>

// The controller belongs to the MAIN/GUI thread. QML reads its properties
// and calls its public invokable functions. Workers communicate via signals.
class ClientController : public QObject
{
    Q_OBJECT
    // READ names the getter; NOTIFY tells QML when to refresh its display.
    Q_PROPERTY(QVariantList records READ records NOTIFY recordsChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)

public:
    explicit ClientController(QObject *parent = nullptr);
    QVariantList records() const;
    QString status() const;

    // Q_INVOKABLE exposes ordinary C++ functions to QML.
    // These signatures and the record field names match your original files.
    Q_INVOKABLE void addRecord(int uniqueID, double lat, double longitude,
                               const QString &comment);
    Q_INVOKABLE void updateRecord(int uniqueID, double lat, double longitude,
                                  const QString &comment);
    Q_INVOKABLE void deleteRecord(int uniqueID);

signals:
    void recordsChanged();
    void statusChanged();
    void sendAddRequest(int uniqueID, double lat, double longitude, const QString &comment);
    void sendUpdateRequest(int uniqueID, double lat, double longitude, const QString &comment);
    void sendDeleteRequest(int uniqueID);

public slots:
    void onAddResponse(quint8 respID, quint8 ack, quint32 uniqueID,
                       float lat, float longitude, const QString &comment);
    void onDeleteResponse(quint8 respID, quint8 ack, quint32 uniqueID);
    void setStatus(const QString &message);

private:
    bool validRecord(int id, double lat, double longitude, const QString &comment);
    int findRecord(quint32 uniqueID) const;
    QVariantList m_records; // A list of maps: uniqueID, lat, longitude, comment.
    QString m_status;
};
#endif

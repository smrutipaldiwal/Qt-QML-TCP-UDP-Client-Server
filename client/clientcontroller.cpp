#include "clientcontroller.h"
#include "protocol.h"
#include <QDebug>
#include <cmath>
#include <limits>

ClientController::ClientController(QObject *parent) : QObject(parent) {}
QVariantList ClientController::records() const { return m_records; }
QString ClientController::status() const { return m_status; }

void ClientController::setStatus(const QString &message)
{
    qInfo().noquote() << message; // Visible in Qt Creator's Application Output.
    if (m_status == message)
        return;
    m_status = message;
    emit statusChanged(); // Optional QML status label refreshes here.
}

bool ClientController::validRecord(int id, double lat, double longitude,
                                   const QString &comment)
{
    if (id < 0) {
        setStatus("ID cannot be negative.");
        return false;
    }
    // The form uses doubles, but the packet stores smaller 32-bit floats.
    const double limit = std::numeric_limits<float>::max();
    if (!std::isfinite(lat) || !std::isfinite(longitude) ||
        std::abs(lat) > limit || std::abs(longitude) > limit) {
        setStatus("Coordinates must be finite numbers that fit in a float.");
        return false;
    }
    // UTF-8 characters may use several bytes. Reject rather than cut one in half.
    if (comment.toUtf8().size() > 49 || comment.contains(QChar(0))) {
        setStatus("Comment must fit in 49 UTF-8 bytes and contain no zero character.");
        return false;
    }
    return true;
}

void ClientController::addRecord(int id, double lat, double longitude,
                                 const QString &comment)
{
    if (!validRecord(id, lat, longitude, comment))
        return;
    setStatus("ADD requested; waiting for server acknowledgement.");
    emit sendAddRequest(id, lat, longitude, comment);
    // Do not add locally here: the task requires a successful ACK first.
}

void ClientController::updateRecord(int id, double lat, double longitude,
                                    const QString &comment)
{
    if (!validRecord(id, lat, longitude, comment))
        return;
    setStatus("UPDATE requested; waiting for server acknowledgement.");
    emit sendUpdateRequest(id, lat, longitude, comment);
}

void ClientController::deleteRecord(int id)
{
    if (id < 0) {
        setStatus("ID cannot be negative.");
        return;
    }
    setStatus("DELETE requested; waiting for server acknowledgement.");
    emit sendDeleteRequest(id);
}

int ClientController::findRecord(quint32 id) const
{
    // Search the list by ID, not by screen position (positions change on deletion).
    for (int i = 0; i < m_records.size(); ++i) {
        if (m_records.at(i).toMap().value("uniqueID").toUInt() == id)
            return i;
    }
    return -1; // -1 means no matching record was found.
}

void ClientController::onAddResponse(quint8 respID, quint8 ack, quint32 id,
                                     float lat, float longitude, const QString &comment)
{
    const QString action = respID == Protocol::CMD_ADD ? "ADD" : "UPDATE";
    if (ack != Protocol::ACK_SUCCESS) {
        setStatus(QString("%1 rejected for ID %2.").arg(action).arg(id));
        return; // A rejected command must not change the displayed list.
    }

    // Build the map ONCE, then replace a matching entry or append a new one.
    const QVariantMap item{{"uniqueID", id}, {"lat", lat},
                           {"longitude", longitude}, {"comment", comment}};
    const int index = findRecord(id);
    if (index < 0)
        m_records.append(item);
    else
        m_records[index] = item;

    emit recordsChanged();
    setStatus(QString("%1 acknowledged for ID %2.").arg(action).arg(id));
}

void ClientController::onDeleteResponse(quint8 respID, quint8 ack, quint32 id)
{
    Q_UNUSED(respID); // Kept in the interface; this slot only handles DELETE.
    if (ack != Protocol::ACK_SUCCESS) {
        setStatus(QString("DELETE rejected for ID %1.").arg(id));
        return;
    }
    const int index = findRecord(id);
    if (index >= 0) {
        m_records.removeAt(index);
        emit recordsChanged();
    }
    setStatus(QString("DELETE acknowledged for ID %1.").arg(id));
}

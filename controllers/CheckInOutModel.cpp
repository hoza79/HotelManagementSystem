#include "CheckInOutModel.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

CheckInOutModel::CheckInOutModel(QObject *parent)
    : FilterableListModel(parent)
{
}

int CheckInOutModel::rowCount(const QModelIndex &) const
{
    return m_filteredEntries.size();
}

QVariant CheckInOutModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_filteredEntries.size())
        return QVariant();

    const auto &entry = m_filteredEntries.at(index.row());
    switch (role) {
    case GuestNameRole:
        return entry.guestName;
    case RoomRole:
        return entry.room;
    case ActionRole:
        return entry.action;
    case TimestampRole:
        return entry.timestamp;
    case HighlightRole:
        return entry.highlight;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CheckInOutModel::roleNames() const
{
    return {
        { GuestNameRole, "guestName" },
        { RoomRole, "room" },
        { ActionRole, "action" },
        { TimestampRole, "timestamp" },
        { HighlightRole, "highlight" }
    };
}

void CheckInOutModel::fetchCheckInOuts()
{
    QUrl url("http://127.0.0.1:8000/api/checkinout/");
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onReplyFinished(reply);
    });
}

void CheckInOutModel::onReplyFinished(QNetworkReply *reply)
{
    QByteArray jsonData = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray())
        return;

    m_entries.clear();
    m_filteredEntries.clear();

    QJsonArray array = doc.array();
    for (const auto &item : array) {
        QJsonObject obj = item.toObject();

        CheckInOut entry;
        QJsonObject resObj = obj["reservation"].toObject();
        entry.guestName = resObj["guest_name"].toString();
        entry.room = resObj["room_number"].toString();
        entry.action = obj["action"].toString();
        entry.timestamp = obj["timestamp"].toString();

        m_entries.append(entry);
    }

    applyFilter();
}

void CheckInOutModel::addCheckInOut(int reservationId, const QString &action, int roomId)
{
    QUrl url("http://127.0.0.1:8000/api/checkinout/create/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["reservation_id"] = reservationId;
    obj["action"] = action;

    if (action == "IN" && roomId != -1) {
        obj["room_id"] = roomId;
    }

    QNetworkReply *reply = m_manager.post(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();

        fetchCheckInOuts();

        emit refreshReservationsRequested();
        emit refreshGuestsRequested();
        emit refreshRoomsRequested();
        emit checkInOutSaved();
    });
}

void CheckInOutModel::applyFilter()
{
    m_filteredEntries.clear();

    if (m_searchText.isEmpty()) {
        m_filteredEntries = m_entries;
        for (auto &entry : m_filteredEntries) {
            entry.highlight = false;
        }
    } else {
        for (const auto &entry : m_entries) {
            bool match =
                entry.guestName.contains(m_searchText, Qt::CaseInsensitive) ||
                entry.room.contains(m_searchText, Qt::CaseInsensitive) ||
                entry.action.contains(m_searchText, Qt::CaseInsensitive);

            if (match) {
                CheckInOut filteredEntry = entry;
                filteredEntry.highlight = true;
                m_filteredEntries.append(filteredEntry);
            }
        }
    }
}

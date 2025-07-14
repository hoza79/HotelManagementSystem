#include "RoomModel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

RoomModel::RoomModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int RoomModel::rowCount(const QModelIndex &) const
{
    return m_rooms.size();
}

QVariant RoomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_rooms.size())
        return QVariant();

    const auto &room = m_rooms.at(index.row());

    switch (role) {
    case RoomNumberRole:
        return room.roomNumber;
    case StatusRole:
        return room.status;
    case RoomTypeRole:
        return room.roomType;
    case IdRole:
        return room.id;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> RoomModel::roleNames() const
{
    return {
        { RoomNumberRole, "roomNumber" },
        { StatusRole, "status" },
        { RoomTypeRole, "roomType" },
        { IdRole, "id" }
    };
}

void RoomModel::fetchRooms()
{
    setSearchText("");
}

void RoomModel::setSearchText(const QString &text)
{
    QUrl url("http://127.0.0.1:8000/api/rooms/");
    if (!text.isEmpty()) {
        url.setQuery(QString("search=%1").arg(QUrl::toPercentEncoding(text)));
    }
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onReplyFinished(reply);
    });
}

void RoomModel::onReplyFinished(QNetworkReply *reply)
{
    QByteArray jsonData = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray())
        return;

    beginResetModel();
    m_rooms.clear();

    QJsonArray array = doc.array();
    for (const auto &item : array) {
        QJsonObject obj = item.toObject();
        Room room;
        room.id = obj["id"].toInt();
        room.roomNumber = obj["room_number"].toString();
        room.status = obj["status"].toString();
        room.roomType = obj["room_type"].toString();
        m_rooms.append(room);
    }

    endResetModel();
    emit roomNumbersChanged();
}

QStringList RoomModel::roomNumbers() const
{
    QStringList list;
    for (const auto &room : m_rooms) {
        list << room.roomNumber;
    }
    return list;
}

QStringList RoomModel::vacantRoomNumbers() const
{
    QStringList list;
    for (const auto &room : m_rooms) {
        if (room.status == "Vacant") {
            list << room.roomNumber;
        }
    }
    return list;
}

int RoomModel::roomIdForNumber(const QString &roomNumber) const
{
    for (const auto &room : m_rooms) {
        if (room.roomNumber == roomNumber)
            return room.id;
    }
    return -1;
}

void RoomModel::updateRoomStatus(int roomId, const QString &newStatus)
{
    QUrl url(QString("http://127.0.0.1:8000/api/rooms/%1/update/").arg(roomId));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["status"] = newStatus;

    QNetworkReply *reply = m_manager.put(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();
        fetchRooms();
    });
}

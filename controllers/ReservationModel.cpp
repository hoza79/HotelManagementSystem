#include "ReservationModel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDateTime>

ReservationModel::ReservationModel(QObject *parent)
    : FilterableListModel(parent)
{
}

int ReservationModel::rowCount(const QModelIndex &) const
{
    return m_filteredReservations.size();
}

QVariant ReservationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_filteredReservations.size())
        return QVariant();

    const auto &res = m_filteredReservations.at(index.row());

    switch (role) {
    case IdRole:
        return res.id;
    case GuestNameRole:
        return res.guestName;
    case CheckInRole:
        return res.checkIn;
    case CheckOutRole:
        return res.checkOut;
    case RoomRole:
        return res.room;
    case ReservationStatusRole:
        return res.reservationStatus;
    case HighlightRole:
        return res.highlight;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReservationModel::roleNames() const
{
    return {
        { IdRole, "id" },
        { GuestNameRole, "guestName" },
        { CheckInRole, "checkIn" },
        { CheckOutRole, "checkOut" },
        { RoomRole, "room" },
        { ReservationStatusRole, "reservationStatus" },
        { HighlightRole, "highlight" }
    };
}

void ReservationModel::fetchReservations()
{
    QUrl url("http://127.0.0.1:8000/api/reservations/");
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        onReplyFinished(reply);
    });
}

void ReservationModel::onReplyFinished(QNetworkReply *reply)
{
    QByteArray jsonData = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray())
        return;

    beginResetModel();

    m_reservations.clear();
    m_filteredReservations.clear();

    QJsonArray array = doc.array();
    for (const auto &item : array) {
        QJsonObject obj = item.toObject();
        Reservation res;
        res.id = obj["id"].toInt();
        res.guestName = obj["guest_name"].toString();

        QString rawCheckIn = obj["check_in"].toString();
        QString rawCheckOut = obj["check_out"].toString();

        QDateTime dtCheckIn = QDateTime::fromString(rawCheckIn, Qt::ISODate);
        QDateTime dtCheckOut = QDateTime::fromString(rawCheckOut, Qt::ISODate);

        res.checkIn = dtCheckIn.toLocalTime().toString("yyyy-MM-dd HH:mm:ss");
        res.checkOut = dtCheckOut.toLocalTime().toString("yyyy-MM-dd HH:mm:ss");

        res.room = obj["room_number"].toString();
        res.reservationStatus = obj["reservation_status"].toString();

        m_reservations.append(res);
    }

    applyFilter();

    endResetModel();

    emit fullNamesChanged();
}

QStringList ReservationModel::fullNames() const
{
    QStringList names;
    for (const auto &res : m_filteredReservations)
        names << res.guestName;
    return names;
}

int ReservationModel::reservationIdAt(int index) const
{
    if (index >= 0 && index < m_filteredReservations.size())
        return m_filteredReservations[index].id;
    return -1;
}

void ReservationModel::addReservation(const QString &guestName,
                                      const QString &guestPhone,
                                      const QString &checkIn,
                                      const QString &checkOut,
                                      const QString &roomType,
                                      const QString &status)
{
    QUrl url("http://127.0.0.1:8000/api/reservations/create/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["guest_name"] = guestName;
    obj["guest_phone"] = guestPhone;
    obj["check_in"] = checkIn;
    obj["check_out"] = checkOut;
    obj["room_type"] = roomType;
    obj["status"] = status;

    QNetworkReply *reply = m_manager.post(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();
        fetchReservations();
        emit refreshCheckInOutsRequested();
        emit reservationSaved();
    });
}

void ReservationModel::updateReservationStatus(int reservationId, const QString &newStatus)
{
    QUrl url(QString("http://127.0.0.1:8000/api/reservations/%1/update/").arg(reservationId));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["reservation_status"] = newStatus;

    QNetworkReply *reply = m_manager.put(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();
        fetchReservations();
    });
}

QVariantMap ReservationModel::get(int row) const
{
    QVariantMap map;

    if (row < 0 || row >= m_filteredReservations.size())
        return map;

    const auto &res = m_filteredReservations.at(row);

    map["id"] = res.id;
    map["guestName"] = res.guestName;
    map["checkIn"] = res.checkIn;
    map["checkOut"] = res.checkOut;
    map["room"] = res.room;
    map["reservationStatus"] = res.reservationStatus;
    map["highlight"] = res.highlight;

    return map;
}

void ReservationModel::applyFilter()
{
    m_filteredReservations.clear();

    if (m_searchText.isEmpty()) {
        m_filteredReservations = m_reservations;
        for (auto &res : m_filteredReservations) {
            res.highlight = false;
        }
    } else {
        for (const auto &res : m_reservations) {
            bool match =
                res.guestName.contains(m_searchText, Qt::CaseInsensitive) ||
                res.room.contains(m_searchText, Qt::CaseInsensitive) ||
                res.reservationStatus.contains(m_searchText, Qt::CaseInsensitive);

            if (match) {
                Reservation filteredRes = res;
                filteredRes.highlight = true;
                m_filteredReservations.append(filteredRes);
            }
        }
    }
}

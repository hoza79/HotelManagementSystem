#include "GuestModel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>

GuestModel::GuestModel(QObject *parent)
    : FilterableListModel(parent)
{
}

int GuestModel::rowCount(const QModelIndex &) const
{
    return m_filteredGuests.size();
}

QVariant GuestModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_filteredGuests.size())
        return QVariant();

    const auto &guest = m_filteredGuests.at(index.row());

    switch (role) {
    case GuestNameRole:
        return guest.guestName;
    case RoomNumberRole:
        return guest.roomNumber;
    case PhoneNumberRole:
        return guest.phoneNumber;
    case HighlightRole:
        return guest.highlight;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> GuestModel::roleNames() const
{
    return {
        { GuestNameRole, "guestName" },
        { RoomNumberRole, "roomNumber" },
        { PhoneNumberRole, "phoneNumber" },
        { HighlightRole, "highlight" }
    };
}

void GuestModel::fetchGuests()
{
    QUrl url("http://127.0.0.1:8000/api/guests/");
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager.get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        onReplyFinished(reply);
    });
}

void GuestModel::onReplyFinished(QNetworkReply *reply)
{
    QByteArray jsonData = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray())
        return;

    m_guests.clear();
    m_filteredGuests.clear();
    m_guestIds.clear();

    QJsonArray array = doc.array();
    for (const auto &item : array) {
        QJsonObject obj = item.toObject();
        Guest guest;
        guest.guestName = obj["full_name"].toString();
        guest.phoneNumber = obj["phone_number"].toString();
        guest.roomNumber = obj["room_number"].toString();
        guest.highlight = false;
        m_guests.append(guest);

        m_guestIds.append(obj["id"].toInt());
    }

    applyFilter();
    emit fullNamesChanged();
    emit modelReset();
}

QStringList GuestModel::fullNames() const
{
    QStringList names;
    for (const auto &guest : m_filteredGuests)
        names << guest.guestName;
    return names;
}

int GuestModel::guestIdAt(int index) const
{
    if (index >= 0 && index < m_guestIds.size())
        return m_guestIds[index];
    return -1;
}

void GuestModel::addGuest(const QString &fullName, const QString &phoneNumber, int roomId)
{
    QUrl url("http://127.0.0.1:8000/api/guests/create/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["full_name"] = fullName;
    obj["phone_number"] = phoneNumber;

    if (roomId != -1) {
        obj["room_id"] = roomId;
    }

    QNetworkReply *reply = m_manager.post(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();
        fetchGuests();
    });
}

void GuestModel::applyFilter()
{
    m_filteredGuests.clear();

    if (m_searchText.isEmpty()) {
        for (auto guest : m_guests) {
            guest.highlight = false;
            m_filteredGuests.append(guest);
        }
    } else {
        for (auto guest : m_guests) {
            bool match =
                guest.guestName.contains(m_searchText, Qt::CaseInsensitive) ||
                guest.phoneNumber.contains(m_searchText, Qt::CaseInsensitive) ||
                guest.roomNumber.contains(m_searchText, Qt::CaseInsensitive);
            if (match) {
                guest.highlight = true;
                m_filteredGuests.append(guest);
            }
        }
    }
}

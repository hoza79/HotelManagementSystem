#ifndef RESERVATIONMODEL_H
#define RESERVATIONMODEL_H

#include <QObject>
#include <QVariant>
#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "FilterableListModel.h"

struct Reservation {
    int id;
    QString guestName;
    QString checkIn;
    QString checkOut;
    QString room;
    QString reservationStatus;
    bool highlight = false;
};

class ReservationModel : public FilterableListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList fullNames READ fullNames NOTIFY fullNamesChanged)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        GuestNameRole,
        CheckInRole,
        CheckOutRole,
        RoomRole,
        ReservationStatusRole,
        HighlightRole
    };

    explicit ReservationModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void fetchReservations();
    Q_INVOKABLE void addReservation(const QString &guestName,
                                    const QString &guestPhone,
                                    const QString &checkIn,
                                    const QString &checkOut,
                                    const QString &roomType,
                                    const QString &status);
    Q_INVOKABLE int reservationIdAt(int index) const;
    Q_INVOKABLE void updateReservationStatus(int reservationId, const QString &newStatus);
    Q_INVOKABLE QVariantMap get(int row) const;

    QStringList fullNames() const;

signals:
    void fullNamesChanged();
    void refreshCheckInOutsRequested();
    void reservationSaved();

private slots:
    void onReplyFinished(QNetworkReply* reply);

protected:
    void applyFilter() override;

private:
    QList<Reservation> m_reservations;
    QList<Reservation> m_filteredReservations;
    QNetworkAccessManager m_manager;
};

#endif // RESERVATIONMODEL_H

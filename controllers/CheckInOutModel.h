#ifndef CHECKINOUTMODEL_H
#define CHECKINOUTMODEL_H

#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include "FilterableListModel.h"

struct CheckInOut {
    QString guestName;
    QString room;
    QString action;
    QString timestamp;
    bool highlight = false;
};

class CheckInOutModel : public FilterableListModel
{
    Q_OBJECT

public:
    enum Roles {
        GuestNameRole = Qt::UserRole + 1,
        RoomRole,
        ActionRole,
        TimestampRole,
        HighlightRole
    };

    explicit CheckInOutModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void fetchCheckInOuts();
    Q_INVOKABLE void addCheckInOut(int reservationId, const QString &action, int roomId);

signals:
    void refreshReservationsRequested();
    void refreshGuestsRequested();
    void refreshRoomsRequested();
    void checkInOutSaved();

private slots:
    void onReplyFinished(QNetworkReply *reply);

protected:
    void applyFilter() override;

private:
    QList<CheckInOut> m_entries;
    QList<CheckInOut> m_filteredEntries;
    QNetworkAccessManager m_manager;
};

#endif // CHECKINOUTMODEL_H

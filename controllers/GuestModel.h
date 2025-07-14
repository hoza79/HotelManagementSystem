#ifndef GUESTMODEL_H
#define GUESTMODEL_H

#include <QObject>
#include <QVariant>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "FilterableListModel.h"

struct Guest {
    QString guestName;
    QString roomNumber;
    QString phoneNumber;
    bool highlight = false;
};

class GuestModel : public FilterableListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList fullNames READ fullNames NOTIFY fullNamesChanged)

public:
    enum Roles {
        GuestNameRole = Qt::UserRole + 1,
        RoomNumberRole,
        PhoneNumberRole,
        HighlightRole
    };

    explicit GuestModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void fetchGuests();
    Q_INVOKABLE void addGuest(const QString &fullName, const QString &phoneNumber, int roomId);
    Q_INVOKABLE int guestIdAt(int index) const;

    QStringList fullNames() const;

signals:
    void fullNamesChanged();
    void modelReset();

private slots:
    void onReplyFinished(QNetworkReply* reply);

protected:
    void applyFilter() override;

private:
    QList<Guest> m_guests;
    QList<Guest> m_filteredGuests;
    QList<int> m_guestIds;
    QNetworkAccessManager m_manager;
};

#endif // GUESTMODEL_H

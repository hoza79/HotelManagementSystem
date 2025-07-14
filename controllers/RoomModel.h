#ifndef ROOMMODEL_H
#define ROOMMODEL_H

#include <QAbstractListModel>
#include <QNetworkAccessManager>

struct Room {
    int id;
    QString roomNumber;
    QString status;
    QString roomType;
};

class RoomModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList roomNumbers READ roomNumbers NOTIFY roomNumbersChanged)
    Q_PROPERTY(QStringList vacantRoomNumbers READ vacantRoomNumbers NOTIFY roomNumbersChanged)

public:
    enum Roles {
        RoomNumberRole = Qt::UserRole + 1,
        StatusRole,
        RoomTypeRole,
        IdRole
    };

    explicit RoomModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void fetchRooms();
    Q_INVOKABLE void setSearchText(const QString &text);
    Q_INVOKABLE int roomIdForNumber(const QString &roomNumber) const;
    Q_INVOKABLE void updateRoomStatus(int roomId, const QString &newStatus);

    QStringList roomNumbers() const;
    QStringList vacantRoomNumbers() const;

signals:
    void roomNumbersChanged();

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QList<Room> m_rooms;
    QNetworkAccessManager m_manager;
};

#endif // ROOMMODEL_H

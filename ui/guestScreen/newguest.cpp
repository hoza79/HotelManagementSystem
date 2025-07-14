#include "newguest.h"

NewGuest::NewGuest(QObject *parent)
    : QAbstractItemModel(parent)
{}

QVariant NewGuest::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex NewGuest::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex NewGuest::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int NewGuest::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int NewGuest::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant NewGuest::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

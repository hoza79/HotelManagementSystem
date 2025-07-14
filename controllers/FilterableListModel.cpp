#include "FilterableListModel.h"

FilterableListModel::FilterableListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void FilterableListModel::setSearchText(const QString &text)
{
    m_searchText = text.trimmed();
    emit layoutAboutToBeChanged();
    applyFilter();
    emit layoutChanged();
}

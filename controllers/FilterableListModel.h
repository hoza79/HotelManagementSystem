#ifndef FILTERABLELISTMODEL_H
#define FILTERABLELISTMODEL_H

#include <QAbstractListModel>

template<typename T>
void highlightMatches(QList<T>& items,
                      const QString& text,
                      std::function<bool(const T&, const QString&)> matches)
{
    for (auto& item : items)
    {
        item.highlight = matches(item, text);
    }
}

class FilterableListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FilterableListModel(QObject *parent = nullptr);

    Q_INVOKABLE void setSearchText(const QString &text);

protected:
    QString m_searchText;
    virtual void applyFilter() = 0;
};

#endif // FILTERABLELISTMODEL_H

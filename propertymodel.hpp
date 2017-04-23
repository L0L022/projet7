#ifndef PROPERTYMODEL_HPP
#define PROPERTYMODEL_HPP

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QSharedPointer>
#include <QJsonObject>
#include <QJsonArray>

class PropertyItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
    Q_PROPERTY(QVariantMap properties READ properties WRITE setProperties NOTIFY propertiesChanged)

public:
    typedef int Id;

    PropertyItem(const Id id = 0, QObject *parent = nullptr);

    Id id() const;
    const QVariantMap &properties() const;
    void setProperties(const QVariantMap &prop);

    Q_INVOKABLE QVariant property(const QString &key) const;
    Q_INVOKABLE QVariant operator[](const QString &key) const;
    Q_INVOKABLE void setProperty(const QString &key, const QVariant &value);
    Q_INVOKABLE void removeProperty(const QString &key);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);

signals:
    void propertiesChanged();

protected:
    QVariantMap m_properties;
};

class PropertyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PropertyRoles {
        PropertyRole = Qt::UserRole + 1,
        IdRole,
        PropertiesRole
    };
    Q_ENUM(PropertyRoles)

    PropertyModel(QObject *parent = nullptr);

    Q_INVOKABLE PropertyItem* append(const PropertyItem::Id proposed_id = 0);
    Q_INVOKABLE void removeAt(const int index);
    Q_INVOKABLE bool removeOne(const PropertyItem::Id id);
    Q_INVOKABLE void clear();

    Q_INVOKABLE PropertyItem *at(const int index) const;
    Q_INVOKABLE const PropertyItem &operator[](const int index) const;
    Q_INVOKABLE PropertyItem *get(const PropertyItem::Id id) const;
    Q_INVOKABLE int indexOf(const PropertyItem::Id id) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

signals:
    void propertyInserted(PropertyItem *property);
    void propertyRemoved(const PropertyItem::Id id);
    void propertyChanged(PropertyItem *property);

protected:
    virtual PropertyItem *makeProperty(const PropertyItem::Id id);
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QSharedPointer<PropertyItem>> m_properties;
};

class PropertyFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterKey READ filterKey WRITE setFilterKey NOTIFY filterKeyChanged)
    Q_PROPERTY(QVariant filterValue READ filterValue WRITE setFilterValue NOTIFY filterValueChanged)

signals:
    void filterKeyChanged();
    void filterValueChanged();

public:
    PropertyFilterModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent)
    {
    }

    QString filterKey() const
    {
        return m_filterKey;
    }

    void setFilterKey(const QString &key)
    {
        emit beginResetModel();
        m_filterKey = key;
        emit endResetModel();
    }

    QVariant filterValue() const
    {
        return m_filterValue;
    }

    void setFilterValue(const QVariant &value)
    {
        emit beginResetModel();
        m_filterValue = value;
        emit endResetModel();
    }

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
    {
        return sourceModel()->data(sourceModel()->index(sourceRow, 0, sourceParent),
                                   PropertyModel::PropertiesRole).toMap().value(m_filterKey) == m_filterValue;
    }

private:
    QString m_filterKey;
    QVariant m_filterValue;
};

#endif // PROPERTYMODEL_HPP

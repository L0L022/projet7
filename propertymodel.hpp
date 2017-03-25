#ifndef PROPERTYMODEL_HPP
#define PROPERTYMODEL_HPP

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QSharedPointer>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

class PropertyItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QVariantMap properties READ properties WRITE setProperties NOTIFY propertiesChanged)

protected:
    QVariantMap _properties;

signals:
    void propertiesChanged();
    void propertyChanged(const QString &key);
    void propertyRemoved(const QString &key);

public:
    PropertyItem(const int _id = 0, QObject *parent = nullptr);

    int id() const;
    const QVariantMap &properties() const;
    void setProperties(const QVariantMap &prop);

    Q_INVOKABLE QVariant property(const QString &key) const;
    Q_INVOKABLE QVariant operator[](const QString &key) const;
    Q_INVOKABLE void setProperty(const QString &key, const QVariant &value);
    Q_INVOKABLE void removeProperty(const QString &key);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);
};

class PropertyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PropertyRoles {
        ItemRole = Qt::UserRole + 1,
        IdRole,
        PropertiesRole
    };
    Q_ENUM(PropertyRoles)

    PropertyModel(QObject *parent = nullptr);
    Q_INVOKABLE PropertyItem* append(const int proposed_id = 0);

    Q_INVOKABLE PropertyItem *at(const int index) const;
    Q_INVOKABLE void removeAt(const int index);
    Q_INVOKABLE bool removeOne(const int id);
    Q_INVOKABLE void clear();

    Q_INVOKABLE int indexOf(const int id) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

protected:
    virtual PropertyItem *makeProperty(const int id);
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QSharedPointer<PropertyItem>> _properties;
};

class PropertyFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
    Q_PROPERTY(QString filterKey READ filterKey WRITE setFilterKey NOTIFY filterKeyChanged)
    Q_PROPERTY(QVariant filterValue READ filterValue WRITE setFilterValue NOTIFY filterValueChanged)
    QString _filterKey;
    QVariant _filterValue;

signals:
    void filterKeyChanged();
    void filterValueChanged();

public:
    PropertyFilterModel(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

    QString filterKey() const {
        return _filterKey;
    }
    void setFilterKey(const QString &key) {
        emit beginResetModel();
        _filterKey = key;
        emit endResetModel();
    }

    QVariant filterValue() const {
        return _filterValue;
    }
    void setFilterValue(const QVariant &value) {
        emit beginResetModel();
        _filterValue = value;
        emit endResetModel();
    }

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        return sourceModel()->data(sourceModel()->index(sourceRow, 0, sourceParent),
                                   PropertyModel::PropertiesRole).toMap().value(_filterKey) == _filterValue;
    }
};

#endif // PROPERTYMODEL_HPP

#ifndef PLAYERADDITION_HPP
#define PLAYERADDITION_HPP

#include <QJsonObject>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QSharedPointer>
#include <QJsonArray>

#include "propertyitem.hpp"

class PlayerAdditionItem : public PropertyItem {
    Q_OBJECT
    Q_PROPERTY(QString category READ getCategory NOTIFY categoryChanged)
public:
    PlayerAdditionItem(const int id = 0, QObject *parent = nullptr) : PropertyItem(id, parent) {
        for(const QString &str : {"name", "description", "category"})
            _properties[str] = "";
        for(const QString &nb : {"CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
            _properties[nb] = 0;
        connect(this, &PlayerAdditionItem::propertyChanged, this, [this](const QString &key){
           if(key == "category")
               emit categoryChanged();
        });
    }

    QString getCategory() const {
        return _properties["category"].toString();
    }

signals:
    void categoryChanged();
};

class PlayerAdditionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AdditionRoles {
        ItemRole = Qt::UserRole + 1,
        IdRole,
        CategoryRole,
        PropertiesRole
    };
    Q_ENUM(AdditionRoles)

    PlayerAdditionModel(QObject *parent = nullptr);
    Q_INVOKABLE PlayerAdditionItem* addAddition(const int proposed_id = 0);
    Q_INVOKABLE bool removeAddition(const int id);

    int additionIdToIndex(const int id) const;
    QModelIndex additionIdToQIndex(const int id) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void fromJson(const QJsonArray &json);
    QJsonArray toJson() const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QSharedPointer<PlayerAdditionItem>> _additions;
};

#endif // PLAYERADDITION_HPP

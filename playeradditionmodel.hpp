#ifndef PLAYERADDITION_HPP
#define PLAYERADDITION_HPP

#include <QJsonObject>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QSharedPointer>

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
    Q_INVOKABLE PlayerAdditionItem* addAddition();
    Q_INVOKABLE bool removeAddition(const int id);
    //Q_INVOKABLE void addProperty(const int id, const QString &key, const QVariant &value);
    //Q_INVOKABLE void removeProperty(const int id, const QString &key);

    int additionIdToIndex(const int id) const;
    QModelIndex additionIdToQIndex(const int id) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    void copy(const PlayerAdditionModel &src);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QSharedPointer<PlayerAdditionItem>> _additions;
};
/*
class PlayerAdditionFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model WRITE setSourceModel NOTIFY modelChanged)
    QString _role;

};
*/
#endif // PLAYERADDITION_HPP

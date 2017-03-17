#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include <QJsonObject>
#include <QAbstractListModel>
#include <QSharedPointer>
#include <QObject>

#include "propertyitem.hpp"
#include "playeradditionmodel.hpp"

class PlayerItem : public PropertyItem {
    Q_OBJECT
    PlayerAdditionModel _additions;

public:
    PlayerItem(const int id = 0, QObject *parent = nullptr) : PropertyItem(id, parent) {
        _properties["edit"] = false;
        for(const QString &str : {"name", "calling"})
            _properties[str] = "";
        for(const QString &nb : {"age", "height", "CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
            _properties[nb] = 0;
    }

    QObject *getAdditions() {
        return &_additions;
    }

    const QObject *getAdditions() const {
        return &_additions;
    }
};

class PlayerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PlayerRoles {
        PlayerRole = Qt::UserRole + 1,
        IdRole,
        PropertiesRole,
        AdditionsRole
    };

    PlayerModel(QObject *parent = nullptr);
    Q_INVOKABLE PlayerItem* addPlayer();
    Q_INVOKABLE bool removePlayer(const int id);
    Q_INVOKABLE PlayerItem *getPlayer(const int id);
    //Q_INVOKABLE void addProperty(const int id, const QString &key, const QVariant &value);
    //Q_INVOKABLE void removeProperty(const int id, const QString &key);

    int playerIdToIndex(const int id) const;
    QModelIndex playerIdToQIndex(const int id) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QSharedPointer<PlayerItem>> _players;
};

#endif // PLAYERMODEL_HPP

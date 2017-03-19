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

    Q_INVOKABLE PlayerAdditionModel *getAdditions() {
        return &_additions;
    }
};

class PlayerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        ItemRole = Qt::UserRole + 1,
        IdRole,
        PropertiesRole,
        AdditionsRole
    };
    Q_ENUM(ItemRoles)

    PlayerModel(QObject *parent = nullptr);
    Q_INVOKABLE PlayerItem* addPlayer(const int proposed_id = 0);
    Q_INVOKABLE bool removePlayerId(const int id);
    Q_INVOKABLE bool removePlayerIndex(const int index);
    Q_INVOKABLE PlayerItem *getPlayerId(const int id);
    Q_INVOKABLE PlayerItem *getPlayerIndex(const int index);

    int playerIdToIndex(const int id) const;
    QModelIndex playerIdToQIndex(const int id) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void fromJson(const QJsonArray &json);
    QJsonArray toJson() const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QSharedPointer<PlayerItem>> _players;
};

#endif // PLAYERMODEL_HPP

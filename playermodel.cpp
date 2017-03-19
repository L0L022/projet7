#include "playermodel.hpp"

PlayerModel::PlayerModel(QObject *parent) : QAbstractListModel(parent)
{
}

PlayerItem* PlayerModel::addPlayer(const int proposed_id) {
    int id = proposed_id;
    for(int i = 0; i < _players.size(); ++i) {
        if(id == _players[i]->getId()) {
            ++id;
            i = 0;
        }
    }

    QSharedPointer<PlayerItem> player(new PlayerItem(id, this));
    connect(player.data(), &PlayerItem::propertiesChanged, this, [this](){
        PlayerItem *player = qobject_cast<PlayerItem*>(sender());
        QModelIndex index = playerIdToQIndex(player->getId());
        emit dataChanged(index, index, {PropertiesRole}); //add item ?
    });

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _players.append(player);
    endInsertRows();

    return player.data();
}

bool PlayerModel::removePlayerId(const int id) {
    return removePlayerIndex(playerIdToIndex(id));
}

bool PlayerModel::removePlayerIndex(const int index) {
    if(index < 0)
        return false;

    beginRemoveRows(QModelIndex(), index, index);
    _players.removeAt(index);
    endRemoveRows();

    return true;
}

PlayerItem *PlayerModel::getPlayerId(const int id) {
    return getPlayerIndex(playerIdToIndex(id));
}

PlayerItem *PlayerModel::getPlayerIndex(const int index) {
    return _players[index].data();
}

int PlayerModel::playerIdToIndex(const int id) const {
    int index = -1;
    for(int i = 0; i < _players.size(); ++i)
        if(_players[i]->getId() == id)
            index = i;

    return index;
}

QModelIndex PlayerModel::playerIdToQIndex(const int id) const {
    return createIndex(playerIdToIndex(id), 0);
}

int PlayerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _players.count();
}

QVariant PlayerModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= _players.count())
        return QVariant();

    PlayerItem *player = _players[index.row()].data();
    if (role == ItemRole)
        return QVariant::fromValue(player);
    else if (role == IdRole)
        return player->getId();
    else if (role == PropertiesRole)
        return player->getProperties();
    else if(role == AdditionsRole)
        return QVariant::fromValue(player->getAdditions());

    return QVariant();
}

void PlayerModel::fromJson(const QJsonArray &json) {
    _players.clear();
    for(const QJsonValue &value : json) {
        if(value.isObject()) {
            QJsonObject player = value.toObject();
            if(player.contains("id")) {
                PlayerItem * item = addPlayer(player["id"].toInt());
                item->setProperties(player.toVariantMap());
                item->getAdditions()->fromJson(player["additions"].toArray());
            }
        }
    }
}

QJsonArray PlayerModel::toJson() const {
    QJsonArray model;
    for(const QSharedPointer<PlayerItem> pt : _players) {
        QJsonObject player = QJsonObject::fromVariantMap(pt->getProperties());
        player["additions"] = pt->getAdditions()->toJson();
        model.append(player);
    }
    return model;
}

QHash<int, QByteArray> PlayerModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ItemRole] = "item_role";
    roles[IdRole] = "id_role";
    roles[PropertiesRole] = "properties_role";
    roles[AdditionsRole] = "additions_role";
    return roles;
}

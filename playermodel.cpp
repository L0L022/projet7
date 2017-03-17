#include "playermodel.hpp"

PlayerModel::PlayerModel(QObject *parent) : QAbstractListModel(parent)
{
}

PlayerItem* PlayerModel::addPlayer() {
    int id = 0;
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

bool PlayerModel::removePlayer(const int id) {
    int index = playerIdToIndex(id);
    if(index < 0)
        return false;

    beginRemoveRows(QModelIndex(), index, index);
    _players.removeAt(index);
    endRemoveRows();

    return true;
}

PlayerItem *PlayerModel::getPlayer(const int id) {
    return _players[playerIdToIndex(id)].data();
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
/*
void PlayerModel::addProperty(const int id, const QString &key, const QVariant &value) {
    QModelIndex index = createIndex(playerIdToIndex(id), 0);
    if(index.isValid()) {
        _players[index.row()].setProperty(key, value);
        emit dataChanged(index, index, {PropertiesRole});
    }
}

void PlayerModel::removeProperty(const int id, const QString &key) {
    QModelIndex index = createIndex(playerIdToIndex(id), 0);
    if(index.isValid()) {
        _players[index.row()].removeProperty(key);
        emit dataChanged(index, index, {PropertiesRole});
    }
}
*/
int PlayerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _players.count();
}

QVariant PlayerModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= _players.count())
        return QVariant();

    PlayerItem *player = _players[index.row()].data();
    if (role == PlayerRole)
        return QVariant::fromValue(player);
    else if (role == IdRole)
        return player->getId();
    else if (role == PropertiesRole)
        return player->getProperties();
    else if(role == AdditionsRole)
        return QVariant::fromValue(player->getAdditions());

    return QVariant();
}
/*
bool PlayerModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() >= _players.count())
        return false;

    PlayerItem &player = _players[index.row()];
    if (role == PropertiesRole && value.isValid()) {
        player.setProperties(value.toJsonObject());
        emit dataChanged(index, index, {PropertiesRole});
        return true;
    }

    return false;
}
*/
QHash<int, QByteArray> PlayerModel::roleNames() const {
    qDebug("salut les gens");
    QHash<int, QByteArray> roles;
    roles[PlayerRole] = "player";
    roles[IdRole] = "id";
    roles[PropertiesRole] = "properties";
    roles[AdditionsRole] = "additions";
    return roles;
}

#include "playeradditionmodel.hpp"

PlayerAdditionModel::PlayerAdditionModel(QObject *parent) : QAbstractListModel(parent)
{}

PlayerAdditionItem* PlayerAdditionModel::addAddition() {
    int id = 0;
    for(int i = 0; i < _additions.size(); ++i) {
        if(id == _additions[i]->getId()) {
            ++id;
            i = 0;
        }
    }

    QSharedPointer<PlayerAdditionItem> addition(new PlayerAdditionItem(id, this));
    connect(addition.data(), &PlayerAdditionItem::propertiesChanged, this, [this](){
        PlayerAdditionItem *player = qobject_cast<PlayerAdditionItem*>(sender());
        QModelIndex index = additionIdToQIndex(player->getId());
        emit dataChanged(index, index, {PropertiesRole}); //add item ?
    });

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _additions.append(addition);
    endInsertRows();

    return addition.data();
}

bool PlayerAdditionModel::removeAddition(const int id) {
    int index = additionIdToIndex(id);
    if(index < 0)
        return false;

    beginRemoveRows(QModelIndex(), index, index);
    _additions.removeAt(index);
    endRemoveRows();

    return true;
}

int PlayerAdditionModel::additionIdToIndex(const int id) const {
    int index = -1;
    for(int i = 0; i < _additions.size(); ++i)
        if(_additions[i]->getId() == id)
            index = i;

    return index;
}

QModelIndex PlayerAdditionModel::additionIdToQIndex(const int id) const {
    return createIndex(additionIdToIndex(id), 0);
}
/*
void PlayerAdditionModel::addProperty(const int id, const QString &key, const QVariant &value) {
    QModelIndex index = createIndex(additionIdToIndex(id), 0);
    if(index.isValid()) {
        _additions[index.row()]->setProperty(key, value);
        emit dataChanged(index, index, {PropertiesRole});
    }
}

void PlayerAdditionModel::removeProperty(const int id, const QString &key) {
    QModelIndex index = createIndex(additionIdToIndex(id), 0);
    if(index.isValid()) {
        _additions[index.row()]->removeProperty(key);
        emit dataChanged(index, index, {PropertiesRole});
    }
}
*/
int PlayerAdditionModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _additions.count();
}

QVariant PlayerAdditionModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= _additions.count())
        return QVariant();

    PlayerAdditionItem *addition = _additions[index.row()].data();
    if (role == ItemRole)
        return QVariant::fromValue(addition);
    else if (role == IdRole)
        return addition->getId();
    else if (role == CategoryRole)
        return addition->getCategory();
    else if (role == PropertiesRole)
        return addition->getProperties();

    return QVariant();
}
/*
bool PlayerAdditionModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() >= _additions.count())
        return false;

    PlayerAdditionItem &addition = _additions[index.row()];
    if (role == PropertiesRole && value.isValid()) {
        addition.setProperties(value.toJsonObject());
        emit dataChanged(index, index, {PropertiesRole});
        return true;
    }

    return false;
}
*/
void PlayerAdditionModel::copy(const PlayerAdditionModel &src) {
    _additions = src._additions;
}

QHash<int, QByteArray> PlayerAdditionModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ItemRole] = "addition";
    roles[IdRole] = "id";
    roles[CategoryRole] = "category";
    roles[PropertiesRole] = "properties";
    return roles;
}

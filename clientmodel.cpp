#include "clientmodel.hpp"

ClientModel::ClientModel(QObject *parent)
    : QAbstractListModel(parent),
      m_clients()
{
    m_clients.append({tr("Nobody"), -1, nullptr});
}

void ClientModel::append(const ClientItem &client)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_clients.append(client);
    endInsertRows();
}

void ClientModel::removeAt(const int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_clients.removeAt(index);
    endRemoveRows();
}

bool ClientModel::removeOne(const ClientItem& client)
{
    int index = m_clients.indexOf(client);
    if (index < 0)
        return false;

    removeAt(index);

    return true;
}

const ClientItem &ClientModel::at(const int index) const
{
    return m_clients.at(index);
}

ClientItem &ClientModel::operator[](const int index)
{
    return m_clients[index];
}

int ClientModel::idToIndex(const QVariant &id) const
{
    for (int i = 0; i < rowCount(); ++i)
        if (m_clients[i].id == id.value<PropertyItem::Id>())
            return i;
    return 0;
}

void ClientModel::setId(const int index, const QVariant &id)
{
    PropertyItem::Id pid = id.value<PropertyItem::Id>();
    if (m_clients[index].id != pid) {
        for (int i = 0; i < rowCount(); ++i) {
            if (m_clients[i].id == pid) {
                m_clients[i].id = -1;
                auto qindex = createIndex(i, 0);
                emit dataChanged(qindex, qindex, {IdRole});
            }
        }
        m_clients[index].id = pid;
        auto qindex = createIndex(index, 0);
        emit dataChanged(qindex, qindex, {IdRole});
    }
}

int ClientModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_clients.count();
}

QVariant ClientModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_clients.count())
        return QVariant();

    const ClientItem &client = m_clients.at(index.row());

    if (role == NameRole)
        return client.name;
    else if (role == IdRole)
        return client.id;

    return QVariant();
}

QHash<int, QByteArray> ClientModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "nameRole";
    roles[IdRole] = "idRole";
    return roles;
}

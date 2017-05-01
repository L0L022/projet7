#include "clientmodel.hpp"

ClientModel::ClientModel(QObject *parent)
    : QAbstractListModel(parent),
      m_clients()
{
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
    if(index < 0)
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

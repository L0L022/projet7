#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QAbstractListModel>
#include <QTcpSocket>

#include "propertymodel.hpp"

class ClientItem {
public:
    QString name;
    PropertyItem::Id id;
    QList<PropertyItem::Id> readRights;
    QList<PropertyItem::Id> writeRights;
    QTcpSocket *socket;

    bool operator ==(const ClientItem &client)
    {
        return name == client.name && id == client.id && readRights == client.readRights && writeRights == client.writeRights && socket == client.socket;
    }
};

class ClientModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ClientRoles {
        NameRole = Qt::UserRole + 1,
        IdRole,
        ReadRightsRole,
        WriteRightRole,
        SocketRole
    };
    Q_ENUM(ClientRoles)

    explicit ClientModel(QObject *parent = nullptr);

    void append(const ClientItem &client);
    void removeAt(const int index);
    bool removeOne(const ClientItem& client);

    const ClientItem &at(const int index) const;
    ClientItem &operator[](const int index);

    Q_INVOKABLE void setId(const int index, const QVariant& id);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ClientItem> m_clients;
};

#endif // CLIENTMODEL_H

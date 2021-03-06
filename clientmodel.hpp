#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QAbstractListModel>
#include <QTcpSocket>

#include "propertymodel.hpp"

class ClientItem {
public:
    ClientItem()
        : name("Unanme client"), id(-1), socket(nullptr)
    {
    }

    bool operator ==(const ClientItem &client)
    {
        return name == client.name && id == client.id && socket == client.socket;
    }

    QString name;
    PropertyItem::Id id;
    QTcpSocket *socket;
};

class ClientModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ClientRoles {
        NameRole = Qt::UserRole + 1,
        IdRole,
        SocketRole
    };
    Q_ENUM(ClientRoles)

    explicit ClientModel(QObject *parent = nullptr);

    void append(const ClientItem &client);
    void removeAt(const int index);
    bool removeOne(const ClientItem& client);

    const ClientItem &at(const int index) const;
    //le model n'est pas notifié si clientitem change
    ClientItem &operator[](const int index);
    Q_INVOKABLE int idToIndex(const QVariant &id) const;

    Q_INVOKABLE void setName(const int index, const QString &name);
    Q_INVOKABLE void setId(const int index, const QVariant &id);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

signals:
    void modelChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ClientItem> m_clients;
};

#endif // CLIENTMODEL_H

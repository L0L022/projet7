#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>

#include "game.hpp"

class GameServer : public Game
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> clients READ clients NOTIFY clientsChanged)
    typedef QMap<PropertyItem::Id, QList<PropertyItem::Id>> MapRights;

public:
    explicit GameServer(const QString &fileName, QObject *parent = nullptr);
    ~GameServer();

    GameType type() const;

    QString ipAddress() const;
    quint16 port() const;

    QList<QString> clients() const;

signals:
    void clientsChanged();

protected:
    void handleLeavingCommands();

private:
    void openServer();
    void closeServer();
    void newConnection();

    void playersNew(const QModelIndex &parent, int first, int last);
    void playersRemove(const QModelIndex &parent, int first, int last);

    void openFromFile();
    void saveToFile();

    // inutile si on fait ça dans handleLeavingCommand
    void sendGame();

    QJsonObject rightsToJson(const MapRights map) const;
    void rightsFromJson(const QJsonObject object, MapRights &map);

    QJsonArray playersToJson(const PropertyItem::Id id) const;

    //c'est vraiment pertinant si on utilise sendGame tout le temps ?
    QJsonObject playerSpecificCommand(const QJsonObject &command, const PropertyItem::Id id) const;

    QString m_fileName;
    QTcpServer m_server;
    QList<QTcpSocket*> m_sockets;

    QMap<QString, PropertyItem::Id> m_clientToId;
    MapRights m_readRights;
    MapRights m_writeRights;
};

#endif // GAMESERVER_HPP

#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>

#include "game.hpp"
#include "clientmodel.hpp"

class GameServer : public Game
{
    Q_OBJECT
    typedef QMap<PropertyItem::Id, QList<PropertyItem::Id>> MapRights;

public:
    explicit GameServer(const QString &fileName, QObject *parent = nullptr);
    ~GameServer();

    GameType type() const;

    QString ipAddress() const;
    quint16 port() const;

    Q_INVOKABLE ClientModel *clients();

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

    ClientModel m_clients;
    MapRights m_readRights;
    MapRights m_writeRights;
};

#endif // GAMESERVER_HPP

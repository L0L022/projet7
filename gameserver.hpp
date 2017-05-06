#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>

#include "game.hpp"
#include "clientmodel.hpp"

class GameServer : public Game
{
    Q_OBJECT

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
    void pushIncomingCommand(QIODevice &device);
    void readCommand(const QJsonObject &command);
    void handleLeavingCommands();

private:
    void openServer();
    void closeServer();
    void newConnection();

    // sert à rien ...
    void playersNew(const QModelIndex &parent, int first, int last);
    void playersRemove(const QModelIndex &parent, int first, int last);

    void openFromFile();
    void saveToFile();

    // inutile si on fait ça dans handleLeavingCommand
    void sendGame();
    QJsonArray playersToJson(const PropertyItem::Id id) const;

    QString m_fileName;
    QTcpServer m_server;
    ClientModel m_clients;
};

#endif // GAMESERVER_HPP

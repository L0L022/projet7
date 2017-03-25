#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QTcpServer>

#include "game.hpp"

class GameServer : public Game
{
    Q_OBJECT

    QTcpServer _server;
public:
    explicit GameServer(QObject *parent = nullptr);
    ~GameServer();

    QString location() const;

private:
    void disconnect();
};

#endif // GAMESERVER_HPP

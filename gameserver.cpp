#include "gameserver.hpp"

GameServer::GameServer(QObject *parent) : Game(parent)
{

}

GameServer::~GameServer() {
    disconnect();
}

QString GameServer::location() const {
    return QString("%1:%2").arg(_server.serverAddress().toString()).arg(_server.serverPort());
}

void GameServer::disconnect() {

}

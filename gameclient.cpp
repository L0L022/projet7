#include "gameclient.hpp"
#include <QHostAddress>

GameClient::GameClient(const QHostAddress &address, quint16 port, QObject *parent) : Game(parent) {

}

GameClient::~GameClient() {
    disconnect();
}

QString GameClient::location() const {
    return QString("%1:%2").arg(_socket.peerAddress().toString()).arg(_socket.peerPort());
}

void GameClient::disconnect() {

}

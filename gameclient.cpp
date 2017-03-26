#include "gameclient.hpp"
#include <QTextStream>
#include <QHostAddress>

GameClient::GameClient(const QString &address, quint16 port, QObject *parent) : Game(parent), _socket(this) {
    connect(&_socket, &QTcpSocket::connected, this, [this]{
        emit ipAddressChanged();
        emit portChanged();
    });
    connect(&_socket, &QTcpSocket::disconnected, this, [this]{
        emit ipAddressChanged();
        emit portChanged();
    });
    connect(&_socket, &QTcpSocket::readyRead, this, [this](){
        readData(_socket.readAll());
    });
    connect(&_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, [this](){
        emit error(_socket.errorString());
    });
    _socket.connectToHost(address, port);
}

GameClient::~GameClient() {
    _socket.disconnectFromHost();
}

QString GameClient::ipAddress() const {
    return _socket.peerAddress().toString();
}

quint16 GameClient::port() const {
    return _socket.peerPort();
}

void GameClient::writeData(const QByteArray &data) {
    QTextStream stream(&_socket);
    stream << data;
}

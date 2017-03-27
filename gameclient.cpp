#include "gameclient.hpp"
#include <QTextStream>
#include <QHostAddress>

GameClient::GameClient(const QString &address, quint16 port, QObject *parent)
    : Game(parent),
      m_socket(this)
{
    connect(&m_socket, &QTcpSocket::connected, this, [this]{
        emit ipAddressChanged();
        emit portChanged();
    });

    connect(&m_socket, &QTcpSocket::disconnected, this, [this]{
        emit ipAddressChanged();
        emit portChanged();
    });

    connect(&m_socket, &QTcpSocket::readyRead, this, [this](){
        readData(m_socket.readAll());
    });

    connect(&m_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, [this](){
        emit error(m_socket.errorString());
    });

    m_socket.connectToHost(address, port);
}

GameClient::~GameClient()
{
    m_socket.disconnectFromHost();
}

Game::GameType GameClient::type() const
{
    return ClientGame;
}

QString GameClient::ipAddress() const
{
    return m_socket.peerAddress().toString();
}

quint16 GameClient::port() const
{
    return m_socket.peerPort();
}
/*
GameItem GameClient::toGameItem() const
{
    return GameItem(ipAddress(), port(), name());
}
*/
void GameClient::writeData(const QByteArray &data)
{
    QTextStream stream(&m_socket);
    stream << data;
}

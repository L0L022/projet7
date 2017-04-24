#include "gameclient.hpp"
#include <QTextStream>
#include <QHostAddress>

GameClient::GameClient(const QString &address, quint16 port, QObject *parent)
    : Game(parent),
      m_userName(""),
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
        pushIncomingCommand(m_socket);
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

QString GameClient::userName() const
{
    return m_userName;
}

void GameClient::setUserName(const QString &userName)
{
    if (m_userName == userName)
        return;
    m_userName = userName;
    emit userNameChanged();

    QJsonObject command;
    command["commandType"] = UserNameCommand;
    command["value"] = m_userName;
    sendCommand(command);
}

QString GameClient::ipAddress() const
{
    return m_socket.peerAddress().toString();
}

quint16 GameClient::port() const
{
    return m_socket.peerPort();
}

void GameClient::handleLeavingCommands()
{
    while(!m_leavingCommands.isEmpty())
        writeCommand(m_leavingCommands.dequeue(), m_socket);
}

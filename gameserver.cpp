#include "gameserver.hpp"
#include <QFile>
#include <QJsonDocument>

GameServer::GameServer(const QString &fileName, QObject *parent)
    : Game(parent),
      m_fileName(fileName),
      m_server(this),
      m_sockets()
{
    connect(&m_server, &QTcpServer::acceptError, this, [this](){
        emit error(m_server.errorString());
    });

    connect(&m_server, &QTcpServer::newConnection, this, &GameServer::newConnection);

    openFromFile();
    openServer();
}

GameServer::~GameServer()
{
    closeServer();
    saveToFile();
}

Game::GameType GameServer::type() const
{
    return ServerGame;
}

QString GameServer::ipAddress() const
{
    return m_server.serverAddress().toString();
}

quint16 GameServer::port() const
{
    return m_server.serverPort();
}
/*
GameItem GameServer::toGameItem() const
{
    return GameItem()
}
*/
void GameServer::openServer()
{
    m_server.listen();
    emit ipAddressChanged();
    emit portChanged();
}

void GameServer::closeServer()
{
    m_server.close();
    emit ipAddressChanged();
    emit portChanged();

    for (QTcpSocket *socket : m_sockets)
        socket->disconnectFromHost();
}

void GameServer::newConnection()
{
    while (m_server.hasPendingConnections()) {
        QTcpSocket *socket = m_server.nextPendingConnection();

        connect(socket, &QTcpSocket::disconnected, this, [this, socket](){
            m_sockets.removeOne(socket);
        });

        connect(socket, &QTcpSocket::readyRead, this, [this, socket](){
            readData(socket->readAll());
        });

        m_sockets.append(socket);
    }
}

void GameServer::openFromFile()
{
    QFile file;
    file.setFileName(m_fileName);
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            if(doc.isObject())
                fromJson(doc.object());
        }
    }
}

void GameServer::saveToFile()
{
    QFile file;
    file.setFileName(m_fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument doc(toJson());
        QTextStream stream(&file);
        stream << doc.toJson();
    }
}

void GameServer::writeData(const QByteArray &data)
{
    for (QTcpSocket *socket : m_sockets) {
        QTextStream stream(socket);
        stream << data;
    }
}

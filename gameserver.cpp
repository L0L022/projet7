#include "gameserver.hpp"
#include <QFile>
#include <QJsonDocument>

GameServer::GameServer(const QString &fileName, QObject *parent) : Game(parent), _fileName(fileName), _server(this), _sockets() {
    connect(&_server, &QTcpServer::acceptError, this, [this](){
        emit error(_server.errorString());
    });
    connect(&_server, &QTcpServer::newConnection, this, &GameServer::newConnection);

    openFromFile();
    openServer();
}

GameServer::~GameServer() {
    closeServer();
    saveToFile();
}

QString GameServer::ipAddress() const {
    return _server.serverAddress().toString();
}

quint16 GameServer::port() const {
    return _server.serverPort();
}

void GameServer::openServer() {
    _server.listen();
    emit ipAddressChanged();
    emit portChanged();
}

void GameServer::closeServer() {
    _server.close();
    emit ipAddressChanged();
    emit portChanged();
    for(QTcpSocket *socket : _sockets)
        socket->disconnectFromHost();
}

void GameServer::newConnection() {
    while(_server.hasPendingConnections()) {
        QTcpSocket *socket = _server.nextPendingConnection();
        connect(socket, &QTcpSocket::disconnected, this, [this](){
            _sockets.removeAll(qobject_cast<QTcpSocket*>(sender()));
        });
        connect(socket, &QTcpSocket::readyRead, this, [this](){
            readData(qobject_cast<QTcpSocket*>(sender())->readAll());
        });
        _sockets.append(socket);
    }
}

void GameServer::openFromFile() {
    QFile file;
    file.setFileName(_fileName);
    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            if(doc.isObject())
                fromJson(doc.object());
        }
    }
}

void GameServer::saveToFile() {
    QFile file;
    file.setFileName(_fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument doc(toJson());
        QTextStream stream(&file);
        stream << doc.toJson();
    }
}

void GameServer::writeData(const QByteArray &data) {
    for(QTcpSocket *socket : _sockets) {
        QTextStream stream(socket);
        stream << data;
    }
}

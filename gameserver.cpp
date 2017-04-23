#include "gameserver.hpp"
#include <QFile>
#include <QJsonDocument>

GameServer::GameServer(const QString &fileName, QObject *parent)
    : Game(parent),
      m_fileName(fileName),
      m_server(this),
      m_sockets(),
      m_clientToId(),
      m_readRights(),
      m_writeRights()
{
    connect(&m_server, &QTcpServer::acceptError, this, [this](){
        emit error(m_server.errorString());
    });

    connect(&m_server, &QTcpServer::newConnection, this, &GameServer::newConnection);

    connect(players(), &PlayerModel::rowsInserted, this, &GameServer::playersNew);
    connect(players(), &PlayerModel::rowsAboutToBeRemoved, this, &GameServer::playersRemove);

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

QList<QString> GameServer::clients() const
{
    QList<QString> list;
    for (const QTcpSocket *socket : m_sockets)
        list.append(socket->peerAddress().toString());
    return list;
}

void GameServer::writeData(const QByteArray &data)
{
    for (QTcpSocket *socket : m_sockets) {
        QTextStream stream(socket);
        stream << data;
    }
}

void GameServer::readCommand(const QJsonObject &object)
{
    //writeCommand(object);
    Game::readCommand(object);

    //sendGame();
}

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
            readData(*socket);
        });

        m_sockets.append(socket);
        sendGame();
    }
}

void GameServer::playersNew(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    for (int i = first; i <= last; ++i) {
        PropertyItem *property = players()->at(i);
        if (!m_readRights.contains(property->id()))
            m_readRights[property->id()] = {property->id()};
        if (!m_writeRights.contains(property->id()))
            m_writeRights[property->id()] = {property->id()};
    }
}

void GameServer::playersRemove(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    for (int i = first; i <= last; ++i) {
        PropertyItem *property = players()->at(i);
        m_readRights.remove(property->id());
        m_writeRights.remove(property->id());
    }
}

void GameServer::openFromFile()
{
    QFile file;
    file.setFileName(m_fileName);
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            if(doc.isObject()) {
                QJsonObject object = doc.object();
                rightsFromJson(object["readRights"].toObject(), m_readRights);
                rightsFromJson(object["writeRights"].toObject(), m_writeRights);
                fromJson(object);
            }
        }
    }
}

void GameServer::saveToFile()
{
    QFile file;
    file.setFileName(m_fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonObject object = toJson();
        object["readRights"] = rightsToJson(m_readRights);
        object["writeRights"] = rightsToJson(m_writeRights);
        QJsonDocument doc(object);
        QTextStream stream(&file);
        stream << doc.toJson();
    }
}

void GameServer::sendGame()
{
    for (QTcpSocket *socket : m_sockets) {
        QJsonObject command;
        command["commandType"] = PlayersResetCommand;
        command["value"] = players()->toJson(); //use playersToJson

        QTextStream stream(socket);
        stream << QJsonDocument(command).toJson(QJsonDocument::Compact).append('\n');
    }
}

QJsonObject GameServer::rightsToJson(const MapRights map) const
{
    QJsonObject object;
    QMapIterator<PropertyItem::Id, QList<PropertyItem::Id>> it(map);
    while (it.hasNext()) {
        it.next();
        QJsonArray array;
        for (const PropertyItem::Id &id : it.value())
            array.append(id);
        object[QString::number(it.key())] = array;
    }
    return object;
}

void GameServer::rightsFromJson(const QJsonObject object, MapRights &map)
{
    for (QJsonObject::ConstIterator it = object.constBegin(); it != object.constEnd(); ++it) {
        QList<PropertyItem::Id> list;
        for (const QJsonValue value : it.value().toArray())
            list.append(value.toVariant().value<PropertyItem::Id>());
        map[it.key().toInt()] = list;
    }
}

QJsonArray GameServer::playersToJson(const PropertyItem::Id id) const
{
    QJsonArray array;
    QList<PropertyItem::Id> read = m_readRights[id];
    QList<PropertyItem::Id> write = m_writeRights[id];
    for (int i = 0; i < players()->rowCount(); ++i) {
        PropertyItem * property = players()->at(i);
        if (read.contains(property->id())) {
            QJsonObject object = property->toJson();
            if (write.contains(property->id()))
                object["editable"] = true;
            else
                object["editable"] = false;
            array.append(object);
        }
    }
    return array;
}

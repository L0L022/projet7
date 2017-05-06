#include "gameserver.hpp"
#include <QFile>
#include <QJsonDocument>

GameServer::GameServer(const QString &fileName, QObject *parent)
    : Game(parent),
      m_fileName(fileName),
      m_server(this),
      m_clients(this)
{
    connect(players(), &PlayerModel::propertyInserted, this, [this](PropertyItem *property){
        PlayerItem *player = qobject_cast<PlayerItem*>(property);
        if (player) {
            connect(player, &PlayerItem::readRightsChanged, this, &GameServer::sendGame);
            connect(player, &PlayerItem::writeRightsChanged, this, &GameServer::sendGame);
        }
    });

    connect(&m_server, &QTcpServer::acceptError, this, [this](){
        emit error(m_server.errorString());
    });

    connect(&m_server, &QTcpServer::newConnection, this, &GameServer::newConnection);

    connect(&m_clients, &ClientModel::modelChanged, this, &GameServer::sendGame);

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

ClientModel *GameServer::clients()
{
    return &m_clients;
}

void GameServer::pushIncomingCommand(QIODevice &device)
{
    PropertyItem::Id senderId(-1);
    for (int i = 0; i < m_clients.rowCount(); ++i)
        if (m_clients[i].socket == &device)
            senderId = m_clients[i].id;

    while(device.canReadLine()) {
        QByteArray data = device.readLine();
        qDebug() << "Sender id : " << senderId;
        qDebug() << "Game::pushIncomingCommand() :" << data;
        QJsonObject command = QJsonDocument::fromJson(data).object();
        command["senderId"] = senderId;
        Game::pushIncomingCommand(command);
    }
}

void GameServer::readCommand(const QJsonObject &command)
{
    PropertyItem::Id senderId = command["senderId"].toVariant().value<PropertyItem::Id>();
    PlayerItem *player = nullptr;
    switch (command["commandType"].toInt()) {
    case PlayersResetCommand:
    case PlayersInsertCommad:
    case PlayersRemoveCommad:
        break;
    case PlayerUpdateCommand: {
        QJsonObject object = command["value"].toObject();
        player = players()->getPlayer(object["id"].toVariant().value<PropertyItem::Id>());
        break;
    }
    case PlayerSubPropertiesResetCommand:
    case PlayerSubPropertiesInsertCommand:
    case PlayerSubPropertiesRemoveCommand:
    case PlayerSubPropertyUpdateCommand:
        player = players()->getPlayer(command["player"].toVariant().value<PropertyItem::Id>());
        break;
    default:
        break;
    }
    if (player) {
        if (player->writeRights().contains(senderId))
            Game::readCommand(command);
    }
    else {
        Game::readCommand(command);
    }
    sendGame();
}

void GameServer::handleLeavingCommands()
{
    while(!m_leavingCommands.isEmpty()) {
        auto command = m_leavingCommands.dequeue();

        switch (command["commandType"].toInt()) {
        case PlayersResetCommand:
        case PlayersInsertCommad:
        case PlayersRemoveCommad:
        case PlayerUpdateCommand:
        case PlayerSubPropertiesResetCommand:
        case PlayerSubPropertiesInsertCommand:
        case PlayerSubPropertiesRemoveCommand:
        case PlayerSubPropertyUpdateCommand:
            sendGame();
            break;
        default:
            for (int i = 0; i < m_clients.rowCount(); ++i)
                if (m_clients[i].socket)
                    writeCommand(command, *m_clients[i].socket);
            break;
        }
    }
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

    for (int i = 0; i < m_clients.rowCount(); ++i)
        if (m_clients[i].socket)
            m_clients[i].socket->disconnectFromHost();
}

void GameServer::newConnection()
{
    while (m_server.hasPendingConnections()) {
        QTcpSocket *socket = m_server.nextPendingConnection();

        connect(socket, &QTcpSocket::disconnected, this, [this, socket](){
            for(int i = 0; i < m_clients.rowCount(); ++i)
                if(socket == m_clients[i].socket)
                    m_clients.removeAt(i);
        });

        connect(socket, &QTcpSocket::readyRead, this, [this, socket](){
            pushIncomingCommand(*socket);
        });

        ClientItem client;
        client.socket = socket;
        m_clients.append(client);

        sendGame();
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
        QJsonDocument doc(object);
        QTextStream stream(&file);
        stream << doc.toJson();
    }
}

void GameServer::sendGame()
{
    QJsonObject game, command;
    game["name"] = name();
    command["commandType"] = GameResetCommand;

    for (int i = 0; i < m_clients.rowCount(); ++i) {
        if (m_clients[i].socket) {
            ClientItem &client = m_clients[i];
            game["players"] = playersToJson(client.id);
            command["value"] = game;
            writeCommand(command, *client.socket);
        }
    }
}

QJsonArray GameServer::playersToJson(const PropertyItem::Id id) const
{
    QJsonArray array;
    for (int i = 0; i < players()->rowCount(); ++i) {
        PlayerItem *player = qobject_cast<PlayerItem*>(players()->at(i));
        if (player) {
            if (player->readRights().contains(id)) {
                QJsonObject object = player->toJson();
                if (player->writeRights().contains(id))
                    object["editable"] = true;
                else
                    object["editable"] = false;
                array.append(object);
            }
        }
    }
    return array;
}

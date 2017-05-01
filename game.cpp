#include "game.hpp"
#include <QDebug>
#include <QJsonDocument>
#include <QTextStream>

Game::Game(QObject *parent)
    : QObject(parent),
      m_name(""),
      m_players(this),
      m_isReadingCommand(false)
{
    connect(this, &Game::newIncomingCommand, this, &Game::handleIncomingCommands);
    connect(this, &Game::newLeavingCommand, this, &Game::handleLeavingCommands);

    connect(this, &Game::nameChanged, this, [this](){
        QJsonObject command;
        command["commandType"] = GameNameCommand;
        command["value"] = m_name;
        sendCommand(command);
    });

    connect(&m_players, &PlayerModel::modelReset, this, [this](){
        QJsonObject command;
        command["commandType"] = PlayersResetCommand;
        command["value"] = m_players.toJson();
        sendCommand(command);
    });

    connect(&m_players, &PlayerModel::propertyInserted, this, [this](PropertyItem *property){

        PlayerItem *player = qobject_cast<PlayerItem*>(property);

        connect(player->subProperties(), &PropertyModel::modelReset, this, [this, player](){
            QJsonObject command;
            command["commandType"] = PlayerSubPropertiesResetCommand;
            command["player"] = player->id();
            command["value"] = player->subProperties()->toJson();
            sendCommand(command);
        });

        connect(player->subProperties(), &PropertyModel::propertyInserted, this, [this, player](PropertyItem *property){
            QJsonObject command;
            command["commandType"] = PlayerSubPropertiesInsertCommand;
            command["player"] = player->id();
            command["value"] = property->toJson();
            sendCommand(command);
        });

        connect(player->subProperties(), &PropertyModel::propertyRemoved, this, [this, player](const PropertyItem::Id id){
            QJsonObject command;
            command["commandType"] = PlayerSubPropertiesRemoveCommand;
            command["player"] = player->id();
            command["value"] = id;
            sendCommand(command);
        });

        connect(player->subProperties(), &PropertyModel::propertyChanged, this, [this, player](const PropertyItem *property){
            QJsonObject command;
            command["commandType"] = PlayerSubPropertyUpdateCommand;
            command["player"] = player->id();
            command["value"] = property->toJson();
            sendCommand(command);
        });

        QJsonObject command;
        command["commandType"] = PlayersInsertCommad;
        command["value"] = property->toJson(); //with all subProperties
        sendCommand(command);
    });

    connect(&m_players, &PlayerModel::propertyRemoved, this, [this](const PropertyItem::Id id){
        QJsonObject command;
        command["commandType"] = PlayersRemoveCommad;
        command["value"] = id;
        sendCommand(command);
    });

    connect(&m_players, &PlayerModel::propertyChanged, this, [this](const PropertyItem *property){
        QJsonObject command;
        command["commandType"] = PlayerUpdateCommand;
        command["value"] = property->toJson(); //with all subProperties
        sendCommand(command);
    });
}

QString Game::name() const
{
    return m_name;
}

void Game::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

PlayerModel *Game::players()
{
    return &m_players;
}

const PlayerModel *Game::players() const
{
    return &m_players;
}

void Game::pushIncomingCommand(const QJsonObject &command)
{
    m_incomingCommands.enqueue(command);
    emit newIncomingCommand();
}

void Game::pushIncomingCommand(QIODevice &device)
{
    while(device.canReadLine()) {
        QByteArray data = device.readLine();
        qDebug() << "Game::pushIncomingCommand() :" << data;
        pushIncomingCommand(QJsonDocument::fromJson(data).object());
    }
}

void Game::readCommand(const QJsonObject &command)
{
    m_isReadingCommand = true;
    switch (command["commandType"].toInt()) {
    case GameResetCommand:
        fromJson(command["value"].toObject());
        break;
    case GameNameCommand:
        setName(command["value"].toString());
        break;
    case PlayersResetCommand:
        players()->fromJson(command["value"].toArray());
        break;
    case PlayersInsertCommad: {
        QJsonObject player = command["value"].toObject();
        if(players()->get(player["id"].toVariant().value<PropertyItem::Id>()) == nullptr)
            players()->append(player["id"].toVariant().value<PropertyItem::Id>())->fromJson(player);
        break;
    }
    case PlayersRemoveCommad:
        players()->removeOne(command["value"].toVariant().value<PropertyItem::Id>());
        break;
    case PlayerUpdateCommand: {
        QJsonObject player = command["value"].toObject();
        players()->get(player["id"].toVariant().value<PropertyItem::Id>())->fromJson(player);
        break;
    }
    case PlayerSubPropertiesResetCommand: {
        players()->getPlayer(command["player"].toVariant().value<PropertyItem::Id>())->subProperties()->fromJson(command["value"].toArray());
        break;
    }
    case PlayerSubPropertiesInsertCommand: {
        QJsonObject subProperty = command["value"].toObject();
        if(players()->getPlayer(command["player"].toVariant().value<PropertyItem::Id>())->subProperties()->get(subProperty["id"].toVariant().value<PropertyItem::Id>()) == nullptr)
            players()->getPlayer(command["player"].toVariant().value<PropertyItem::Id>())->append(subProperty["id"].toVariant().value<PropertyItem::Id>())->fromJson(subProperty);
        break;
    }
    case PlayerSubPropertiesRemoveCommand: {
        QJsonObject subProperty = command["value"].toObject();
        players()->getPlayer(command["player"].toVariant().value<PropertyItem::Id>())->subProperties()->removeOne(subProperty["id"].toVariant().value<PropertyItem::Id>());
        break;
    }
    case PlayerSubPropertyUpdateCommand: {
        QJsonObject subProperty = command["value"].toObject();
        players()->getPlayer(command["player"].toVariant().value<PropertyItem::Id>())->subProperties()->get(subProperty["id"].toVariant().value<PropertyItem::Id>())->fromJson(subProperty);
        break;
    }
    default:
        break;
    }
    m_isReadingCommand = false;
}

void Game::sendCommand(const QJsonObject &command)
{
    m_leavingCommands.enqueue(command);
    emit newLeavingCommand();
}

void Game::handleIncomingCommands()
{
    while(!m_incomingCommands.isEmpty())
        readCommand(m_incomingCommands.dequeue());
}

void Game::writeCommand(const QJsonObject &command, QIODevice &device)
{
    if(m_isReadingCommand)
        return;
qDebug() << QJsonDocument(command).toJson(QJsonDocument::Compact).append('\n');
    QTextStream stream(&device);
    stream << QJsonDocument(command).toJson(QJsonDocument::Compact).append('\n');
}

QJsonObject Game::toJson() const
{
    QJsonObject obj;
    obj["name"] = m_name;
    obj["players"] = m_players.toJson();
    return obj;
}

void Game::fromJson(const QJsonObject &json)
{
    setName(json["name"].toString());
    m_players.fromJson(json["players"].toArray());
}

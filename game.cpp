#include "game.hpp"
#include <QDebug>
#include <QJsonDocument>

Game::Game(QObject *parent)
    : QObject(parent),
      m_name(""),
      m_players(this)
{
    connect(&m_players, &PlayerModel::modelReset, this, [this](){
        QJsonObject command;
        command["commandType"] = PlayersResetCommand;
        command["value"] = m_players.toJson();
        writeCommand(command);
    });

    connect(&m_players, &PlayerModel::propertyInserted, this, [this](PropertyItem *property){

        PlayerItem *player = qobject_cast<PlayerItem*>(property);

        connect(player->subProperties(), &PropertyModel::modelReset, this, [this, player](){
            QJsonObject command;
            command["commandType"] = PlayerSubPropertiesResetCommand;
            command["player"] = player->id();
            command["value"] = player->subProperties()->toJson();
            writeCommand(command);
        });

        connect(player->subProperties(), &PropertyModel::propertyInserted, this, [this, player](PropertyItem *property){
            QJsonObject command;
            command["commandType"] = PlayerSubPropertiesInsertCommand;
            command["player"] = player->id();
            command["value"] = property->toJson();
            writeCommand(command);
        });

        connect(player->subProperties(), &PropertyModel::propertyRemoved, this, [this, player](const PropertyItem::Id id){
            QJsonObject command;
            command["commandType"] = PlayerSubPropertiesRemoveCommand;
            command["player"] = player->id();
            command["value"] = id;
            writeCommand(command);
        });

        connect(player->subProperties(), &PropertyModel::propertyChanged, this, [this, player](const PropertyItem *property){
            QJsonObject command;
            command["commandType"] = PlayerSubPropertyUpdateCommand;
            command["player"] = player->id();
            command["value"] = property->toJson();
            writeCommand(command);
        });

        QJsonObject command;
        command["commandType"] = PlayersInsertCommad;
        command["value"] = property->toJson(); //with all subProperties
        writeCommand(command);
    });

    connect(&m_players, &PlayerModel::propertyRemoved, this, [this](const PropertyItem::Id id){
        QJsonObject command;
        command["commandType"] = PlayersRemoveCommad;
        command["value"] = id;
        writeCommand(command);
    });

    connect(&m_players, &PlayerModel::propertyChanged, this, [this](const PropertyItem *property){
        QJsonObject command;
        command["commandType"] = PlayerUpdateCommand;
        command["value"] = property->toJson(); //with all subProperties
        writeCommand(command);
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

void Game::readData(QIODevice &device)
{
    while(device.canReadLine()) {
        QByteArray data = device.readLine();
        qDebug() << "Game::readData() :" << data;
        readCommand(QJsonDocument::fromJson(data).object());
    }
}

void Game::readCommand(const QJsonObject &object)
{
    switch (object["commandType"].toInt()) {
    case GameNameCommand:
        setName(object["value"].toString());
        break;
    case PlayersResetCommand:
        players()->fromJson(object["value"].toArray());
        break;
    case PlayersInsertCommad: {
        QJsonObject player = object["value"].toObject();
        if (players()->at(players()->indexOf(player["id"].toVariant().value<PropertyItem::Id>())) == nullptr) {
            PropertyItem *property = players()->append(player["id"].toVariant().value<PropertyItem::Id>());
            property->fromJson(player);
        }
        break;
    }
    case PlayersRemoveCommad:
        players()->removeOne(object["value"].toVariant().value<PropertyItem::Id>());
        break;
    case PlayerUpdateCommand: {
        QJsonObject player = object["value"].toObject();
        PropertyItem *property = players()->at(players()->indexOf(player["id"].toVariant().value<PropertyItem::Id>()));
        property->fromJson(player);
        break;
    }
    case PlayerSubPropertiesResetCommand: {
        QJsonObject obj = object["value"].toObject();
        PropertyItem *property = players()->at(players()->indexOf(object["player"].toVariant().value<PropertyItem::Id>()));
        PlayerItem *player = qobject_cast<PlayerItem*>(property);
        player->subProperties()->fromJson(object["value"].toArray());
        break;
    }
    case PlayerSubPropertiesInsertCommand: {
        QJsonObject obj = object["value"].toObject();
        PropertyItem *property = players()->at(players()->indexOf(object["player"].toVariant().value<PropertyItem::Id>()));
        PlayerItem *player = qobject_cast<PlayerItem*>(property);

        PropertyItem *item = player->append(obj["id"].toVariant().value<PropertyItem::Id>());
        item->fromJson(obj);

        break;
    }
    case PlayerSubPropertiesRemoveCommand: {
        QJsonObject obj = object["value"].toObject();
        PropertyItem *property = players()->at(players()->indexOf(object["player"].toVariant().value<PropertyItem::Id>()));
        PlayerItem *player = qobject_cast<PlayerItem*>(property);

        player->subProperties()->removeOne(obj["id"].toVariant().value<PropertyItem::Id>());

        break;
    }
    case PlayerSubPropertyUpdateCommand: {
        QJsonObject obj = object["value"].toObject();
        PropertyItem *property = players()->at(players()->indexOf(object["player"].toVariant().value<PropertyItem::Id>()));
        PlayerItem *player = qobject_cast<PlayerItem*>(property);

        player->subProperties()->at(player->subProperties()->indexOf(obj["id"].toVariant().value<PropertyItem::Id>()))->fromJson(obj);

        break;
    }
    default:
        break;
    }
}

void Game::writeCommand(const QJsonObject &object)
{
    writeData(QJsonDocument(object).toJson(QJsonDocument::Compact).append('\n'));
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

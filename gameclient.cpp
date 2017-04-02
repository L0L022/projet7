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
        readData(m_socket.readAll());
    });

    connect(&m_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, [this](){
        emit error(m_socket.errorString());
    });

    connect(players(), &PlayerModel::propertyInserted, this, [this](PropertyItem *property){
        QJsonObject command;
        command["commandType"] = PlayersInsertCommad;
        command["value"] = property->toJson();
        writeCommand(command);
    });

    connect(players(), &PlayerModel::propertyRemoved, this, [this](const PropertyItem::Id id){
        QJsonObject command;
        command["commandType"] = PlayersRemoveCommad;
        command["value"] = id;
        writeCommand(command);
    });

    connect(players(), &PlayerModel::propertyChanged, this, [this](const PropertyItem *property){
        QJsonObject command;
        command["commandType"] = PlayersPropertyChangedCommand;
        command["value"] = property->toJson();
        writeCommand(command);
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
    writeCommand(command);
}

QString GameClient::ipAddress() const
{
    return m_socket.peerAddress().toString();
}

quint16 GameClient::port() const
{
    return m_socket.peerPort();
}

void GameClient::writeData(const QByteArray &data)
{
    QTextStream stream(&m_socket);
    stream << data;
}


void GameClient::readCommand(const QJsonObject &object)
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
    case PlayersPropertyChangedCommand: {
        QJsonObject player = object["value"].toObject();
        PropertyItem *property = players()->at(players()->indexOf(player["id"].toVariant().value<PropertyItem::Id>()));
        property->fromJson(player);
        break;
    }
    default:
        break;
    }
}

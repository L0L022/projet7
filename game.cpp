#include "game.hpp"
#include <QDebug>
#include <QJsonDocument>

Game::Game(QObject *parent)
    : QObject(parent),
      m_name(""),
      m_players(this)
{
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

void Game::readData(const QByteArray &data)
{
    qDebug() << "Game::readData() :" << data;
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

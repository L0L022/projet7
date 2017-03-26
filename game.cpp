#include "game.hpp"
#include <QDebug>
#include <QJsonDocument>

Game::Game(QObject *parent) : QObject(parent), _name(""), _players(this)
{
}

QString Game::name() const {
    return _name;
}

void Game::setName(const QString &new_name) {
    _name = new_name;
    emit nameChanged();
}

PlayerModel *Game::players() {
    return &_players;
}

void Game::readData(const QByteArray &data) {
    qDebug() << "Game::readData() :" << data;
}

QJsonObject Game::toJson() const {
    QJsonObject obj;
    obj["name"] = _name;
    obj["players"] = _players.toJson();
    return obj;
}

void Game::fromJson(const QJsonObject &json) {
    setName(json["name"].toString());
    players()->fromJson(json["players"].toArray());
}

void Game::load(const QByteArray &data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(doc.isArray())
        _players.fromJson(doc.array());
}

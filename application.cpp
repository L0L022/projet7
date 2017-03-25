#include "application.hpp"
#include <QDir>
#include <QDebug>
#include <QJsonDocument>

Application::Application(QObject *parent) : QObject(parent), _currentGame(nullptr)
{
}

void Application::startNewGame(const QString &name) {
    closeGame();
    GameServer *game = new GameServer(this);
    _currentGame = game;
    emit currentGameChanged();
}

void Application::loadExistGame(const QHostAddress &address, quint16 port) {
    closeGame();
    GameClient *game = new GameClient(address, port, this);
    _currentGame = game;
    emit currentGameChanged();
}

void Application::closeGame() {
    delete _currentGame;
    _currentGame = nullptr;
    emit currentGameChanged();
}

Game *Application::currentGame() {
    return _currentGame;
}

GameModel *Application::savedGame() {
    return &_savedGame;
}

void Application::refreshSavedGame() {
    _savedGame.clear();
    QDir dir("../projet7");
    for(QFileInfo info : dir.entryInfoList({"*.game"})) {
        QString val;
        QFile file;
        file.setFileName(info.absoluteFilePath());
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

        if(doc.isObject()) {
            QJsonObject obj = doc.object();
            PropertyItem * item = _savedGame.append();
            item->setProperty("name", obj["name"].toVariant());
            item->setProperty("location", info.fileName());
        }
    }
}

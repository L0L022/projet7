#include "application.hpp"
#include <QDir>
#include <QDebug>
#include <QJsonDocument>

Application::Application(QObject *parent)
    : QObject(parent),
      m_currentGame(nullptr),
      m_availableGames(this)
{
}

Game *Application::currentGame()
{
    return m_currentGame;
}

void Application::startNewGame(const QString &fileName)
{
    closeGame();
    GameServer *game = new GameServer(fileName, this);
    setCurrentGame(game);
}

void Application::loadExistGame(const QString &address, quint16 port)
{
    closeGame();
    GameClient *game = new GameClient(address, port, this);
    setCurrentGame(game);
}

void Application::startGame(const int index)
{
    const GameItem &game = m_availableGames.at(index);
    if (game.type() == GameItem::FileGame)
        startNewGame(game.fileName());
    else if (game.type() == GameItem::NetworkGame)
        loadExistGame(game.address(), game.port());
}

void Application::closeGame()
{
    setCurrentGame();
}

GameModel *Application::availableGames()
{
    return &m_availableGames;
}

void Application::refreshAvailableGames()
{
    //à tester
    for (int i = 0; i < m_availableGames.rowCount(); ++i)
        while (m_availableGames.at(i).type() == GameItem::FileGame && i < m_availableGames.rowCount())
            m_availableGames.removeAt(i);

    QDir dir("/tmp");
    for (QFileInfo info : dir.entryInfoList({"*.json"})) {
        QFile file;
        file.setFileName(info.absoluteFilePath());
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            GameItem game(info.absoluteFilePath(), obj["name"].toString());
            m_availableGames.append(game);
        }
    }
}

void Application::say_something(QString blabla)
{
    if (currentGame() != nullptr) {
        currentGame()->writeData(blabla.toUtf8());
    }
}

void Application::setCurrentGame(Game *game)
{
    delete m_currentGame;
    m_currentGame = game;
    emit currentGameChanged();
}

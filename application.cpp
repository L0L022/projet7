#include "application.hpp"
#include "projet7.hpp"
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QNetworkAddressEntry>

Application::Application(QObject *parent)
    : QObject(parent),
      m_currentGame(nullptr),
      m_availableGames(this),
      m_hostFinder(Projet7::portHostFinder, this)
{
    connect(&m_hostFinder, &HostFinder::hostFound, this, &Application::hostFound);
}

Game *Application::currentGame()
{
    return m_currentGame;
}

void Application::newFileGame(const QString &gameName)
{
    loadFileGame(Projet7::instance()->gamesLocation() + "/" + gameName.simplified() + ".json");
    if (m_currentGame)
        m_currentGame->setName(gameName);
}

void Application::loadFileGame(const QString &fileName)
{
    GameServer *game = new GameServer(fileName, this);
    setCurrentGame(game);
}

void Application::loadNetworkGame(const QString &address, quint16 port)
{
    GameClient *game = new GameClient(address, port, this);
    setCurrentGame(game);
}

void Application::loadAvailableGame(const int index)
{
    const GameItem &game = m_availableGames.at(index);
    if (game.type() == GameItem::FileGame)
        loadFileGame(game.fileName());
    else if (game.type() == GameItem::NetworkGame)
        loadNetworkGame(game.address(), game.port());
}

void Application::removeAvailableGame(const int index)
{
    const GameItem &game = m_availableGames.at(index);
    if (game.type() == GameItem::FileGame)
        QFile::remove(game.fileName());
    refreshFileGames();
}

void Application::closeCurrentGame()
{
    setCurrentGame();
}

GameModel *Application::availableGames()
{
    return &m_availableGames;
}

void Application::refreshFileGames()
{
    for (int i = 0; i < m_availableGames.rowCount(); ++i)
        while (i < m_availableGames.rowCount() && m_availableGames.at(i).type() == GameItem::FileGame)
            m_availableGames.removeAt(i);

    QDir dir(Projet7::instance()->gamesLocation());
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

void Application::refreshNetworkGames()
{
    for (int i = 0; i < m_availableGames.rowCount(); ++i)
        while (i < m_availableGames.rowCount() && m_availableGames.at(i).type() == GameItem::NetworkGame)
            m_availableGames.removeAt(i);

    sendPresenceMessage();
}

void Application::setCurrentGame(Game *game)
{
    delete m_currentGame;
    m_currentGame = game;
    emit currentGameChanged();
    sendPresenceMessage();
}

void Application::sendPresenceMessage()
{
    QJsonObject object;
    if (m_currentGame && m_currentGame->type() == Game::ServerGame) {
        object = GameItem(Projet7::instance()->localhostAddresses().first().toString(), m_currentGame->port(), m_currentGame->name()).toJson();
        object["game"] = "server";
    } else {
        object = GameItem(Projet7::instance()->localhostAddresses().first().toString(), 0, "").toJson();
        object["game"] = "client";
    }
    QJsonDocument document(object);
    m_hostFinder.sendMessage(document.toJson());
}

void Application::hostFound(const QHostAddress &hostAddress, const QByteArray &message)
{
    Q_UNUSED(hostAddress)
    QJsonDocument document = QJsonDocument::fromJson(message);
    if (document.isObject()) {
        QJsonObject object(document.object());
        GameItem gameMessage = GameItem::fromJson(object);

        for (int i = 0; i < m_availableGames.rowCount(); ++i) {
            const GameItem &game = m_availableGames.at(i);
            if (game.type() == GameItem::NetworkGame && game.address() == gameMessage.address()) {
                m_availableGames.removeAt(i);
            }
        }

        if (object["game"].toString() == "client") {
            if (m_currentGame && m_currentGame->type() == Game::ServerGame)
                sendPresenceMessage();
        } else if (object["game"].toString() == "server") {
            if (gameMessage.address() != Projet7::instance()->localhostAddresses().first().toString())
                m_availableGames.append(gameMessage);
        }
    }
}

#include "application.hpp"
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QNetworkAddressEntry>

Application::Application(QObject *parent)
    : QObject(parent),
      m_currentGame(nullptr),
      m_availableGames(this),
      m_hostFinder(8888, this),
      m_fileGameDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))
{
    connect(&m_hostFinder, &HostFinder::hostFound, this, &Application::hostFound);
    QDir("/").mkpath(m_fileGameDir);
}

Game *Application::currentGame()
{
    return m_currentGame;
}

void Application::newFileGame(const QString &gameName)
{
    qDebug() << m_fileGameDir;
    loadFileGame(m_fileGameDir + "/" + gameName + ".json");
    if (m_currentGame)
        m_currentGame->setName(gameName);
}

void Application::loadFileGame(const QString &fileName)
{
    closeCurrentGame();
    GameServer *game = new GameServer(fileName, this);
    setCurrentGame(game);
}

void Application::loadNetworkGame(const QString &address, quint16 port)
{
    closeCurrentGame();
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

    QDir dir(m_fileGameDir);
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
    sendPresenceMessage();
}

void Application::sendPresenceMessage()
{
    QJsonObject object;
    if (m_currentGame && m_currentGame->type() == Game::ServerGame) {
        object = GameItem(getMyIp(), m_currentGame->port(), m_currentGame->name()).toJson();
        object["game"] = "server";
    } else {
        object = GameItem(getMyIp(), 0, "").toJson();
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
        //vraiment null
        //object["location"] = hostAddress.toString();
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
            m_availableGames.append(gameMessage);
        }
    }
}

QString Application::getMyIp() const
{
    QString myIp = QHostAddress(QHostAddress::Any).toString();
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (int i = 0; i < interfaces.count(); ++i)
    {
        if (interfaces.at(i).flags() != (QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::IsLoopBack)) {
        QList<QNetworkAddressEntry> entries = interfaces.at(i).addressEntries();
            for (int j = 0; j < entries.count(); ++j)
                    myIp = entries.at(j).ip().toString();
        }
    }
    return myIp;
}

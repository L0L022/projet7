#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "gamemodel.hpp"
#include "hostfinder.hpp"
#include "gameclient.hpp"
#include "gameserver.hpp"

class Application : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Game* currentGame READ currentGame NOTIFY currentGameChanged)

public:    
    explicit Application(QObject *parent = nullptr);

    Game *currentGame();
    Q_INVOKABLE void newFileGame(const QString &gameName);
    Q_INVOKABLE void loadFileGame(const QString &fileName);
    Q_INVOKABLE void loadNetworkGame(const QString &address, quint16 port);
    Q_INVOKABLE void loadAvailableGame(const int index);
    Q_INVOKABLE void removeAvailableGame(const int index);
    Q_INVOKABLE void closeCurrentGame();

    Q_INVOKABLE GameModel *availableGames();
    Q_INVOKABLE void refreshFileGames();
    Q_INVOKABLE void refreshNetworkGames();

signals:
    void userNameChanged();
    void currentGameChanged();

private:
    void setCurrentGame(Game *game = nullptr);
    void sendPresenceMessage();
    void hostFound(const QHostAddress &hostAddress, const QByteArray &message);

    Game *m_currentGame;
    GameModel m_availableGames;
    HostFinder m_hostFinder;
    const QString m_fileGameDir;
};

#endif // APPLICATION_HPP

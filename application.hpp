#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QObject>
#include <QHostAddress>

#include "gamemodel.hpp"
#include "gameclient.hpp"
#include "gameserver.hpp"

class Application : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Game* currentGame READ currentGame NOTIFY currentGameChanged)

public:
    explicit Application(QObject *parent = nullptr);

    Q_INVOKABLE void startNewGame(const QString &name);
    Q_INVOKABLE void loadExistGame(const QHostAddress &address, quint16 port);
    Q_INVOKABLE void closeGame();

    Game *currentGame();

    Q_INVOKABLE GameModel *savedGame();
    Q_INVOKABLE void refreshSavedGame();

signals:
    void currentGameChanged();

private:
    Game *_currentGame;
    GameModel _savedGame;
};

#endif // APPLICATION_HPP

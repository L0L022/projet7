#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "gamemodel.hpp"
#include "gameclient.hpp"
#include "gameserver.hpp"

class Application : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Game* currentGame READ currentGame NOTIFY currentGameChanged)

public:
    explicit Application(QObject *parent = nullptr);

    Q_INVOKABLE void startNewGame(const QString &fileName);
    Q_INVOKABLE void loadExistGame(const QString &address, quint16 port);
    Q_INVOKABLE void closeGame();

    Game *currentGame();

    Q_INVOKABLE GameModel *savedGame();
    Q_INVOKABLE void refreshSavedGame();

    Q_INVOKABLE void say_something(QString blabla); // juste pour le test

signals:
    void currentGameChanged();

private:
    void setCurrentGame(Game *game = nullptr);

    Game *_currentGame;
    GameModel _savedGame;
};

#endif // APPLICATION_HPP

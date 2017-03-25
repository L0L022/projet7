#ifndef GAMECLIENT_HPP
#define GAMECLIENT_HPP

#include <QTcpSocket>

#include "game.hpp"

class GameClient : public Game
{
    Q_OBJECT

    QTcpSocket _socket;
public:
    explicit GameClient(const QHostAddress &address, quint16 port, QObject *parent = nullptr);
    ~GameClient();

    QString location() const;

private:
    void disconnect();
};

#endif // GAMECLIENT_HPP

#ifndef GAMECLIENT_HPP
#define GAMECLIENT_HPP

#include <QTcpSocket>

#include "game.hpp"

class GameClient : public Game
{
    Q_OBJECT

    QTcpSocket _socket;
public:
    explicit GameClient(const QString &address, quint16 port, QObject *parent = nullptr);
    ~GameClient();

    QString ipAddress() const;
    quint16 port() const;

protected:
    void writeData(const QByteArray &data);
};

#endif // GAMECLIENT_HPP

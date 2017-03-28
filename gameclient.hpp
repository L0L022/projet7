#ifndef GAMECLIENT_HPP
#define GAMECLIENT_HPP

#include <QTcpSocket>

#include "game.hpp"

class GameClient : public Game
{
    Q_OBJECT

public:
    explicit GameClient(const QString &address, quint16 port, QObject *parent = nullptr);
    ~GameClient();

    GameType type() const;

    QString ipAddress() const;
    quint16 port() const;

protected:
    void writeData(const QByteArray &data);

private:
    QTcpSocket m_socket;
};

#endif // GAMECLIENT_HPP

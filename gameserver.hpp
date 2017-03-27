#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>

#include "game.hpp"

class GameServer : public Game
{
    Q_OBJECT

public:
    explicit GameServer(const QString &fileName, QObject *parent = nullptr);
    ~GameServer();

    GameType type() const;

    QString ipAddress() const;
    quint16 port() const;

    //GameItem toGameItem() const;

private:
    void openServer();
    void closeServer();
    void newConnection();

    void openFromFile();
    void saveToFile();

    void writeData(const QByteArray &data);

    QString m_fileName;
    QTcpServer m_server;
    QList<QTcpSocket*> m_sockets;
};

#endif // GAMESERVER_HPP

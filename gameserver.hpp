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

protected:
    void writeData(const QByteArray &data);

private:
    void openServer();
    void closeServer();
    void newConnection();

    void openFromFile();
    void saveToFile();


    QString m_fileName;
    QTcpServer m_server;
    QList<QTcpSocket*> m_sockets;
};

#endif // GAMESERVER_HPP

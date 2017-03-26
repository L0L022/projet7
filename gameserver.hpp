#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>

#include "game.hpp"

class GameServer : public Game
{
    Q_OBJECT

    QString _fileName;
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;
public:
    explicit GameServer(const QString &fileName, QObject *parent = nullptr);
    ~GameServer();

    QString ipAddress() const;
    quint16 port() const;

private:
    void openServer();
    void closeServer();
    void newConnection();

    void openFromFile();
    void saveToFile();

    void writeData(const QByteArray &data);
};

#endif // GAMESERVER_HPP

#ifndef GAMECLIENT_HPP
#define GAMECLIENT_HPP

#include <QTcpSocket>

#include "game.hpp"

class GameClient : public Game
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)

public:
    explicit GameClient(const QString &address, quint16 port, QObject *parent = nullptr);
    ~GameClient();

    GameType type() const;

    QString userName() const;
    void setUserName(const QString &userName);

    QString ipAddress() const;
    quint16 port() const;

signals:
    void userNameChanged();

protected:
    void writeData(const QByteArray &data);
    void readCommand(const QJsonObject &object);

private:
    QString m_userName;
    QTcpSocket m_socket;
};

#endif // GAMECLIENT_HPP

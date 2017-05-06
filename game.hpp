#ifndef GAME_HPP
#define GAME_HPP

#include "playermodel.hpp"
#include "gamemodel.hpp"
#include <QAbstractSocket>
#include <QQueue>

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameType type READ type CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString ipAddress READ ipAddress NOTIFY ipAddressChanged)
    Q_PROPERTY(quint16 port READ port NOTIFY portChanged)

public:
    enum GameType {
        ClientGame,
        ServerGame
    };
    Q_ENUM(GameType)

    explicit Game(QObject *parent = nullptr);

    virtual GameType type() const = 0;

    QString name() const;
    void setName(const QString &name);

    virtual QString ipAddress() const = 0;
    virtual quint16 port() const = 0;

    Q_INVOKABLE PlayerModel *players();
    const PlayerModel *players() const;

signals:
    void error(const QString &errorString);

    void newIncomingCommand();
    void newLeavingCommand();

    void nameChanged();
    void ipAddressChanged();
    void portChanged();

protected:
    enum CommandType {
        GameResetCommand,
        GameNameCommand,
        UserNameCommand,

        PlayersResetCommand,
        PlayersInsertCommad,
        PlayersRemoveCommad,
        PlayerUpdateCommand,

        PlayerSubPropertiesResetCommand,
        PlayerSubPropertiesInsertCommand,
        PlayerSubPropertiesRemoveCommand,
        PlayerSubPropertyUpdateCommand
    };
    void pushIncomingCommand(const QJsonObject &command);
    virtual void pushIncomingCommand(QIODevice &device);

    virtual void readCommand(const QJsonObject &command);
    void sendCommand(const QJsonObject &command);
    virtual void handleLeavingCommands() = 0;
    // ou alors un virtual handleLeavingCommand = 0 ET handleLeavingCommandS
    void writeCommand(const QJsonObject &command, QIODevice &device);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    QQueue<QJsonObject> m_leavingCommands;

private:
    void handleIncomingCommands();

    QString m_name;
    PlayerModel m_players;
    bool m_isReadingCommand;
    QQueue<QJsonObject> m_incomingCommands;
};

#endif // GAME_HPP

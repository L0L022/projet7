#ifndef GAME_HPP
#define GAME_HPP

#include "playermodel.hpp"
#include "gamemodel.hpp"
#include <QAbstractSocket>

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

    //virtual GameItem toGameItem() const = 0;

protected:
    void readData(const QByteArray &data);
public: // juste pour le test
    virtual void writeData(const QByteArray &data) = 0;
protected:
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

signals:
    void nameChanged();
    void ipAddressChanged();
    void portChanged();
    void error(const QString &errorString);

private:
    //void load(const QByteArray &data);

    QString m_name;
    PlayerModel m_players;
};

#endif // GAME_HPP

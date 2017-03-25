#ifndef GAME_HPP
#define GAME_HPP

#include "playermodel.hpp"

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString location READ location CONSTANT)

    QString _name;
public:
    explicit Game(QObject *parent = nullptr);
    virtual ~Game();

    QString name() const;
    void setName(const QString &new_name);

    virtual QString location() const;
    Q_INVOKABLE PlayerModel *players();

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

protected:
    PlayerModel _players;

signals:
    void nameChanged();

private:
    void load(const QByteArray &data);
};

#endif // GAME_HPP

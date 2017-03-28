#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <QAbstractListModel>
#include <QJsonObject>

class GameItem
{
public:
    enum GameType {
        FileGame,
        NetworkGame
    };

    GameItem(QString fileName, QString name);
    GameItem(QString address, quint16 port, QString name);

    GameType type() const;
    QString name() const;
    void setName(const QString &name);
    QString location() const;
    QString fileName() const;
    QString address() const;
    quint16 port() const;

    QJsonObject toJson() const;
    static GameItem fromJson(const QJsonObject &object);

    friend bool operator==(const GameItem &l, const GameItem &r);

private:
    GameType m_type;
    QString m_name;
    QString m_location;
    quint16 m_port;
};

class GameModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum GameRoles {
        TypeRole = Qt::UserRole + 1,
        NameRole,
        LocationRole,
        FileNameRole,
        AddressRole,
        PortRole
    };
    Q_ENUM(GameRoles)

    GameModel(QObject *parent = nullptr);

    void append(const GameItem &game);
    void removeAt(const int index);
    void clear();

    const GameItem &at(const int index) const;
    GameItem &operator[](const int index);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<GameItem> m_games;
};

#endif // GAMEMODEL_HPP

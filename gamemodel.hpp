#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <QAbstractListModel>

class GameItem
{
public:
    enum GameType {
        FileGame,
        NetworkGame
    };

    GameItem(QString fileName, QString name);
    GameItem(QString address, quint16 port, QString name);

    QString address() const;

    GameType type() const;
    QString name() const;
    void setName(const QString &name);
    QString location() const;

    quint16 port() const;
    QString fileName() const;

private:
    const GameType m_type;
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
        AddressRole,
        PortRole,
        FileNameRole
    };
    Q_ENUM(GameRoles)

    GameModel(QObject *parent = nullptr);

    void append(const GameItem &game);
    const GameItem &at(const int index) const;
    void clear();
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void removeAt(const int index);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    GameItem &operator[](const int index);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<GameItem> m_games;
};

#endif // GAMEMODEL_HPP

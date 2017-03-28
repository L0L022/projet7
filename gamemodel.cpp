#include "gamemodel.hpp"
#include <QFileInfo>

GameItem::GameItem(QString fileName, QString name)
    : m_type(FileGame),
      m_name(name),
      m_location(fileName),
      m_port(0)
{
}

GameItem::GameItem(QString address, quint16 port, QString name)
    : m_type(NetworkGame),
      m_name(name),
      m_location(address),
      m_port(port)
{
}

GameItem::GameType GameItem::type() const
{
    return m_type;
}

QString GameItem::name() const
{
    return m_name;
}

void GameItem::setName(const QString &name)
{
    m_name = name;
}

QString GameItem::location() const
{
    if (m_type == FileGame)
        return QFileInfo(m_location).fileName();
    else if (m_type == NetworkGame)
        return QString("%1:%2").arg(m_location).arg(m_port);

    return "";
}

QString GameItem::fileName() const
{
    return m_location;
}

QString GameItem::address() const
{
    return m_location;
}

quint16 GameItem::port() const
{
    return m_port;
}

QJsonObject GameItem::toJson() const
{
    QJsonObject object;
    object["type"] = m_type;
    object["name"] = m_name;
    object["location"] = m_location;
    object["port"] = m_port;
    return object;
}

GameItem GameItem::fromJson(const QJsonObject &object)
{
    if (object["type"] == FileGame) {
        return GameItem(object["location"].toString(), object["name"].toString());
    } else if (object["type"] == NetworkGame) {
        return GameItem(object["location"].toString(), object["port"].toInt(), object["name"].toString());
    }
    return GameItem("", "unknown type");
}

bool operator==(const GameItem &l, const GameItem &r)
{
    return l.m_type == r.m_type && l.m_name == r.m_name && l.m_location == r.m_location && l.m_port == r.m_port;
}

GameModel::GameModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void GameModel::append(const GameItem &game)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_games.append(game);
    endInsertRows();
}

void GameModel::removeAt(const int index)
{
    if (0 > index || index > m_games.size())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_games.removeAt(index);
    endRemoveRows();
}

void GameModel::clear()
{
    beginResetModel();
    m_games.clear();
    endResetModel();
}

const GameItem &GameModel::at(const int index) const
{
    return m_games.at(index);
}

GameItem &GameModel::operator[](const int index)
{
    return m_games[index];
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_games.count())
        return QVariant();

    const GameItem &game = m_games.at(index.row());

    if (role == TypeRole)
        return game.type();
    else if (role == NameRole)
        return game.name();
    else if (role == LocationRole)
        return game.location();
    else if (role == FileNameRole)
        return game.fileName();
    else if (role == AddressRole)
        return game.address();
    else if (role == PortRole)
        return game.port();

    return QVariant();
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_games.count();
}

QHash<int, QByteArray> GameModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "typeRole";
    roles[NameRole] = "nameRole";
    roles[LocationRole] = "locationRole";
    roles[FileNameRole] = "fileNameRole";
    roles[AddressRole] = "addressRole";
    roles[PortRole] = "portRole";
    return roles;
}

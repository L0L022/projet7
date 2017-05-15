#include "projet7.hpp"
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QStandardPaths>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

const quint16 Projet7::portGame = 19856, Projet7::portHostFinder = 19857;
Projet7 *Projet7::m_instance = nullptr;

Projet7::Projet7(QObject *parent)
    : QObject(parent),
      m_userName(tr("Unnamed client")),
      m_filesLocation(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)),
      m_localhostAddresses(),
      m_broadcastAddresses(),
      m_gen(),
      m_dis(nullptr)
{
    QDir("/").mkpath(m_filesLocation);

    std::random_device rd;
    m_gen.seed(rd());

    reloadAddresses();
    load();
}

Projet7::~Projet7()
{
    delete m_dis;
    save();
}

Projet7 *Projet7::instance()
{
    if (!m_instance)
        m_instance = new Projet7(QCoreApplication::instance());

    return m_instance;
}

QString Projet7::filesLocation() const
{
    return m_filesLocation;
}

QString Projet7::userName() const
{
    return m_userName;
}

void Projet7::setUserName(const QString &name)
{
    if (m_userName != name) {
        m_userName = name;
        emit userNameChanged();
    }
}

const QList<QHostAddress> &Projet7::localhostAddresses() const
{
    return m_localhostAddresses;
}

const QList<QHostAddress> &Projet7::broadcastAddresses() const
{
    return m_broadcastAddresses;
}

void Projet7::reloadAddresses()
{
    auto flags = (QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::CanBroadcast);
    for (const QNetworkInterface &interface : QNetworkInterface::allInterfaces()) {
        if (flags == (interface.flags() &= flags)) {
            for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
                if (!entry.ip().isNull() && entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                    m_localhostAddresses.append(entry.ip());
                if (!entry.broadcast().isNull() && entry.broadcast().protocol() == QAbstractSocket::IPv4Protocol)
                    m_broadcastAddresses.append(entry.broadcast());
            }
        }
    }
    if (m_localhostAddresses.empty())
        m_localhostAddresses.append(QHostAddress::AnyIPv4);
    if (m_broadcastAddresses.empty())
        m_broadcastAddresses.append(QHostAddress::Broadcast);
    qDebug() << "m_localhostAddresses : " << m_localhostAddresses << " m_broadcastAddresses : " << m_broadcastAddresses;
}

unsigned int Projet7::die(unsigned int nbFace)
{
    if (nbFace < 1)
        return 0;

    if (!m_dis or m_dis->max() != nbFace) {
        delete m_dis;
        m_dis = new std::uniform_int_distribution<unsigned int>(1, nbFace);
    }
    return (*m_dis)(m_gen);
}

void Projet7::save() const
{
    QFile file(m_filesLocation + "/config.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonObject obj;
        obj["userName"] = m_userName;

        QTextStream stream(&file);
        stream << QJsonDocument(obj).toJson();
    }
}

void Projet7::load()
{
    QFile file(m_filesLocation + "/config.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
        if (!obj.isEmpty()) {
            m_userName = obj["userName"].toString();
        }
    }
}

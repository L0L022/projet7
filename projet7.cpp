#include "projet7.hpp"
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QDebug>

const quint16 Projet7::portGame = 19856, Projet7::portHostFinder = 19857;
Projet7 *Projet7::m_instance = nullptr;

Projet7::Projet7(QObject *parent)
    : QObject(parent),
      m_userName(tr("Unnamed client")),
      m_localhostAddresses(),
      m_broadcastAddresses(),
      m_gen(),
      m_dis(nullptr)
{
    std::random_device rd;
    m_gen.seed(rd());

    reloadAddresses();
}

Projet7::~Projet7()
{
    delete m_dis;
}

Projet7 *Projet7::instance()
{
    if (!m_instance)
        m_instance = new Projet7(QCoreApplication::instance());

    return m_instance;
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
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    m_localhostAddresses.append(entry.ip());
                    m_broadcastAddresses.append(entry.broadcast());
                }
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
    if (!m_dis or m_dis->max() != nbFace) {
        delete m_dis;
        m_dis = new std::uniform_int_distribution<unsigned int>(1, nbFace);
    }
    return (*m_dis)(m_gen);
}

#include "hostfinder.hpp"
#include <QNetworkDatagram>
#include <QNetworkAddressEntry>
#include <QDebug>

HostFinder::HostFinder(const quint16 port, QObject *parent)
    : QObject(parent),
      m_socket(this),
      m_broadcastIp(QHostAddress::Any)
{
    connect(&m_socket, &QUdpSocket::readyRead, this, &HostFinder::readMessage);

    connect(&m_socket, static_cast<void (QUdpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, [this](){
        qDebug() << "HostFinder error : " << m_socket.errorString();
    });

    auto flags = (QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::CanBroadcast);
    for (const QNetworkInterface &interface : QNetworkInterface::allInterfaces()) {
        if (flags == (interface.flags() &= flags))
            for(const QNetworkAddressEntry &entry : interface.addressEntries())
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                    m_broadcastIp = entry.broadcast();
    }

    setPort(port);
}

void HostFinder::sendMessage(const QByteArray &message)
{
    m_socket.writeDatagram(message, m_broadcastIp, port());
}

quint16 HostFinder::port() const
{
    return m_socket.localPort();
}

void HostFinder::setPort(const quint16 port)
{
    m_socket.bind(port, QAbstractSocket::ShareAddress);
    emit portChanged();
}

void HostFinder::readMessage()
{
    while (m_socket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket.receiveDatagram();
        emit hostFound(datagram.senderAddress(), datagram.data());
    }
}

#include "hostfinder.hpp"
#include <QNetworkDatagram>
#include <QDebug>

HostFinder::HostFinder(const quint16 port, QObject *parent)
    : QObject(parent),
      m_socket(this)
{
    connect(&m_socket, &QUdpSocket::readyRead, this, &HostFinder::readMessage);
    setPort(port);
}

void HostFinder::sendMessage(const QByteArray &message)
{
    m_socket.writeDatagram(message, QHostAddress::Broadcast, port());
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

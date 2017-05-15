#include "hostfinder.hpp"
#include "projet7.hpp"
#include <QNetworkDatagram>

HostFinder::HostFinder(const quint16 port, QObject *parent)
    : QObject(parent),
      m_socket(this)
{
    connect(&m_socket, &QUdpSocket::readyRead, this, &HostFinder::readMessage);

    connect(&m_socket, static_cast<void (QUdpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, [this](){
        qDebug() << "HostFinder error : " << m_socket.errorString();
    });

    setPort(port);
}

void HostFinder::sendMessage(const QByteArray &message)
{
    for(const QHostAddress &address : Projet7::instance()->broadcastAddresses())
        m_socket.writeDatagram(message, address, port());
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

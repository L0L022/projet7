#ifndef HOSTFINDER_HPP
#define HOSTFINDER_HPP

#include <QObject>
#include <QUdpSocket>

class HostFinder : public QObject
{
    Q_OBJECT

public:
    explicit HostFinder(const quint16 port, QObject *parent = 0);

    void sendMessage(const QByteArray &message);

    quint16 port() const;
    void setPort(const quint16 port);

signals:
    void hostFound(const QHostAddress &hostAddress, const QByteArray &message);

    void portChanged();

private:
    void readMessage();

    QUdpSocket m_socket;
    QHostAddress m_broadcastIp;
};

#endif // HOSTFINDER_HPP

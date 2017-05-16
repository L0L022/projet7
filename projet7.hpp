#ifndef PROJET7_HPP
#define PROJET7_HPP

#include <random>

#include <QObject>
#include <QHostAddress>

class Projet7 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 portGame MEMBER portGame CONSTANT)
    Q_PROPERTY(quint16 portHostFinder MEMBER portHostFinder CONSTANT)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString configLocation READ configLocation CONSTANT)
    Q_PROPERTY(QString gamesLocation READ gamesLocation CONSTANT)

    explicit Projet7(QObject *parent = 0);

public:
    ~Projet7();

    static Projet7 *instance();

    QString userName() const;
    void setUserName(const QString &name);

    QString configLocation() const;
    QString gamesLocation() const;

    const QList<QHostAddress> &localhostAddresses() const;
    const QList<QHostAddress> &broadcastAddresses() const;
    void reloadAddresses();

    Q_INVOKABLE unsigned int die(unsigned int nbFace = 6);

    void save() const;
    void load();

public:
    static const quint16 portGame, portHostFinder;

signals:
    void userNameChanged();

private:
    static Projet7 *m_instance;

    QString m_userName;
    QString m_configLocation;
    QString m_gamesLocation;

    QList<QHostAddress> m_localhostAddresses;
    QList<QHostAddress> m_broadcastAddresses;

    std::mt19937 m_gen;
    std::uniform_int_distribution<unsigned int> *m_dis;
};

#endif // PROJET7_HPP

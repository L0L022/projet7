#ifndef PROJET7_HPP
#define PROJET7_HPP

#include <random>

#include <QObject>

class Projet7 : public QObject
{
    Q_OBJECT
    explicit Projet7(QObject *parent = 0);

public:
    ~Projet7();

    static Projet7 *instance();

    Q_INVOKABLE unsigned int die(size_t nbFace = 6);

private:
    static Projet7 *m_instance;

    std::mt19937 m_gen;
    std::uniform_int_distribution<unsigned int> *m_dis;
};

#endif // PROJET7_HPP

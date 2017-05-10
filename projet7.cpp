#include "projet7.hpp"
#include <QCoreApplication>

Projet7 *Projet7::m_instance = nullptr;

Projet7::Projet7(QObject *parent)
    : QObject(parent), m_gen(), m_dis(nullptr)
{
    std::random_device rd;
    m_gen.seed(rd());
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

unsigned int Projet7::die(size_t nbFace)
{
    if (!m_dis or m_dis->max() != nbFace) {
        delete m_dis;
        m_dis = new std::uniform_int_distribution<unsigned int>(1, nbFace);
    }
    return (*m_dis)(m_gen);
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "projet7.hpp"
#include "application.hpp"
#include "playermodel.hpp"

#include "game.hpp"
#include "gameclient.hpp"
#include "gameserver.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>

#include <iostream>
using namespace std;

static QObject *projet7_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return Projet7::instance();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<Projet7>("Projet7", 1, 0, "Projet7", projet7_provider);
    qmlRegisterType<Application>("Projet7", 1, 0, "Application");

    qmlRegisterUncreatableType<GameItem>("Projet7", 1, 0, "GameItem", "Access to enum only");
    qmlRegisterType<GameModel>("Projet7", 1, 0, "GameModel");

    qmlRegisterUncreatableType<Game>("Projet7", 1, 0, "Game", "Use Application");
    qmlRegisterUncreatableType<GameClient>("Projet7", 1, 0, "GameClient", "Use Application");
    qmlRegisterUncreatableType<GameServer>("Projet7", 1, 0, "GameServer", "Use Application");

    qmlRegisterType<ClientModel>("Projet7", 1, 0, "ClientModel");

    qmlRegisterType<PropertyItem>("Projet7", 1, 0, "PropertyItem");
    qRegisterMetaType<PropertyItem::Id>("Id");
    qmlRegisterType<PropertyModel>("Projet7", 1, 0, "PropertyModel");
    qmlRegisterType<PropertyFilterModel>("Projet7", 1, 0, "PropertyFilterModel");

    qmlRegisterType<PlayerItem>("Projet7", 1, 0, "PlayerItem");
    qRegisterMetaType<PlayerItem::Rights>("Rights");
    qmlRegisterType<PlayerModel>("Projet7", 1, 0, "PlayerModel");

    QVariant characters, factions;
    QFile file(":/Univers/characters.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        characters = QJsonDocument::fromJson(file.readAll()).array().toVariantList();
    }
    file.close();
    file.setFileName(":/Univers/factions.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        factions = QJsonDocument::fromJson(file.readAll()).array().toVariantList();
    }
    file.close();

    Application mon_app;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app", &mon_app);
    engine.rootContext()->setContextProperty("characters", characters);
    engine.rootContext()->setContextProperty("factions", factions);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "application.hpp"
#include "playermodel.hpp"
#include "playeradditionmodel.hpp"

#include "game.hpp"
#include "gameclient.hpp"
#include "gameserver.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Application>("Projet7", 1, 0, "Application");

    qmlRegisterType<GameModel>("Projet7", 1, 0, "GameModel");

    qmlRegisterUncreatableType<Game>("Projet7", 1, 0, "Game", "Use Application");
    qmlRegisterUncreatableType<GameClient>("Projet7", 1, 0, "GameClient", "Use Application");
    qmlRegisterUncreatableType<GameServer>("Projet7", 1, 0, "GameServer", "Use Application");

    qmlRegisterType<PropertyItem>("Projet7", 1, 0, "PropertyItem");
    qmlRegisterType<PropertyModel>("Projet7", 1, 0, "PropertyModel");
    qmlRegisterType<PropertyFilterModel>("Projet7", 1, 0, "PropertyFilterModel");

    qmlRegisterType<PlayerItem>("Projet7", 1, 0, "PlayerItem");
    qmlRegisterType<PlayerModel>("Projet7", 1, 0, "PlayerModel");

    qmlRegisterType<PlayerAdditionItem>("Projet7", 1, 0, "PlayerAdditionItem");
    qmlRegisterType<PlayerAdditionModel>("Projet7", 1, 0, "PlayerAdditionModel");

    Application mon_app;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app", &mon_app);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

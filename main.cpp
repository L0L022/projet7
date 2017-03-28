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

    qmlRegisterType<Application>("me", 1, 0, "Application");

    qmlRegisterType<GameModel>("me", 1, 0, "GameModel");

    qmlRegisterUncreatableType<Game>("me", 1, 0, "Game", "Use Application");
    qmlRegisterUncreatableType<GameClient>("me", 1, 0, "GameClient", "Use Application");
    qmlRegisterUncreatableType<GameServer>("me", 1, 0, "GameServer", "Use Application");

    qmlRegisterType<PropertyItem>("me", 1, 0, "PropertyItem");
    qmlRegisterType<PropertyModel>("me", 1, 0, "PropertyModel");
    qmlRegisterType<PropertyFilterModel>("me", 1, 0, "PropertyFilterModel");

    qmlRegisterType<PlayerItem>("me", 1, 0, "PlayerItem");
    qmlRegisterType<PlayerModel>("me", 1, 0, "PlayerModel");

    qmlRegisterType<PlayerAdditionItem>("me", 1, 0, "PlayerAdditionItem");
    qmlRegisterType<PlayerAdditionModel>("me", 1, 0, "PlayerAdditionModel"); 

    Application mon_app;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app", &mon_app);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "application.hpp"
#include "playermodel.hpp"
#include "playeradditionmodel.hpp"
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
    qmlRegisterType<PlayerAdditionModel>("me", 1, 0, "PlayerAdditionModel");
    qmlRegisterType<PlayerItem>("me", 1, 0, "PlayerItem");
    qmlRegisterType<PropertyItem>("me", 1, 0, "PropertyItem");
    qmlRegisterType<PropertyModel>("me", 1, 0, "PropertyModel");
    qmlRegisterType<PlayerAdditionItem>("me", 1, 0, "PlayerAdditionItem");
    qmlRegisterType<PropertyFilterModel>("me", 1, 0, "PropertyFilterModel");

    QString val;
    QFile file;
    file.setFileName("../projet7/players.json");
    //file.setFileName(":/players.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

    PlayerModel model;
    model.fromJson(doc.array());

    app.connect(&app, &QGuiApplication::aboutToQuit, [&model](){
        QJsonDocument doc(model.toJson());
        QFile file;
        file.setFileName("../projet7/players.json");
        //file.setFileName(":/players.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream data(&file);
        data << doc.toJson();
        file.close();
    });

    Application mon_app;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("players", &model);
    engine.rootContext()->setContextProperty("app", &mon_app);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

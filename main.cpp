#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "playermodel.hpp"
#include "playeradditionmodel.hpp"
#include <QSortFilterProxyModel>
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

    qmlRegisterType<PlayerAdditionModel>("me", 1, 0, "PlayerAdditionModel");
    qmlRegisterType<PlayerItem>("me", 1, 0, "PlayerItem");
    qmlRegisterType<PlayerAdditionItem>("me", 1, 0, "PlayerAdditionItem");
    qmlRegisterType<QSortFilterProxyModel>("me", 1, 0, "QSortFilterProxyModel");

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

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("players", &model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

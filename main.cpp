#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "playermodel.hpp"
#include "playeradditionmodel.hpp"
#include <QJsonArray>
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
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream data(&file);
        data << doc.toJson();
        file.close();
    });

    /*
    PlayerItem * loic = model.addPlayer(),
               * alex = model.addPlayer(),
               * hugo = model.addPlayer();

    loic->setProperty("name", "Loïc");
    loic->setProperty("age", 32);
    loic->setProperty("job", "Charboonneur");
    PlayerAdditionModel* loic_add = loic->getAdditions();
    PlayerAdditionItem* loic_add_1 = loic_add->addAddition();
    loic_add_1->setProperty("name", "peluche");
    loic_add_1->setProperty("description", "fait jolie");
    loic_add_1->setProperty("CC", 10);
    loic_add_1->setProperty("category", "characteristic");
    PlayerAdditionItem* loic_add_2 = loic_add->addAddition();
    loic_add_2->setProperty("name", "hache");
    loic_add_2->setProperty("description", "pour tuer des gens");
    loic_add_2->setProperty("category", "skill");

    alex->setProperty("name", "Alexandre");
    alex->setProperty("age", 20);
    alex->setProperty("job", "Dancer");
    PlayerAdditionModel* alex_add = alex->getAdditions();
    for(int i = 0; i < 10; ++i) {
        PlayerAdditionItem * alex_add_item = alex_add->addAddition();
        alex_add_item->setProperty("name", "Nom !!!");
        alex_add_item->setProperty("description", "Je suis la description !!!");
        if(i > 6)
            alex_add_item->setProperty("category", "skill");
        else
            alex_add_item->setProperty("category", "characteristic");
    }

    hugo->setProperty("name", "Hugo");
    hugo->setProperty("age", 7);
    hugo->setProperty("job", "Singer");
*/
    //cout << QJsonDocument(model.toJson()).toJson().toStdString() << endl;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("players", &model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

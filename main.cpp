#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "playermodel.hpp"
#include "playeradditionmodel.hpp"
#include <QJsonArray>

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

    PlayerModel model;
    PlayerItem * loic = model.addPlayer(),
               * alex = model.addPlayer(),
               * hugo = model.addPlayer();

    loic->setProperty("name", "Loïc");
    loic->setProperty("age", 32);
    loic->setProperty("job", "Charboonneur");
    PlayerAdditionModel* loic_add = qobject_cast<PlayerAdditionModel*>(loic->getAdditions());
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
    PlayerAdditionModel* alex_add = qobject_cast<PlayerAdditionModel*>(alex->getAdditions());
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
/*
    model.addProperty(0, "name", "Loïc");
    model.addProperty(0, "age", 10);
    model.addProperty(1, "name", "Alexandre");
    model.addProperty(1, "age", 30);
    model.addProperty(2, "name", "Hugo");
    model.addProperty(2, "age", 30);
*/
    QJsonArray players;
    for(int i = 0; i<10; ++i) {
        QJsonObject player;
        for(const QString &str : {"name", "calling"})
            player[str] = "player_name";
        for(const QString &nb : {"age", "height", "CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
            player[nb] = 10;
        QJsonArray additions;
        for(int i = 0; i<10; ++i) {
            QJsonObject addition;
            for(const QString &str : {"name", "description", "category"})
                addition[str] = "add_name";
            for(const QString &nb : {"CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
                addition[nb] = 50;
            additions.append(addition);
        }
        player["additions"] = additions;
        players.append(player);
        //cout << QJsonDocument(player).toJson().toStdString() << endl;
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("players", &model);
    engine.rootContext()->setContextProperty("myjson", players);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

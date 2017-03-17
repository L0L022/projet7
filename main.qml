import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

import me 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")    

    TabView {
        id: view
        currentIndex: 1
        anchors.fill: parent

        Repeater {
            model: players
            delegate: Tab {
                title: properties.name
                NewPlayerView {
                    anchors.fill: parent
                }
            }
        }
    }

/*
    TabView {
        id: view

        currentIndex: 1
        anchors.fill: parent

        Repeater {
            model: players
            delegate: Tab {
                title: id
                Column {
                    Text { text: properties.name }
                    SpinBox {
                        value: player.getProperty("age")
                        editable: true
                    }
                    Text { text: properties.job }
                    Repeater {
                        model: additions
                        delegate: Text {
                            text: id + " " + properties.name + " " + properties.description
                        }
                    }

                    Button {
                        text: "Valider"
                        onClicked: {
                            players.getPlayer(id).setProperty("age", 99);
                            players.getPlayer(id).setProperty("name", "NOM CHANGÉ");
                            player.setProperty("job", "nothing");
                        }
                    }
                }
            }
        }
    }*/
/*
    TabView {
        id: view

        currentIndex: 1
        anchors.fill: parent

        Repeater {
            model: myjson
            delegate: Tab { NewPlayerView {} }
        }
    }
*/
/*
    GridView {
        width: 640
        height: 434
        clip: true

        cellWidth: 400; cellHeight: 200
        model: myjson
        delegate: Column {
            Label { text: modelData.name }

            GridView {
        width: 300
        height: 300
        clip: true

        cellWidth: 400; cellHeight: 200
        model: modelData.additions
        delegate: Row {
            Label { text: "addition" }
            Label { text: modelData.name }
            Label { text: modelData.CC }
            Label { text: modelData.CT }
            Label { text: modelData.F }
            Label { text: modelData.B }
            Label { text: modelData.A }
            Label { text: modelData.I }
        }
            }
    }
    }*/
/*
    GridView {
        width: 640
        height: 434
        clip: true

        cellWidth: 400; cellHeight: 200
        model: playerModel
        delegate: PlayerView {}
    }

    Button {
        id: button
        y: 362
        text: qsTr("Button")
        onClicked: playerModel.addPlayer();
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }
    */
}

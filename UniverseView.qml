import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    objectName: "UniverseView"
    readonly property string title: qsTr("Choose a character")

    function getFactionIndex(id) {
        for (var i = 0; i < factions.length; ++i)
            if (factions[i].id === id)
                return i;
        return -1;
    }

    Component {
        id: swipeview

        Item {
            id: swipeitem
            property string title
            property alias model: repeater.model
            property Component delegate
            property alias currentIndex: swipe.currentIndex

            SwipeView {
                id: swipe
                anchors.fill: parent
                clip: true

                Repeater {
                    id: repeater
                    delegate: Loader {
                        id: loader
                        property int modelIndex: index
                        active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                        sourceComponent: swipeitem.delegate
                    }
                }
            }

            PageIndicator {
                 count: swipe.count
                 currentIndex: swipe.currentIndex
                 anchors.bottom: swipe.bottom
                 anchors.horizontalCenter: parent.horizontalCenter
             }
        }
    }

    Component {
        id: characterDelegate

        CharacterDelegate {
            character: characters[modelIndex]
            faction: factions[getFactionIndex(character.faction)]
        }
    }

    Component {
        id: factionDelegate

        FactionDelegate {
            faction: factions[modelIndex]
        }
    }

    ListView {
        anchors.fill: parent
        model: ListModel {
            Component.onCompleted: {
                for (var i = 0; i < characters.length; ++i)
                    append(characters[i]);
            }
        }

        section.property: "faction"
        section.delegate: ItemDelegate {
            width: parent.width
            font.bold: true
            font.italic: true
            text: factions[section].name
            onClicked: stack.push(swipeview, {"title": qsTr("Factions"), "model": factions, "delegate": factionDelegate, "currentIndex": section})
        }

        delegate: ItemDelegate {
            width: parent.width
            text: name
            onClicked: stack.push(swipeview, {"title": qsTr("Characters"), "model": characters, "delegate": characterDelegate, "currentIndex": index})
        }
    }
}

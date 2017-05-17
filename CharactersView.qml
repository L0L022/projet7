import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    readonly property string title: qsTr("Characters")
    property int faction

    SwipeView {
        anchors.fill: parent

        Repeater {
            id: repeater
            model: 3
            delegate: Loader {
                property int faction: faction
                active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                source: "CharacterDelegate.qml"
            }
        }
    }
}

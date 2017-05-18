import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    objectName: "FactionsView"
    readonly property string title: qsTr("Factions")

    SwipeView {
        id: view
        anchors.fill: parent

        Repeater {
            model: Projet7.factions
            delegate: Loader {
                property int modelIndex: index
                active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                source: "FactionDelegate.qml"
            }
        }
    }

    PageIndicator {
        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    property var faction

    GridLayout {
        anchors.fill: parent

        Image {
            Layout.row: 0
            Layout.column: 0
            Layout.rowSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: faction.imageRole
            fillMode: Image.PreserveAspectFit
        }

        Label {
            Layout.row: 0
            Layout.column: 1
            text: faction.nameRole
        }

        Label {
            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 2
            text: faction.descriptionRole
        }
    }
}

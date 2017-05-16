import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Flickable {
    id: item
    contentHeight: layout.implicitHeight
    property var faction

    GridLayout {
        id: layout
        width: item.width

        Image {
            Layout.row: 0
            Layout.column: 0
            Layout.rowSpan: 2
            Layout.fillHeight: true
            source: faction.image
            fillMode: Image.PreserveAspectFit
        }

        Label {
            Layout.row: 0
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: faction.name
        }

        Label {
            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 2
            Layout.fillWidth: true
            text: faction.description
            wrapMode: Text.Wrap
        }
    }
}

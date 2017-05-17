import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    readonly property string title: qsTr("Rolling dice")

    Component {
        id: die

        Rectangle {
            width: grid.cellWidth - 5
            height: grid.cellHeight - 5
            color: "transparent"
            border.color: "white"
            border.width: 5
            radius: 10

            Label {
                anchors.fill: parent
                text: modelData
                font.pointSize: 400
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                fontSizeMode: Text.Fit
            }
        }
    }

    ListModel {
        id: results
    }

    ColumnLayout {
        anchors.fill: parent

        GridView {
            id: grid
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: results
            delegate: die
            clip: true
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Number of faces")
            }

            SpinBox {
                id: nbFace
                value: 6
                editable: true
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Number of dice")
            }

            SpinBox {
                id: nbDie
                from: 1
                value: 1
                editable: true
            }
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Roll the dice !")
            onClicked: {
                results.clear()
                for (var i = 0; i < nbDie.value; ++i)
                    results.append({"value": Projet7.die(nbFace.value)})
            }
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Item {
    id: item1
    ColumnLayout {
        id: superColumn
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        RowLayout {
            Layout.fillWidth: true
            Rectangle {
                id: rectangle
                width: 275
                height: 53
                Layout.fillWidth: true

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 6

                    Label {
                        text: qsTr("Nom :")
                    }

                    TextField {
                        text: properties.name
                        onAccepted: player.setProperty("name", text)
                        Layout.fillWidth: true
                    }
                }

            }
            Rectangle {
                id: rectangle1
                width: 275
                height: 53
                Layout.fillWidth: true

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 6

                    Label {
                        text: qsTr("Age :")
                    }

                    TextField {
                        text: properties.age
                        onAccepted: player.setProperty("age", text)
                        Layout.fillWidth: true
                    }
                }
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Rectangle {
                width: 275
                height: 53
                Layout.fillWidth: true
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 6

                    Label {
                        text: qsTr("Vocation :")
                    }

                    TextField {
                        text: properties.calling
                        onAccepted: player.setProperty("calling", text)
                        Layout.fillWidth: true
                    }
                }
            }

            Rectangle {
                width: 275
                height: 53
                Layout.fillWidth: true

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 6

                    Label {
                        text: qsTr("Taille :")
                    }

                    TextField {
                        text: properties.height
                        onAccepted: player.setProperty("height", text)
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
    GroupBox {
        id: groupBox
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: superColumn.bottom
        anchors.topMargin: 6
        title: qsTr("Caracteristique")
        height: 200

        Row {
            id: rowText
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            Repeater {
                model: ["CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"]
                delegate: Text {
                    text: modelData
                    horizontalAlignment: Text.AlignHCenter
                    width: 50
                }
            }

        }

        ListView {
            clip: true
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: rowText.bottom
            model: QSortFilterProxyModel {
                sourceModel: additions
                filterRole: PlayerAdditionModel.CategoryRole
                filterRegExp: /characteristic/i
            }

            delegate: Row {
                Repeater {
                    model: ["CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"]
                    delegate: TextField {
                        id: superTextField
                        text: properties[modelData]
                        onAccepted: {
                            console.log(addition)
                            addition.setProperty(modelData, text)
                        }
                        width: 50

                        ToolTip {
                            parent: superTextField
                            visible: superTextField.activeFocus
                            text: "Nom : " + properties.name + "\nDescription : " + properties.description
                        }
                    }
                }
            }
        }
    }

    GroupBox {
        id: groupBox1
        anchors.bottom: rowLayout.top
        anchors.bottomMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: groupBox.bottom
        anchors.topMargin: 6
        title: qsTr("Toutes les stats")

        ListView {
            clip: true
            anchors.fill: parent
            model: additions
            delegate: Row {
                Repeater {
                    model: ["id", "name", "description"]
                    delegate: TextField {
                        text: properties[modelData]
                        onAccepted: addition.setProperty(modelData, text)
                        ToolTip.text: modelData
                    }
                }
            }
        }
    }

    Row {
        id: rowLayout
        height: 47
        spacing: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8

        Button {
            id: button
            text: qsTr("Add Addition")
            onClicked: additions.addAddition()
        }

        Button {
            id: button1
            text: qsTr("Remove Addition")
        }
    }

}

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Item {

    Rectangle {
        id: rectangle
        x: 23
        y: 25
        width: 275
        height: 53
        border.width: 2

        RowLayout {
            id: rowLayout
            anchors.leftMargin: 6
            anchors.rightMargin: 6
            anchors.fill: parent

            Label {
                id: label
                text: qsTr("Nom :")
            }

            TextField {
                id: textField
                text: properties.name
                onAccepted: player.setProperty("name", text)
                Layout.fillWidth: true
            }
        }

    }

    Rectangle {
        id: rectangle1
        x: 23
        y: 84
        width: 275
        height: 53
        RowLayout {
            id: rowLayout1
            anchors.fill: parent
            Label {
                id: label1
                text: qsTr("Age :")
            }

            TextField {
                id: textField4
                text: properties.age
                onAccepted: player.setProperty("age", text)
                Layout.fillWidth: true
            }
        }
    }

    Rectangle {
        id: rectangle2
        x: 337
        y: 25
        width: 275
        height: 53
        RowLayout {
            id: rowLayout2
            anchors.fill: parent
            Label {
                id: label2
                text: qsTr("Vocation :")
            }

            TextField {
                id: textField1
                text: properties.calling
                onAccepted: player.setProperty("calling", text)
                Layout.fillWidth: true
            }
        }
    }

    Rectangle {
        id: rectangle3
        x: 337
        y: 84
        width: 275
        height: 53
        RowLayout {
            id: rowLayout3
            anchors.fill: parent
            Label {
                id: label3
                text: qsTr("Taille :")
            }

            TextField {
                id: textField2
                text: properties.height
                onAccepted: player.setProperty("height", text)
                Layout.fillWidth: true
            }
        }
    }

    GroupBox {
        id: groupBox
        x: 23
        y: 143
        width: 589
        height: 198
        title: qsTr("Caracteristique")

        ListView {
            anchors.fill: parent
            model: QSortFilterProxyModel {
                sourceModel: additions
                filterRole: PlayerAdditionModel.CategoryRole
                filterRegExp: /characteristic/i
            }

            delegate: Row {
                Repeater {
                    model: ["id", "name", "description", "CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"]
                    delegate: TextField {
                        text: properties[modelData]
                        onAccepted: {
                            console.log(addition)
                            addition.setProperty(modelData, text)
                        }
                        width: 50
                        ToolTip.text: modelData
                    }
                }
            }
        }

/*
        TableView {
            id: supertable
            anchors.fill: parent
            model: additions
            itemDelegate: Item {
                SpinBox {
                    id: superspin
                    value: styleData.value
                    visible: styleData.selected
                    onEditingFinished: {
                        if(modelData[supertable.getColumn(styleData.column).role] !== value) {
                            modelData[supertable.getColumn(styleData.column).role] = value;
                            supertable.selection.clear();
                        }
                    }
                }
                Text {
                    visible: !styleData.selected
                    text: {
                        superspin.value
                    }
                }
            }
            TableViewColumn { role: "id"; title: "id"; width: 60 }
            TableViewColumn { role: "properties.CC"; title: "CC"; width: 60 }
            TableViewColumn { role: "CT"; title: "CT"; width: 60 }
            TableViewColumn { role: "F"; title: "F"; width: 60 }
            TableViewColumn { role: "B"; title: "B"; width: 60 }
            TableViewColumn { role: "A"; title: "A"; width: 60 }
            TableViewColumn { role: "I"; title: "I"; width: 60 }
            TableViewColumn { role: "Desc"; title: "Desc"; width: 60 }
            TableViewColumn { role: "Int"; title: "Int"; width: 60 }
            TableViewColumn { role: "Soc"; title: "Soc"; width: 60 }
            TableViewColumn { role: "FM"; title: "FM"; width: 60 }
        }
*/
        /*

        ListView {
            id: gridView
            anchors.fill: parent
            model: modelData.additions
            clip: true
            delegate: Rectangle {
                height: 50
                width: view.width
                border.color: "#000000"

                Row {
                    spacing: 4
                    Label { text: modelData.CC }
                    Text { text: modelData.CT }
                    Text { text: modelData.F }
                    Text { text: modelData.B }
                    Text { text: modelData.A }
                    Text { text: modelData.I }
                    Text { text: modelData.Desc }
                    Text { text: modelData.Int }
                    Text { text: modelData.Soc }
                }

                MouseArea {
                    id: mouse
                    anchors.fill: parent
                }

                ToolTip {
                    text: modelData.name
                    visible: mouse.containsMouse
                }
            }
        }*/
    }

    GroupBox {
        id: groupBox1
        x: 23
        y: 347
        width: 589
        height: 125
        title: qsTr("Competences")

        ListView {
            anchors.fill: parent
            model: QSortFilterProxyModel {
                sourceModel: additions
                filterRole: PlayerAdditionModel.CategoryRole
                filterRegExp: /skill/i
            }
            delegate: Row {
                Repeater {
                    model: ["id", "name", "description"]
                    delegate: TextField {
                        text: properties[modelData]
                        onAccepted: {
                            console.log(addition)
                            addition.setProperty(modelData, text)
                        }
                        width: 50
                        ToolTip.text: modelData
                    }
                }
            }
        }
    }

}

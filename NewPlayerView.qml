import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Item {
    id: item1

    EditProperties {
        id: superedit
    }

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

            SuperSaisi {
                key: "name"
                key_name: "Nom"
            }
            SuperSaisi {
                key: "age"
                key_name: "Age"
            }
        }
        RowLayout {
            Layout.fillWidth: true

            SuperSaisi {
                key: "calling"
                key_name: "Vocation"
            }
            SuperSaisi {
                key: "height"
                key_name: "Taille"
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
                sourceModel: additions_role
                filterRole: PlayerAdditionModel.CategoryRole
                filterRegExp: /characteristic/i
            }

            delegate: Row {
                Repeater {
                    model: ["CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"]
                    delegate: TextField {
                        id: salut

                        HelpProperties {
                            id: superhelp1
                            propertyKey: modelData
                        }

                        text: superhelp1.inputValue
                        onTextChanged: superhelp1.inputValue = text
                        color: text === superhelp1.propertyValue ? "green" : "orange"
                        onAccepted: superhelp1.set()
                        ToolTip.text: modelData

                        ToolTip {
                            parent: salut
                            visible: salut.activeFocus
                            text: "Nom : " + properties_role.name + "\nDescription : " + properties_role.description
                        }
                    }

                        /*TextField {
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
                    }*/
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
            model: additions_role
            delegate: Row {
                Repeater {
                    model: ["id", "name", "description"]
                    delegate: TextField {

                        HelpProperties {
                            id: superhelp
                            propertyKey: modelData
                        }

                        text: superhelp.inputValue
                        onTextChanged: superhelp.inputValue = text
                        color: text === superhelp.propertyValue ? "green" : "orange"
                        onAccepted: superhelp.set()
                        ToolTip.text: modelData

                        Button {
                            text: "reset"
                            onClicked: superhelp.reset()
                        }

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
            text: "edit"
            onClicked: superedit.open()
        }
    }

}

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Item {
    id: item1

    ColumnLayout {
        id: superColumn
        anchors.fill: parent
        anchors.margins: 6

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

        GroupBox {
            id: groupBox
            title: qsTr("Caractéristiques")
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent

                Row {
                    id: rowText

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
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip: true

                    model: item_role.additions()
                    /*QSortFilterProxyModel {
                        sourceModel: additions_role
                        filterRole: PlayerAdditionModel.CategoryRole
                        filterRegExp: /characteristic/i
                    }*/

                    delegate: Row {
                        width: parent.width

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
                                width: 50

                                ToolTip {
                                    parent: salut
                                    visible: salut.activeFocus
                                    text: "Nom : " + properties_role.name + "\nDescription : " + properties_role.description
                                }
                            }
                        }
                    }
                }
            }
        }

        GroupBox {
            id: groupBox1
            title: qsTr("Toutes les stats")
            Layout.fillHeight: true
            Layout.fillWidth: true

            ListView {
                clip: true
                anchors.fill: parent
                model: item_role.additions()
                delegate: Row {
                    width: parent.width
                    Repeater {
                        model: ["name", "description"]
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
                        }
                    }
                }
            }
        }

        Button {
            Layout.alignment: Qt.AlignRight
            text: "Éditer les stats"
            onClicked: stack.push("qrc:///EditProperties.qml", {"item_role": item_role, "properties_role": properties_role, "additions_role": item_role.additions()})
        }
    }
}



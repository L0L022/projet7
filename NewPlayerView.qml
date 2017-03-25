import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Flickable {
    id: item1
    contentHeight: superColumn.implicitHeight
    clip: true

    ColumnLayout {
        id: superColumn
        anchors.fill: parent

        GridLayout {
            Layout.fillWidth: true
            columns: item1.width > item1.height ? 2 : 1

            SuperSaisi {
                key: "name"
                key_name: "Nom"
            }

            SuperSaisi {
                key: "age"
                key_name: "Age"
            }

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
            Layout.minimumHeight: 200

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

                    model: PropertyFilterModel {
                        sourceModel: item_role.additions()
                        filterKey: "category"
                        filterValue: "characteristic"
                    }

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

        RowLayout {

            ComboBox {
                id: superCombo
                Layout.fillWidth: true
                model: ["skill", "equipment", "weapon", "armor", "characteristic"]
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: "Éditer les stats"
                onClicked: stack.push("qrc:///EditProperties.qml", {"item_role": item_role, "additions_role": item_role.additions()})
            }
        }

        Frame {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 200

            ListView {
                clip: true
                anchors.fill: parent
                model: PropertyFilterModel {
                    sourceModel: item_role.additions()
                    filterKey: "category"
                    filterValue: superCombo.currentText
                    onFilterValueChanged: console.log(filterValue)
                }
                delegate: RowLayout {
                    width: parent.width
                    Repeater {
                        model: ["name", "description"]
                        delegate: TextField {
                            Layout.fillWidth: true

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
    }
}



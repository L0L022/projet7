import QtQuick 2.7
//import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Flickable {
    id: item
    contentHeight: columnLayout.implicitHeight
    clip: true

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        GridLayout {
            Layout.fillWidth: true
            columns: item.width > item.height ? 2 : 1

            Repeater {
                model: ["name", "age", "calling", "height"]
                delegate: RowLayout {
                    PropertyField {
                        Layout.fillWidth: true
                        key: modelData
                        placeholderText: modelData
                    }
                }
            }
        }

        GroupBox {
            title: qsTr("Caractéristiques")
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 200

            ColumnLayout {
                anchors.fill: parent

                Row {
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
                        sourceModel: propertyRole.subProperties()
                        filterKey: "category"
                        filterValue: "characteristic"
                    }

                    delegate: Row {
                        width: parent.width

                        Repeater {
                            model: ["CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"]
                            delegate: PropertyField {
                                id: supertruc
                                key: modelData
                                width: 50
                                showResetButton: false

                                ToolTip {
                                    visible: parent.inTextField
                                    text: "Nom : " + propertiesRole.name + "\nDescription : " + propertiesRole.description
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
                //AAAH C'EST PAS BIEN
                model: ["skill", "equipment", "weapon", "armor", "characteristic"]
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: "Éditer les sous propriétées"
                onClicked: stack.push("qrc:///PropertyView.qml", {"propertyRole": propertyRole})
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
                    sourceModel: propertyRole.subProperties()
                    filterKey: "category"
                    filterValue: superCombo.currentText
                    onFilterValueChanged: console.log(filterValue)
                }
                delegate: RowLayout {
                    width: parent.width
                    Repeater {
                        model: ["name", "description"]
                        delegate: PropertyField {
                            key: modelData
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }
    }
}



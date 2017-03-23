import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Dialog {
    title: "edit properties"
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: parent.width * 0.9
    height: parent.height * 0.9

    ColumnLayout {
        anchors.fill: parent
    ListView {
        Layout.fillHeight: true
        Layout.fillWidth: true
        model: additions_role
        delegate: RowLayout {
            Label {
                text: properties_role.name
            }

            Button {
                text: "edit"
                onClicked: supereditpro.open()
            }

            EditProperty {
                id: supereditpro
            }

            Button {
                text: "remove"
                onClicked: additions_role.removeAddition(id_role)
            }
        }
    }
    RowLayout {
        Button {
            text: "add"
            onClicked: additions_role.addAddition()
        }
    }

}
}

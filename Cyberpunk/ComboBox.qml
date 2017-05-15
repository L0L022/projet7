import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T

T.ComboBox {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    spacing: 8
    padding: 6
    leftPadding: padding + 6
    rightPadding: padding + 6

    delegate: ItemDelegate {
        width: control.popup.width
        text: control.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
        font.weight: control.currentIndex === index ? Font.DemiBold : Font.Normal
        highlighted: control.highlightedIndex == index
        hoverEnabled: control.hoverEnabled
        background: Rectangle {
            color: "transparent"
        }
    }

    contentItem: Text {
        leftPadding: control.mirrored && control.indicator ? control.indicator.width + control.spacing : 0
        rightPadding: !control.mirrored && control.indicator ? control.indicator.width + control.spacing : 0

        text: control.displayText
//        font: control.font
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        opacity: enabled ? 1 : 0.3

        color: "white"
        font.family: smallFont.name
        FontLoader {
            id: smallFont
            source: "Xolonium.ttf"
        }
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 50
        color: "transparent"
        visible: !control.flat || control.pressed

        Image {
            anchors.fill: parent
            anchors.topMargin: 4
            anchors.bottomMargin: 4
            anchors.leftMargin: 8
            anchors.rightMargin: 46
            source: control.pressed || popup.visible ? "fondR.jpeg" : "fondB.jpeg"
            fillMode: Image.Tile
        }

        BorderImage {
            anchors.fill: parent
            source: "combobox.png"
            border.left: 16; border.top: 22
            border.right: 53; border.bottom: 22
            horizontalTileMode: BorderImage.Repeat
        }
    }

    popup: T.Popup {
        y: control.height - (control.visualFocus ? 0 : 1)
        width: control.width
        implicitHeight: contentItem.implicitHeight
        topMargin: 6
        bottomMargin: 6

        contentItem: ListView {
            id: listview
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            highlightRangeMode: ListView.ApplyRange
            highlightMoveDuration: 0

            T.ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Item {
            Image {
                anchors.fill: parent
                anchors.topMargin: 4
                anchors.bottomMargin: 4
                anchors.leftMargin: 8
                anchors.rightMargin: 8
                source: "fondB.jpeg"
                fillMode: Image.Tile
            }

            BorderImage {
                anchors.fill: parent
                source: "bouton.png"
                border.left: 16; border.top: 11
                border.right: 16; border.bottom: 11
                horizontalTileMode: BorderImage.Repeat
                verticalTileMode: BorderImage.Repeat
            }
        }
    }
}

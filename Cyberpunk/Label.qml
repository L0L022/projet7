import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T

T.Label {
    id: control

    color: "white"
    font.family: smallFont.name
    FontLoader {
        id: smallFont
        source: "Xolonium.ttf"
    }
}

import QtQuick 2.15
import QtQuick.Layouts 1.15

RowLayout {
    property var headerElements: []

    width: parent.width
    spacing: 20
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
        topMargin: 15
    }

    Repeater {
        model: parent.headerElements
        Text {
            text: modelData
            color: "white"
            font.pixelSize: 24
            font.bold: true
            Layout.preferredWidth: 150
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}

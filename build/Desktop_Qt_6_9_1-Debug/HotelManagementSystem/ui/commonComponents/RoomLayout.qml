import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: roomLayout
    width: 100
    height: 100
    radius: 8
    border.color: "white"
    border.width: 1.5
    color: "#153B56"

    property string roomNumber: ""
    property string status: ""

    signal clicked()

    Column {
        anchors.fill: parent
        anchors.margins: 6
        spacing: 4

        Text {
            text: roomNumber
            color: "white"
            font.pixelSize: 18
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: parent.width
        }

        Rectangle {
            width: parent.width
            height: 28
            radius: 4
            color: {
                if (status === "Occupied") return "#E53935";
                else if (status === "Vacant") return "#43A047";
                else if (status === "Dirty") return "#FBC02D";
                else if (status === "Out of Order") return "#607D8B";
                else return "gray";
            }

            Text {
                anchors.centerIn: parent
                text: status.toUpperCase()
                color: "white"
                font.pixelSize: 12
                font.bold: true
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: roomLayout.clicked()
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
    }
}

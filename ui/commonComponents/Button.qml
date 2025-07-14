import QtQuick 2.15

Item {
    id: button
    width: 80
    height: 80

    property string buttonColor: "#3A6EA5"
    property string buttonText: ""
    property string buttonSource: ""

    signal clicked()

    Column {
        anchors.centerIn: parent
        spacing: 6

        Rectangle {
            id: background
            width: button.width
            height: button.height
            color: button.buttonColor
            radius: 10
            border.color: "white"
            border.width: 1

            Image {
                anchors.fill: parent
                source: button.buttonSource
                width: 32
                height: 32
                fillMode: Image.PreserveAspectFit
            }

            MouseArea {
                anchors.fill: parent
                onClicked: button.clicked()
                hoverEnabled: true
                onEntered: background.color = Qt.darker(button.buttonColor, 1.2)
                onExited: background.color = button.buttonColor
            }
        }

        Text {
            text: button.buttonText
            color: "white"
            font.pixelSize: 23
            horizontalAlignment: Text.AlignHCenter
            width: button.width
            font.bold: true
            font.weight: Font.Black
        }
    }
}

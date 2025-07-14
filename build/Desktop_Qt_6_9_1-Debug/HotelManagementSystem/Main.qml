import QtQuick
import HotelManagementSystem

Window {
    visibility: Window.Maximized
    title: qsTr("Hello World")


    SharedScreen {
        id: welcomeScreen
        anchors.fill: parent
    }
}

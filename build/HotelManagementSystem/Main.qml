import QtQuick
import HotelManagementSystem

Window {
    visibility: Window.Maximized
    title: qsTr("Hello World")

    WelcomeScreen {
        id: welcomeScreen
        anchors.fill: parent
    }
}

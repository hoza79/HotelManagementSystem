import QtQuick 2.15
import "../commonComponents"
import QtQuick.Layouts

Rectangle {
    id: sideBar
    width: 120
    height: parent.height * 0.7
    color: "transparent"


    signal reservationsClicked()
    signal guestsClicked()
    signal checkInAndOutClicked()
    signal roomStatusClicked()

    anchors {
        left: parent.left
        verticalCenter: parent.verticalCenter
        leftMargin: 30
    }

    ColumnLayout {
        id: buttonColumn
        anchors.fill: parent

        Button {
            Layout.alignment: Qt.AlignHCenter
            buttonColor: "#3A6EA5"
            buttonText: "Reservations"
            buttonSource: "qrc:/ui/assets/reservations.png"
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            buttonColor: "#3A6EA5"
            buttonText: "Check in/out"
            buttonSource: "qrc:/ui/assets/check-in-out.png"
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            buttonColor: "#3A6EA5"
            buttonText: "Room Status"
            buttonSource: "qrc:/ui/assets/roomStatus.png"
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            buttonColor: "#3A6EA5"
            buttonText: "Guests"
            buttonSource: "qrc:/ui/assets/guests.png"
        }
    }
}

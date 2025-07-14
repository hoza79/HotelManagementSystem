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
    signal homeClicked()
    signal newReservationClicked()
    signal newGuestClicked()


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
            buttonText: "Home"
            buttonSource: "qrc:/ui/assets/home.png"
            onClicked: {
                sideBar.homeClicked()
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            buttonColor: "#3A6EA5"
            buttonText: "Reservations"
            buttonSource: "qrc:/ui/assets/reservations.png"
            onClicked: {
                sideBar.reservationsClicked()
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            buttonColor: "#3A6EA5"
            buttonText: "Check in/out"
            buttonSource: "qrc:/ui/assets/check-in-out.png"
            onClicked: {
                sideBar.checkInAndOutClicked()
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            buttonColor: "#3A6EA5"
            buttonText: "Room Status"
            buttonSource: "qrc:/ui/assets/roomStatus.png"
            onClicked: {
                sideBar.roomStatusClicked()
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            buttonColor: "#3A6EA5"
            buttonText: "Guests"
            buttonSource: "qrc:/ui/assets/guests.png"
            onClicked: {
                sideBar.guestsClicked()
            }
        }
    }
}

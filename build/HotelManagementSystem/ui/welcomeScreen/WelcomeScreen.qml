import QtQuick 2.15
import "../commonComponents"
import "../sideBar"
import "../reservationScreen"

Rectangle {
    anchors.fill: parent

    Image {
        id: bg
        source: "qrc:/ui/assets/backgroundImage.png"
        fillMode: Image.Stretch
        anchors.fill: parent
    }

    Rectangle{
        color: "#000000"
        opacity: 0.3
        anchors.fill: parent
    }

    SideBar{
        id: sideBar

        Loader{
            id: pageLoader
            anchors.fill: parent
        }

        onReservationsClicked: {
            pageLoader.source = "../reservationScreen/Rerservation.qml"
        }

        onGuestsClicked: {
            pageLoader.source = "../guestScreen/Guest.qml"
        }

        onCheckInAndOutClicked: {
            pageLoader.source = "../checkInAndOutSCreen/CheckInAndOut"
        }

        onRoomStatusClicked: {
            pageLoader.source = "../roomStatus/RoomStatus"
        }


    }

}

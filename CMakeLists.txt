cmake_minimum_required(VERSION 3.16)

project(HotelManagementSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appHotelManagementSystem
    main.cpp
)

qt_add_qml_module(appHotelManagementSystem
    URI HotelManagementSystem
    VERSION 1.0

    QML_FILES
        Main.qml
        ui/welcomeScreen/WelcomeScreen.qml
        ui/commonComponents/Button.qml
        ui/sideBar/SideBar.qml
        ui/guestScreen/GuestScreen.qml
        ui/checkInAndOutScreen/CheckInAndOut.qml
        ui/roomStatus/RoomStatus.qml
        ui/reservationScreen/ReservationScreen.qml
        ui/commonComponents/SharedScreen.qml
        ui/reservationScreen/NewReservation.qml
        ui/guestScreen/NewGuest.qml
        ui/commonComponents/RoomLayout.qml
        ui/checkInAndOutScreen/NewCheckInOut.qml


    SOURCES


        controllers/ReservationModel.h
        controllers/ReservationModel.cpp
        controllers/GuestModel.h
        controllers/GuestModel.cpp
        controllers/RoomModel.h
        controllers/RoomModel.cpp
        controllers/CheckInOutModel.h
        controllers/CheckInOutModel.cpp
        controllers/FilterableListModel.h
        controllers/FilterableListModel.cpp





)

qt_add_resources(appHotelManagementSystem "resources"
    PREFIX "/"
    FILES
        ui/assets/backgroundImage.png
        ui/assets/reservations.png
        ui/assets/guests.png
        ui/assets/check-in-out.png
        ui/assets/roomStatus.png
        ui/assets/home.png
        ui/assets/searchIcon.png
)

set_target_properties(appHotelManagementSystem PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHotelManagementSystem
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appHotelManagementSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

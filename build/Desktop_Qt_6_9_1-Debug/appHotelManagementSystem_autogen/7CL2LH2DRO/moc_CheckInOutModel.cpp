/****************************************************************************
** Meta object code from reading C++ file 'CheckInOutModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../controllers/CheckInOutModel.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CheckInOutModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15CheckInOutModelE_t {};
} // unnamed namespace

template <> constexpr inline auto CheckInOutModel::qt_create_metaobjectdata<qt_meta_tag_ZN15CheckInOutModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CheckInOutModel",
        "refreshReservationsRequested",
        "",
        "refreshGuestsRequested",
        "refreshRoomsRequested",
        "checkInOutSaved",
        "onReplyFinished",
        "QNetworkReply*",
        "reply",
        "fetchCheckInOuts",
        "addCheckInOut",
        "reservationId",
        "action",
        "roomId"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'refreshReservationsRequested'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'refreshGuestsRequested'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'refreshRoomsRequested'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'checkInOutSaved'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onReplyFinished'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Method 'fetchCheckInOuts'
        QtMocHelpers::MethodData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'addCheckInOut'
        QtMocHelpers::MethodData<void(int, const QString &, int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 11 }, { QMetaType::QString, 12 }, { QMetaType::Int, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CheckInOutModel, qt_meta_tag_ZN15CheckInOutModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CheckInOutModel::staticMetaObject = { {
    QMetaObject::SuperData::link<FilterableListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15CheckInOutModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15CheckInOutModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15CheckInOutModelE_t>.metaTypes,
    nullptr
} };

void CheckInOutModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CheckInOutModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->refreshReservationsRequested(); break;
        case 1: _t->refreshGuestsRequested(); break;
        case 2: _t->refreshRoomsRequested(); break;
        case 3: _t->checkInOutSaved(); break;
        case 4: _t->onReplyFinished((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 5: _t->fetchCheckInOuts(); break;
        case 6: _t->addCheckInOut((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CheckInOutModel::*)()>(_a, &CheckInOutModel::refreshReservationsRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CheckInOutModel::*)()>(_a, &CheckInOutModel::refreshGuestsRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CheckInOutModel::*)()>(_a, &CheckInOutModel::refreshRoomsRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (CheckInOutModel::*)()>(_a, &CheckInOutModel::checkInOutSaved, 3))
            return;
    }
}

const QMetaObject *CheckInOutModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CheckInOutModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15CheckInOutModelE_t>.strings))
        return static_cast<void*>(this);
    return FilterableListModel::qt_metacast(_clname);
}

int CheckInOutModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FilterableListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CheckInOutModel::refreshReservationsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CheckInOutModel::refreshGuestsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CheckInOutModel::refreshRoomsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CheckInOutModel::checkInOutSaved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP

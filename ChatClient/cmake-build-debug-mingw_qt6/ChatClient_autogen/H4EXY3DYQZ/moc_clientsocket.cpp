/****************************************************************************
** Meta object code from reading C++ file 'clientsocket.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../NetWork/clientsocket.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
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
struct qt_meta_tag_ZN12ClientSocketE_t {};
} // unnamed namespace

template <> constexpr inline auto ClientSocket::qt_create_metaobjectdata<qt_meta_tag_ZN12ClientSocketE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ClientSocket",
        "signalMessage",
        "",
        "type",
        "dataVal",
        "signalStatus",
        "state",
        "sltSendMessage",
        "sltSendOnline",
        "sltSendOffline",
        "sltDisconnected",
        "sltConnected",
        "sltReadyRead"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'signalMessage'
        QtMocHelpers::SignalData<void(const quint8 &, const QJsonValue &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 3 }, { QMetaType::QJsonValue, 4 },
        }}),
        // Signal 'signalStatus'
        QtMocHelpers::SignalData<void(const quint8 &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 6 },
        }}),
        // Slot 'sltSendMessage'
        QtMocHelpers::SlotData<void(const quint8 &, const QJsonValue &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 3 }, { QMetaType::QJsonValue, 4 },
        }}),
        // Slot 'sltSendOnline'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'sltSendOffline'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'sltDisconnected'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'sltConnected'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'sltReadyRead'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ClientSocket, qt_meta_tag_ZN12ClientSocketE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ClientSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12ClientSocketE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12ClientSocketE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12ClientSocketE_t>.metaTypes,
    nullptr
} };

void ClientSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ClientSocket *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signalMessage((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[2]))); break;
        case 1: _t->signalStatus((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1]))); break;
        case 2: _t->sltSendMessage((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[2]))); break;
        case 3: _t->sltSendOnline(); break;
        case 4: _t->sltSendOffline(); break;
        case 5: _t->sltDisconnected(); break;
        case 6: _t->sltConnected(); break;
        case 7: _t->sltReadyRead(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ClientSocket::*)(const quint8 & , const QJsonValue & )>(_a, &ClientSocket::signalMessage, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientSocket::*)(const quint8 & )>(_a, &ClientSocket::signalStatus, 1))
            return;
    }
}

const QMetaObject *ClientSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12ClientSocketE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ClientSocket::signalMessage(const quint8 & _t1, const QJsonValue & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void ClientSocket::signalStatus(const quint8 & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP

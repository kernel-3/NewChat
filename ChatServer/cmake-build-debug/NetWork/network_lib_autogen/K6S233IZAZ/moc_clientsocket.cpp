/****************************************************************************
** Meta object code from reading C++ file 'clientsocket.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../NetWork/headers/clientsocket.h"
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
        "signalConnected",
        "",
        "signalDisConnected",
        "signalDownloadFile",
        "json",
        "signalMsgToClient",
        "type",
        "id",
        "dataVal",
        "SltSendMessage",
        "SltConnected",
        "SltDisconnected",
        "SltReadyRead"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'signalConnected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'signalDisConnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'signalDownloadFile'
        QtMocHelpers::SignalData<void(const QJsonValue &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonValue, 5 },
        }}),
        // Signal 'signalMsgToClient'
        QtMocHelpers::SignalData<void(const quint8 &, const int &, const QJsonValue &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 7 }, { QMetaType::Int, 8 }, { QMetaType::QJsonValue, 9 },
        }}),
        // Slot 'SltSendMessage'
        QtMocHelpers::SlotData<void(const quint8 &, const QJsonValue &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 7 }, { QMetaType::QJsonValue, 5 },
        }}),
        // Slot 'SltConnected'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltDisconnected'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltReadyRead'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
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
        case 0: _t->signalConnected(); break;
        case 1: _t->signalDisConnected(); break;
        case 2: _t->signalDownloadFile((*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[1]))); break;
        case 3: _t->signalMsgToClient((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[3]))); break;
        case 4: _t->SltSendMessage((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[2]))); break;
        case 5: _t->SltConnected(); break;
        case 6: _t->SltDisconnected(); break;
        case 7: _t->SltReadyRead(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ClientSocket::*)()>(_a, &ClientSocket::signalConnected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientSocket::*)()>(_a, &ClientSocket::signalDisConnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientSocket::*)(const QJsonValue & )>(_a, &ClientSocket::signalDownloadFile, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientSocket::*)(const quint8 & , const int & , const QJsonValue & )>(_a, &ClientSocket::signalMsgToClient, 3))
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
void ClientSocket::signalConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ClientSocket::signalDisConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ClientSocket::signalDownloadFile(const QJsonValue & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ClientSocket::signalMsgToClient(const quint8 & _t1, const int & _t2, const QJsonValue & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}
namespace {
struct qt_meta_tag_ZN16ClientFileSocketE_t {};
} // unnamed namespace

template <> constexpr inline auto ClientFileSocket::qt_create_metaobjectdata<qt_meta_tag_ZN16ClientFileSocketE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ClientFileSocket",
        "signalConnected",
        "",
        "signalDisConnected",
        "signalRecvFinished",
        "id",
        "json",
        "displayError",
        "QAbstractSocket::SocketError",
        "SltReadyRead",
        "SltUpdateClientProgress",
        "numBytes"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'signalConnected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'signalDisConnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'signalRecvFinished'
        QtMocHelpers::SignalData<void(int, const QJsonValue &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::QJsonValue, 6 },
        }}),
        // Slot 'displayError'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 2 },
        }}),
        // Slot 'SltReadyRead'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltUpdateClientProgress'
        QtMocHelpers::SlotData<void(qint64)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ClientFileSocket, qt_meta_tag_ZN16ClientFileSocketE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ClientFileSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ClientFileSocketE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ClientFileSocketE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16ClientFileSocketE_t>.metaTypes,
    nullptr
} };

void ClientFileSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ClientFileSocket *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signalConnected(); break;
        case 1: _t->signalDisConnected(); break;
        case 2: _t->signalRecvFinished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[2]))); break;
        case 3: _t->displayError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 4: _t->SltReadyRead(); break;
        case 5: _t->SltUpdateClientProgress((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ClientFileSocket::*)()>(_a, &ClientFileSocket::signalConnected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientFileSocket::*)()>(_a, &ClientFileSocket::signalDisConnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientFileSocket::*)(int , const QJsonValue & )>(_a, &ClientFileSocket::signalRecvFinished, 2))
            return;
    }
}

const QMetaObject *ClientFileSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientFileSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ClientFileSocketE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientFileSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ClientFileSocket::signalConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ClientFileSocket::signalDisConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ClientFileSocket::signalRecvFinished(int _t1, const QJsonValue & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}
QT_WARNING_POP

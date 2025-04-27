/****************************************************************************
** Meta object code from reading C++ file 'tcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../NetWork/headers/tcpserver.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpserver.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9TcpServerE_t {};
} // unnamed namespace

template <> constexpr inline auto TcpServer::qt_create_metaobjectdata<qt_meta_tag_ZN9TcpServerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TcpServer",
        "signalUserStatus",
        "",
        "text",
        "SltNewConnection",
        "SltConnected",
        "SltDisConnected"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'signalUserStatus'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'SltNewConnection'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'SltConnected'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'SltDisConnected'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessProtected, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TcpServer, qt_meta_tag_ZN9TcpServerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TcpServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9TcpServerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9TcpServerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9TcpServerE_t>.metaTypes,
    nullptr
} };

void TcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TcpServer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signalUserStatus((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->SltNewConnection(); break;
        case 2: _t->SltConnected(); break;
        case 3: _t->SltDisConnected(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TcpServer::*)(const QString & )>(_a, &TcpServer::signalUserStatus, 0))
            return;
    }
}

const QMetaObject *TcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9TcpServerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TcpServer::signalUserStatus(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN12TcpMsgServerE_t {};
} // unnamed namespace

template <> constexpr inline auto TcpMsgServer::qt_create_metaobjectdata<qt_meta_tag_ZN12TcpMsgServerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TcpMsgServer",
        "signalDownloadFile",
        "",
        "json",
        "SltTransFileToClient",
        "userId",
        "SltNewConnection",
        "SltConnected",
        "SltDisConnected",
        "SltMsgToClient",
        "type",
        "id"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'signalDownloadFile'
        QtMocHelpers::SignalData<void(const QJsonValue &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonValue, 3 },
        }}),
        // Slot 'SltTransFileToClient'
        QtMocHelpers::SlotData<void(const int &, const QJsonValue &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::QJsonValue, 3 },
        }}),
        // Slot 'SltNewConnection'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltConnected'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltDisConnected'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltMsgToClient'
        QtMocHelpers::SlotData<void(const quint8 &, const int &, const QJsonValue &)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::UChar, 10 }, { QMetaType::Int, 11 }, { QMetaType::QJsonValue, 3 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TcpMsgServer, qt_meta_tag_ZN12TcpMsgServerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TcpMsgServer::staticMetaObject = { {
    QMetaObject::SuperData::link<TcpServer::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12TcpMsgServerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12TcpMsgServerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12TcpMsgServerE_t>.metaTypes,
    nullptr
} };

void TcpMsgServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TcpMsgServer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signalDownloadFile((*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[1]))); break;
        case 1: _t->SltTransFileToClient((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[2]))); break;
        case 2: _t->SltNewConnection(); break;
        case 3: _t->SltConnected(); break;
        case 4: _t->SltDisConnected(); break;
        case 5: _t->SltMsgToClient((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TcpMsgServer::*)(const QJsonValue & )>(_a, &TcpMsgServer::signalDownloadFile, 0))
            return;
    }
}

const QMetaObject *TcpMsgServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpMsgServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12TcpMsgServerE_t>.strings))
        return static_cast<void*>(this);
    return TcpServer::qt_metacast(_clname);
}

int TcpMsgServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TcpMsgServer::signalDownloadFile(const QJsonValue & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN13TcpFileServerE_t {};
} // unnamed namespace

template <> constexpr inline auto TcpFileServer::qt_create_metaobjectdata<qt_meta_tag_ZN13TcpFileServerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TcpFileServer",
        "signalRecvFinished",
        "",
        "id",
        "json",
        "SltNewConnection",
        "SltConnected",
        "SltDisConnected",
        "SltClientDownloadFile"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'signalRecvFinished'
        QtMocHelpers::SignalData<void(int, const QJsonValue &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::QJsonValue, 4 },
        }}),
        // Slot 'SltNewConnection'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltConnected'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltDisConnected'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'SltClientDownloadFile'
        QtMocHelpers::SlotData<void(const QJsonValue &)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QJsonValue, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TcpFileServer, qt_meta_tag_ZN13TcpFileServerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TcpFileServer::staticMetaObject = { {
    QMetaObject::SuperData::link<TcpServer::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TcpFileServerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TcpFileServerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13TcpFileServerE_t>.metaTypes,
    nullptr
} };

void TcpFileServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TcpFileServer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signalRecvFinished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[2]))); break;
        case 1: _t->SltNewConnection(); break;
        case 2: _t->SltConnected(); break;
        case 3: _t->SltDisConnected(); break;
        case 4: _t->SltClientDownloadFile((*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TcpFileServer::*)(int , const QJsonValue & )>(_a, &TcpFileServer::signalRecvFinished, 0))
            return;
    }
}

const QMetaObject *TcpFileServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpFileServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TcpFileServerE_t>.strings))
        return static_cast<void*>(this);
    return TcpServer::qt_metacast(_clname);
}

int TcpFileServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TcpFileServer::signalRecvFinished(int _t1, const QJsonValue & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}
QT_WARNING_POP

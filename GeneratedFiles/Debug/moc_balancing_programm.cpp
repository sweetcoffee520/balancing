/****************************************************************************
** Meta object code from reading C++ file 'balancing_programm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../balancing_programm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'balancing_programm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_balancing_programm_t {
    QByteArrayData data[10];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_balancing_programm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_balancing_programm_t qt_meta_stringdata_balancing_programm = {
    {
QT_MOC_LITERAL(0, 0, 18), // "balancing_programm"
QT_MOC_LITERAL(1, 19, 8), // "readfile"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "savefile"
QT_MOC_LITERAL(4, 38, 9), // "pro_close"
QT_MOC_LITERAL(5, 48, 4), // "help"
QT_MOC_LITERAL(6, 53, 11), // "codi_adjust"
QT_MOC_LITERAL(7, 65, 10), // "ird_adjust"
QT_MOC_LITERAL(8, 76, 8), // "ori_data"
QT_MOC_LITERAL(9, 85, 13) // "level_network"

    },
    "balancing_programm\0readfile\0\0savefile\0"
    "pro_close\0help\0codi_adjust\0ird_adjust\0"
    "ori_data\0level_network"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_balancing_programm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void balancing_programm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        balancing_programm *_t = static_cast<balancing_programm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readfile(); break;
        case 1: _t->savefile(); break;
        case 2: _t->pro_close(); break;
        case 3: _t->help(); break;
        case 4: _t->codi_adjust(); break;
        case 5: _t->ird_adjust(); break;
        case 6: _t->ori_data(); break;
        case 7: _t->level_network(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject balancing_programm::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_balancing_programm.data,
    qt_meta_data_balancing_programm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *balancing_programm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *balancing_programm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_balancing_programm.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int balancing_programm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'chealthmonitorwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/chealthmonitorwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chealthmonitorwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CHealthMonitorWidget_t {
    QByteArrayData data[8];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CHealthMonitorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CHealthMonitorWidget_t qt_meta_stringdata_CHealthMonitorWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CHealthMonitorWidget"
QT_MOC_LITERAL(1, 21, 12), // "updateHealth"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "runDiagnostics"
QT_MOC_LITERAL(4, 50, 11), // "resetAlarms"
QT_MOC_LITERAL(5, 62, 15), // "onModuleClicked"
QT_MOC_LITERAL(6, 78, 10), // "moduleName"
QT_MOC_LITERAL(7, 89, 18) // "exportHealthReport"

    },
    "CHealthMonitorWidget\0updateHealth\0\0"
    "runDiagnostics\0resetAlarms\0onModuleClicked\0"
    "moduleName\0exportHealthReport"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CHealthMonitorWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

       0        // eod
};

void CHealthMonitorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CHealthMonitorWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateHealth(); break;
        case 1: _t->runDiagnostics(); break;
        case 2: _t->resetAlarms(); break;
        case 3: _t->onModuleClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->exportHealthReport(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CHealthMonitorWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_CHealthMonitorWidget.data,
    qt_meta_data_CHealthMonitorWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CHealthMonitorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CHealthMonitorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CHealthMonitorWidget.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int CHealthMonitorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

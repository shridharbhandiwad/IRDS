/****************************************************************************
** Meta object code from reading C++ file 'cpredictivemaintenancewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/cpredictivemaintenancewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cpredictivemaintenancewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPredictiveMaintenanceWidget_t {
    QByteArrayData data[9];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPredictiveMaintenanceWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPredictiveMaintenanceWidget_t qt_meta_stringdata_CPredictiveMaintenanceWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "CPredictiveMaintenanceWidget"
QT_MOC_LITERAL(1, 29, 12), // "updateStatus"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 22), // "scheduleMaintenanceNow"
QT_MOC_LITERAL(4, 66, 22), // "viewMaintenanceHistory"
QT_MOC_LITERAL(5, 89, 18), // "onComponentClicked"
QT_MOC_LITERAL(6, 108, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 125, 4), // "item"
QT_MOC_LITERAL(8, 130, 23) // "exportMaintenanceReport"

    },
    "CPredictiveMaintenanceWidget\0updateStatus\0"
    "\0scheduleMaintenanceNow\0viewMaintenanceHistory\0"
    "onComponentClicked\0QListWidgetItem*\0"
    "item\0exportMaintenanceReport"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPredictiveMaintenanceWidget[] = {

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
       8,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,

       0        // eod
};

void CPredictiveMaintenanceWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CPredictiveMaintenanceWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateStatus(); break;
        case 1: _t->scheduleMaintenanceNow(); break;
        case 2: _t->viewMaintenanceHistory(); break;
        case 3: _t->onComponentClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->exportMaintenanceReport(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CPredictiveMaintenanceWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_CPredictiveMaintenanceWidget.data,
    qt_meta_data_CPredictiveMaintenanceWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CPredictiveMaintenanceWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPredictiveMaintenanceWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPredictiveMaintenanceWidget.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int CPredictiveMaintenanceWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

/****************************************************************************
** Meta object code from reading C++ file 'ctracktablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/ctracktablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctracktablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CTrackTableWidget_t {
    QByteArrayData data[13];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CTrackTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CTrackTableWidget_t qt_meta_stringdata_CTrackTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CTrackTableWidget"
QT_MOC_LITERAL(1, 18, 13), // "trackSelected"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 7), // "trackId"
QT_MOC_LITERAL(4, 41, 18), // "trackDoubleClicked"
QT_MOC_LITERAL(5, 60, 16), // "updateTrackTable"
QT_MOC_LITERAL(6, 77, 23), // "onTrackSelectionChanged"
QT_MOC_LITERAL(7, 101, 15), // "onFilterChanged"
QT_MOC_LITERAL(8, 117, 4), // "text"
QT_MOC_LITERAL(9, 122, 23), // "onIdentityFilterChanged"
QT_MOC_LITERAL(10, 146, 5), // "index"
QT_MOC_LITERAL(11, 152, 16), // "onClearAllTracks"
QT_MOC_LITERAL(12, 169, 14) // "onExportTracks"

    },
    "CTrackTableWidget\0trackSelected\0\0"
    "trackId\0trackDoubleClicked\0updateTrackTable\0"
    "onTrackSelectionChanged\0onFilterChanged\0"
    "text\0onIdentityFilterChanged\0index\0"
    "onClearAllTracks\0onExportTracks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CTrackTableWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   60,    2, 0x08 /* Private */,
       6,    0,   61,    2, 0x08 /* Private */,
       7,    1,   62,    2, 0x08 /* Private */,
       9,    1,   65,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CTrackTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CTrackTableWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->trackSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->trackDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateTrackTable(); break;
        case 3: _t->onTrackSelectionChanged(); break;
        case 4: _t->onFilterChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onIdentityFilterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onClearAllTracks(); break;
        case 7: _t->onExportTracks(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CTrackTableWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTrackTableWidget::trackSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CTrackTableWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTrackTableWidget::trackDoubleClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CTrackTableWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_CTrackTableWidget.data,
    qt_meta_data_CTrackTableWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CTrackTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CTrackTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CTrackTableWidget.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int CTrackTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void CTrackTableWidget::trackSelected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CTrackTableWidget::trackDoubleClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

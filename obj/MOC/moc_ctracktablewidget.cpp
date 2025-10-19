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
    QByteArrayData data[19];
    char stringdata0[262];
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
QT_MOC_LITERAL(5, 60, 17), // "trackRightClicked"
QT_MOC_LITERAL(6, 78, 9), // "globalPos"
QT_MOC_LITERAL(7, 88, 16), // "trackImageLoaded"
QT_MOC_LITERAL(8, 105, 9), // "imagePath"
QT_MOC_LITERAL(9, 115, 16), // "updateTrackTable"
QT_MOC_LITERAL(10, 132, 23), // "onTrackSelectionChanged"
QT_MOC_LITERAL(11, 156, 15), // "onFilterChanged"
QT_MOC_LITERAL(12, 172, 4), // "text"
QT_MOC_LITERAL(13, 177, 23), // "onIdentityFilterChanged"
QT_MOC_LITERAL(14, 201, 5), // "index"
QT_MOC_LITERAL(15, 207, 16), // "onClearAllTracks"
QT_MOC_LITERAL(16, 224, 14), // "onExportTracks"
QT_MOC_LITERAL(17, 239, 18), // "onTableContextMenu"
QT_MOC_LITERAL(18, 258, 3) // "pos"

    },
    "CTrackTableWidget\0trackSelected\0\0"
    "trackId\0trackDoubleClicked\0trackRightClicked\0"
    "globalPos\0trackImageLoaded\0imagePath\0"
    "updateTrackTable\0onTrackSelectionChanged\0"
    "onFilterChanged\0text\0onIdentityFilterChanged\0"
    "index\0onClearAllTracks\0onExportTracks\0"
    "onTableContextMenu\0pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CTrackTableWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       5,    2,   75,    2, 0x06 /* Public */,
       7,    2,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   85,    2, 0x08 /* Private */,
      10,    0,   86,    2, 0x08 /* Private */,
      11,    1,   87,    2, 0x08 /* Private */,
      13,    1,   90,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,
      16,    0,   94,    2, 0x08 /* Private */,
      17,    1,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QPoint,    3,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   18,

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
        case 2: _t->trackRightClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 3: _t->trackImageLoaded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->updateTrackTable(); break;
        case 5: _t->onTrackSelectionChanged(); break;
        case 6: _t->onFilterChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onIdentityFilterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onClearAllTracks(); break;
        case 9: _t->onExportTracks(); break;
        case 10: _t->onTableContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
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
        {
            using _t = void (CTrackTableWidget::*)(int , const QPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTrackTableWidget::trackRightClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CTrackTableWidget::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTrackTableWidget::trackImageLoaded)) {
                *result = 3;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
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

// SIGNAL 2
void CTrackTableWidget::trackRightClicked(int _t1, const QPoint & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CTrackTableWidget::trackImageLoaded(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

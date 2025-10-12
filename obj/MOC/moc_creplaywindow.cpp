/****************************************************************************
** Meta object code from reading C++ file 'creplaywindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/creplaywindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'creplaywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CReplayWindow_t {
    QByteArrayData data[21];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CReplayWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CReplayWindow_t qt_meta_stringdata_CReplayWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CReplayWindow"
QT_MOC_LITERAL(1, 14, 12), // "windowClosed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "playVideo"
QT_MOC_LITERAL(4, 38, 10), // "pauseVideo"
QT_MOC_LITERAL(5, 49, 9), // "stopVideo"
QT_MOC_LITERAL(6, 59, 16), // "setPlaybackSpeed"
QT_MOC_LITERAL(7, 76, 5), // "speed"
QT_MOC_LITERAL(8, 82, 14), // "seekToPosition"
QT_MOC_LITERAL(9, 97, 8), // "position"
QT_MOC_LITERAL(10, 106, 17), // "onPositionChanged"
QT_MOC_LITERAL(11, 124, 17), // "onDurationChanged"
QT_MOC_LITERAL(12, 142, 8), // "duration"
QT_MOC_LITERAL(13, 151, 14), // "onStateChanged"
QT_MOC_LITERAL(14, 166, 19), // "QMediaPlayer::State"
QT_MOC_LITERAL(15, 186, 5), // "state"
QT_MOC_LITERAL(16, 192, 14), // "onSpeedChanged"
QT_MOC_LITERAL(17, 207, 5), // "value"
QT_MOC_LITERAL(18, 213, 14), // "minimizeWindow"
QT_MOC_LITERAL(19, 228, 14), // "maximizeWindow"
QT_MOC_LITERAL(20, 243, 11) // "closeWindow"

    },
    "CReplayWindow\0windowClosed\0\0playVideo\0"
    "pauseVideo\0stopVideo\0setPlaybackSpeed\0"
    "speed\0seekToPosition\0position\0"
    "onPositionChanged\0onDurationChanged\0"
    "duration\0onStateChanged\0QMediaPlayer::State\0"
    "state\0onSpeedChanged\0value\0minimizeWindow\0"
    "maximizeWindow\0closeWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CReplayWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    1,   83,    2, 0x0a /* Public */,
       8,    1,   86,    2, 0x0a /* Public */,
      10,    1,   89,    2, 0x08 /* Private */,
      11,    1,   92,    2, 0x08 /* Private */,
      13,    1,   95,    2, 0x08 /* Private */,
      16,    1,   98,    2, 0x08 /* Private */,
      18,    0,  101,    2, 0x08 /* Private */,
      19,    0,  102,    2, 0x08 /* Private */,
      20,    0,  103,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::LongLong,    9,
    QMetaType::Void, QMetaType::LongLong,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CReplayWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CReplayWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->windowClosed(); break;
        case 1: _t->playVideo(); break;
        case 2: _t->pauseVideo(); break;
        case 3: _t->stopVideo(); break;
        case 4: _t->setPlaybackSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->seekToPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onPositionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->onDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->onStateChanged((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 9: _t->onSpeedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->minimizeWindow(); break;
        case 11: _t->maximizeWindow(); break;
        case 12: _t->closeWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CReplayWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CReplayWindow::windowClosed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CReplayWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CReplayWindow.data,
    qt_meta_data_CReplayWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CReplayWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CReplayWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CReplayWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CReplayWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CReplayWindow::windowClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

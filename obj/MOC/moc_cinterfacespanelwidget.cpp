/****************************************************************************
** Meta object code from reading C++ file 'cinterfacespanelwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/cinterfacespanelwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cinterfacespanelwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CInterfacesPanelWidget_t {
    QByteArrayData data[62];
    char stringdata0[954];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CInterfacesPanelWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CInterfacesPanelWidget_t qt_meta_stringdata_CInterfacesPanelWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "CInterfacesPanelWidget"
QT_MOC_LITERAL(1, 23, 19), // "servoAzimuthChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 7), // "azimuth"
QT_MOC_LITERAL(4, 52, 21), // "servoElevationChanged"
QT_MOC_LITERAL(5, 74, 9), // "elevation"
QT_MOC_LITERAL(6, 84, 17), // "servoSpeedChanged"
QT_MOC_LITERAL(7, 102, 5), // "speed"
QT_MOC_LITERAL(8, 108, 18), // "servoHomeRequested"
QT_MOC_LITERAL(9, 127, 18), // "servoStopRequested"
QT_MOC_LITERAL(10, 146, 25), // "servoCalibrationRequested"
QT_MOC_LITERAL(11, 172, 16), // "radarModeChanged"
QT_MOC_LITERAL(12, 189, 4), // "mode"
QT_MOC_LITERAL(13, 194, 17), // "radarRangeChanged"
QT_MOC_LITERAL(14, 212, 5), // "range"
QT_MOC_LITERAL(15, 218, 16), // "radarGainChanged"
QT_MOC_LITERAL(16, 235, 4), // "gain"
QT_MOC_LITERAL(17, 240, 23), // "radarScanStartRequested"
QT_MOC_LITERAL(18, 264, 22), // "radarScanStopRequested"
QT_MOC_LITERAL(19, 287, 19), // "radarResetRequested"
QT_MOC_LITERAL(20, 307, 17), // "gunAzimuthChanged"
QT_MOC_LITERAL(21, 325, 19), // "gunElevationChanged"
QT_MOC_LITERAL(22, 345, 16), // "gunFireRequested"
QT_MOC_LITERAL(23, 362, 16), // "gunSafetyToggled"
QT_MOC_LITERAL(24, 379, 7), // "enabled"
QT_MOC_LITERAL(25, 387, 16), // "gunRoundsChanged"
QT_MOC_LITERAL(26, 404, 6), // "rounds"
QT_MOC_LITERAL(27, 411, 18), // "missileTypeChanged"
QT_MOC_LITERAL(28, 430, 4), // "type"
QT_MOC_LITERAL(29, 435, 19), // "missileTargetLocked"
QT_MOC_LITERAL(30, 455, 7), // "trackId"
QT_MOC_LITERAL(31, 463, 22), // "missileLaunchRequested"
QT_MOC_LITERAL(32, 486, 21), // "missileAbortRequested"
QT_MOC_LITERAL(33, 508, 17), // "missileArmToggled"
QT_MOC_LITERAL(34, 526, 5), // "armed"
QT_MOC_LITERAL(35, 532, 15), // "eotsZoomChanged"
QT_MOC_LITERAL(36, 548, 4), // "zoom"
QT_MOC_LITERAL(37, 553, 21), // "eotsBrightnessChanged"
QT_MOC_LITERAL(38, 575, 10), // "brightness"
QT_MOC_LITERAL(39, 586, 19), // "eotsContrastChanged"
QT_MOC_LITERAL(40, 606, 8), // "contrast"
QT_MOC_LITERAL(41, 615, 17), // "eotsIRModeToggled"
QT_MOC_LITERAL(42, 633, 23), // "eotsLaserRangeRequested"
QT_MOC_LITERAL(43, 657, 19), // "eotsTrackingToggled"
QT_MOC_LITERAL(44, 677, 14), // "loggingStarted"
QT_MOC_LITERAL(45, 692, 14), // "loggingStopped"
QT_MOC_LITERAL(46, 707, 14), // "loggingCleared"
QT_MOC_LITERAL(47, 722, 16), // "recordingStarted"
QT_MOC_LITERAL(48, 739, 16), // "recordingStopped"
QT_MOC_LITERAL(49, 756, 15), // "recordingPaused"
QT_MOC_LITERAL(50, 772, 13), // "replayStarted"
QT_MOC_LITERAL(51, 786, 13), // "replayStopped"
QT_MOC_LITERAL(52, 800, 12), // "replayPaused"
QT_MOC_LITERAL(53, 813, 18), // "replaySpeedChanged"
QT_MOC_LITERAL(54, 832, 19), // "updateServoPosition"
QT_MOC_LITERAL(55, 852, 17), // "updateRadarStatus"
QT_MOC_LITERAL(56, 870, 6), // "status"
QT_MOC_LITERAL(57, 877, 15), // "updateGunStatus"
QT_MOC_LITERAL(58, 893, 15), // "roundsRemaining"
QT_MOC_LITERAL(59, 909, 19), // "updateMissileStatus"
QT_MOC_LITERAL(60, 929, 16), // "appendLogMessage"
QT_MOC_LITERAL(61, 946, 7) // "message"

    },
    "CInterfacesPanelWidget\0servoAzimuthChanged\0"
    "\0azimuth\0servoElevationChanged\0elevation\0"
    "servoSpeedChanged\0speed\0servoHomeRequested\0"
    "servoStopRequested\0servoCalibrationRequested\0"
    "radarModeChanged\0mode\0radarRangeChanged\0"
    "range\0radarGainChanged\0gain\0"
    "radarScanStartRequested\0radarScanStopRequested\0"
    "radarResetRequested\0gunAzimuthChanged\0"
    "gunElevationChanged\0gunFireRequested\0"
    "gunSafetyToggled\0enabled\0gunRoundsChanged\0"
    "rounds\0missileTypeChanged\0type\0"
    "missileTargetLocked\0trackId\0"
    "missileLaunchRequested\0missileAbortRequested\0"
    "missileArmToggled\0armed\0eotsZoomChanged\0"
    "zoom\0eotsBrightnessChanged\0brightness\0"
    "eotsContrastChanged\0contrast\0"
    "eotsIRModeToggled\0eotsLaserRangeRequested\0"
    "eotsTrackingToggled\0loggingStarted\0"
    "loggingStopped\0loggingCleared\0"
    "recordingStarted\0recordingStopped\0"
    "recordingPaused\0replayStarted\0"
    "replayStopped\0replayPaused\0"
    "replaySpeedChanged\0updateServoPosition\0"
    "updateRadarStatus\0status\0updateGunStatus\0"
    "roundsRemaining\0updateMissileStatus\0"
    "appendLogMessage\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CInterfacesPanelWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      38,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  229,    2, 0x06 /* Public */,
       4,    1,  232,    2, 0x06 /* Public */,
       6,    1,  235,    2, 0x06 /* Public */,
       8,    0,  238,    2, 0x06 /* Public */,
       9,    0,  239,    2, 0x06 /* Public */,
      10,    0,  240,    2, 0x06 /* Public */,
      11,    1,  241,    2, 0x06 /* Public */,
      13,    1,  244,    2, 0x06 /* Public */,
      15,    1,  247,    2, 0x06 /* Public */,
      17,    0,  250,    2, 0x06 /* Public */,
      18,    0,  251,    2, 0x06 /* Public */,
      19,    0,  252,    2, 0x06 /* Public */,
      20,    1,  253,    2, 0x06 /* Public */,
      21,    1,  256,    2, 0x06 /* Public */,
      22,    0,  259,    2, 0x06 /* Public */,
      23,    1,  260,    2, 0x06 /* Public */,
      25,    1,  263,    2, 0x06 /* Public */,
      27,    1,  266,    2, 0x06 /* Public */,
      29,    1,  269,    2, 0x06 /* Public */,
      31,    0,  272,    2, 0x06 /* Public */,
      32,    0,  273,    2, 0x06 /* Public */,
      33,    1,  274,    2, 0x06 /* Public */,
      35,    1,  277,    2, 0x06 /* Public */,
      37,    1,  280,    2, 0x06 /* Public */,
      39,    1,  283,    2, 0x06 /* Public */,
      41,    1,  286,    2, 0x06 /* Public */,
      42,    0,  289,    2, 0x06 /* Public */,
      43,    1,  290,    2, 0x06 /* Public */,
      44,    0,  293,    2, 0x06 /* Public */,
      45,    0,  294,    2, 0x06 /* Public */,
      46,    0,  295,    2, 0x06 /* Public */,
      47,    0,  296,    2, 0x06 /* Public */,
      48,    0,  297,    2, 0x06 /* Public */,
      49,    0,  298,    2, 0x06 /* Public */,
      50,    0,  299,    2, 0x06 /* Public */,
      51,    0,  300,    2, 0x06 /* Public */,
      52,    0,  301,    2, 0x06 /* Public */,
      53,    1,  302,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      54,    2,  305,    2, 0x0a /* Public */,
      55,    1,  310,    2, 0x0a /* Public */,
      57,    1,  313,    2, 0x0a /* Public */,
      59,    1,  316,    2, 0x0a /* Public */,
      60,    1,  319,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Double,   36,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    5,
    QMetaType::Void, QMetaType::QString,   56,
    QMetaType::Void, QMetaType::Int,   58,
    QMetaType::Void, QMetaType::QString,   56,
    QMetaType::Void, QMetaType::QString,   61,

       0        // eod
};

void CInterfacesPanelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CInterfacesPanelWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->servoAzimuthChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->servoElevationChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->servoSpeedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->servoHomeRequested(); break;
        case 4: _t->servoStopRequested(); break;
        case 5: _t->servoCalibrationRequested(); break;
        case 6: _t->radarModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->radarRangeChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->radarGainChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->radarScanStartRequested(); break;
        case 10: _t->radarScanStopRequested(); break;
        case 11: _t->radarResetRequested(); break;
        case 12: _t->gunAzimuthChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->gunElevationChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->gunFireRequested(); break;
        case 15: _t->gunSafetyToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->gunRoundsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->missileTypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->missileTargetLocked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->missileLaunchRequested(); break;
        case 20: _t->missileAbortRequested(); break;
        case 21: _t->missileArmToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->eotsZoomChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->eotsBrightnessChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->eotsContrastChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->eotsIRModeToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->eotsLaserRangeRequested(); break;
        case 27: _t->eotsTrackingToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->loggingStarted(); break;
        case 29: _t->loggingStopped(); break;
        case 30: _t->loggingCleared(); break;
        case 31: _t->recordingStarted(); break;
        case 32: _t->recordingStopped(); break;
        case 33: _t->recordingPaused(); break;
        case 34: _t->replayStarted(); break;
        case 35: _t->replayStopped(); break;
        case 36: _t->replayPaused(); break;
        case 37: _t->replaySpeedChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 38: _t->updateServoPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 39: _t->updateRadarStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 40: _t->updateGunStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->updateMissileStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 42: _t->appendLogMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CInterfacesPanelWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::servoAzimuthChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::servoElevationChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::servoSpeedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::servoHomeRequested)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::servoStopRequested)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::servoCalibrationRequested)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::radarModeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::radarRangeChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::radarGainChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::radarScanStartRequested)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::radarScanStopRequested)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::radarResetRequested)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::gunAzimuthChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::gunElevationChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::gunFireRequested)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::gunSafetyToggled)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::gunRoundsChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::missileTypeChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::missileTargetLocked)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::missileLaunchRequested)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::missileAbortRequested)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::missileArmToggled)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::eotsZoomChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::eotsBrightnessChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::eotsContrastChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::eotsIRModeToggled)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::eotsLaserRangeRequested)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::eotsTrackingToggled)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::loggingStarted)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::loggingStopped)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::loggingCleared)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::recordingStarted)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::recordingStopped)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::recordingPaused)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::replayStarted)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::replayStopped)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::replayPaused)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (CInterfacesPanelWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CInterfacesPanelWidget::replaySpeedChanged)) {
                *result = 37;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CInterfacesPanelWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_CInterfacesPanelWidget.data,
    qt_meta_data_CInterfacesPanelWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CInterfacesPanelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CInterfacesPanelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CInterfacesPanelWidget.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int CInterfacesPanelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void CInterfacesPanelWidget::servoAzimuthChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CInterfacesPanelWidget::servoElevationChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CInterfacesPanelWidget::servoSpeedChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CInterfacesPanelWidget::servoHomeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CInterfacesPanelWidget::servoStopRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CInterfacesPanelWidget::servoCalibrationRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CInterfacesPanelWidget::radarModeChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CInterfacesPanelWidget::radarRangeChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CInterfacesPanelWidget::radarGainChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CInterfacesPanelWidget::radarScanStartRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void CInterfacesPanelWidget::radarScanStopRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void CInterfacesPanelWidget::radarResetRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void CInterfacesPanelWidget::gunAzimuthChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void CInterfacesPanelWidget::gunElevationChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void CInterfacesPanelWidget::gunFireRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void CInterfacesPanelWidget::gunSafetyToggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void CInterfacesPanelWidget::gunRoundsChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void CInterfacesPanelWidget::missileTypeChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void CInterfacesPanelWidget::missileTargetLocked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void CInterfacesPanelWidget::missileLaunchRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void CInterfacesPanelWidget::missileAbortRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void CInterfacesPanelWidget::missileArmToggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void CInterfacesPanelWidget::eotsZoomChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void CInterfacesPanelWidget::eotsBrightnessChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void CInterfacesPanelWidget::eotsContrastChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void CInterfacesPanelWidget::eotsIRModeToggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void CInterfacesPanelWidget::eotsLaserRangeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 26, nullptr);
}

// SIGNAL 27
void CInterfacesPanelWidget::eotsTrackingToggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void CInterfacesPanelWidget::loggingStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 28, nullptr);
}

// SIGNAL 29
void CInterfacesPanelWidget::loggingStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 29, nullptr);
}

// SIGNAL 30
void CInterfacesPanelWidget::loggingCleared()
{
    QMetaObject::activate(this, &staticMetaObject, 30, nullptr);
}

// SIGNAL 31
void CInterfacesPanelWidget::recordingStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 31, nullptr);
}

// SIGNAL 32
void CInterfacesPanelWidget::recordingStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 32, nullptr);
}

// SIGNAL 33
void CInterfacesPanelWidget::recordingPaused()
{
    QMetaObject::activate(this, &staticMetaObject, 33, nullptr);
}

// SIGNAL 34
void CInterfacesPanelWidget::replayStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 34, nullptr);
}

// SIGNAL 35
void CInterfacesPanelWidget::replayStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 35, nullptr);
}

// SIGNAL 36
void CInterfacesPanelWidget::replayPaused()
{
    QMetaObject::activate(this, &staticMetaObject, 36, nullptr);
}

// SIGNAL 37
void CInterfacesPanelWidget::replaySpeedChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

#ifndef CINTERFACESWIDGET_H
#define CINTERFACESWIDGET_H

#include <QDockWidget>
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QProgressBar>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QListWidget>
#include <QTimer>
#include <QFileDialog>
#include <QDateTime>

class CInterfacesWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CInterfacesWidget(QWidget *parent = nullptr);
    ~CInterfacesWidget();

private slots:
    // Servo Controller slots
    void onServoAzimuthChanged(double value);
    void onServoElevationChanged(double value);
    void onServoSpeedChanged(int value);
    void onServoHomeClicked();
    void onServoStopClicked();
    void onServoModeChanged(const QString &mode);
    
    // Radar Controller slots
    void onRadarPowerToggled(bool enabled);
    void onRadarModeChanged(const QString &mode);
    void onRadarRangeChanged(int range);
    void onRadarScanRateChanged(int rate);
    void onRadarGainChanged(int gain);
    
    // Gun Controller slots
    void onGunPowerToggled(bool enabled);
    void onGunModeChanged(const QString &mode);
    void onGunElevationChanged(double elevation);
    void onGunAzimuthChanged(double azimuth);
    void onGunFireClicked();
    void onGunSafetyToggled(bool enabled);
    
    // Missile Controller slots
    void onMissilePowerToggled(bool enabled);
    void onMissileTypeChanged(const QString &type);
    void onMissileLaunchClicked();
    void onMissileAbortClicked();
    void onMissileTargetLockToggled(bool locked);
    
    // EOTS (Electro-Optical Targeting System) slots
    void onEotsPowerToggled(bool enabled);
    void onEotsModeChanged(const QString &mode);
    void onEotsZoomChanged(int zoom);
    void onEotsTrackingToggled(bool enabled);
    void onEotsCalibrateClicked();
    
    // Logging slots
    void onLoggingToggled(bool enabled);
    void onLogLevelChanged(const QString &level);
    void onLogSaveClicked();
    void onLogClearClicked();
    void updateLogDisplay();
    
    // Screen Recording slots
    void onRecordingToggled(bool enabled);
    void onRecordingQualityChanged(const QString &quality);
    void onRecordingSaveClicked();
    void onRecordingStopClicked();
    
    // Replay System slots
    void onReplayLoadClicked();
    void onReplayPlayClicked();
    void onReplayPauseClicked();
    void onReplayStopClicked();
    void onReplaySpeedChanged(double speed);
    void onReplayPositionChanged(int position);

signals:
    // Servo signals
    void servoPositionChanged(double azimuth, double elevation);
    void servoModeChanged(const QString &mode);
    
    // Radar signals
    void radarConfigChanged(bool power, const QString &mode, int range, int scanRate, int gain);
    
    // Gun signals
    void gunConfigChanged(bool power, const QString &mode, double elevation, double azimuth);
    void gunFired();
    
    // Missile signals
    void missileConfigChanged(bool power, const QString &type);
    void missileLaunched();
    void missileAborted();
    
    // EOTS signals
    void eotsConfigChanged(bool power, const QString &mode, int zoom, bool tracking);
    
    // System signals
    void loggingStateChanged(bool enabled, const QString &level);
    void recordingStateChanged(bool enabled, const QString &quality);
    void replayStateChanged(const QString &action, double speed);

private:
    void setupUI();
    void setupServoController();
    void setupRadarController();
    void setupGunController();
    void setupMissileController();
    void setupEotsController();
    void setupLoggingPanel();
    void setupRecordingPanel();
    void setupReplayPanel();
    void applyModernTheme();
    
    // Main UI components
    QTabWidget *m_tabWidget;
    
    // Controller tabs
    QWidget *m_servoTab;
    QWidget *m_radarTab;
    QWidget *m_gunTab;
    QWidget *m_missileTab;
    QWidget *m_eotsTab;
    QWidget *m_systemTab;
    
    // Servo Controller components
    QDoubleSpinBox *m_servoAzimuth;
    QDoubleSpinBox *m_servoElevation;
    QSlider *m_servoSpeed;
    QPushButton *m_servoHome;
    QPushButton *m_servoStop;
    QComboBox *m_servoMode;
    QLabel *m_servoStatus;
    QProgressBar *m_servoProgress;
    
    // Radar Controller components
    QCheckBox *m_radarPower;
    QComboBox *m_radarMode;
    QSpinBox *m_radarRange;
    QSlider *m_radarScanRate;
    QSlider *m_radarGain;
    QLabel *m_radarStatus;
    QProgressBar *m_radarSignalStrength;
    
    // Gun Controller components
    QCheckBox *m_gunPower;
    QComboBox *m_gunMode;
    QDoubleSpinBox *m_gunElevation;
    QDoubleSpinBox *m_gunAzimuth;
    QPushButton *m_gunFire;
    QCheckBox *m_gunSafety;
    QLabel *m_gunStatus;
    QProgressBar *m_gunAmmo;
    
    // Missile Controller components
    QCheckBox *m_missilePower;
    QComboBox *m_missileType;
    QPushButton *m_missileLaunch;
    QPushButton *m_missileAbort;
    QCheckBox *m_missileTargetLock;
    QLabel *m_missileStatus;
    QProgressBar *m_missileReadiness;
    
    // EOTS components
    QCheckBox *m_eotsPower;
    QComboBox *m_eotsMode;
    QSlider *m_eotsZoom;
    QCheckBox *m_eotsTracking;
    QPushButton *m_eotsCalibrate;
    QLabel *m_eotsStatus;
    
    // System components (Logging, Recording, Replay)
    QCheckBox *m_loggingEnabled;
    QComboBox *m_logLevel;
    QPushButton *m_logSave;
    QPushButton *m_logClear;
    QTextEdit *m_logDisplay;
    
    QCheckBox *m_recordingEnabled;
    QComboBox *m_recordingQuality;
    QPushButton *m_recordingSave;
    QPushButton *m_recordingStop;
    QLabel *m_recordingStatus;
    
    QPushButton *m_replayLoad;
    QPushButton *m_replayPlay;
    QPushButton *m_replayPause;
    QPushButton *m_replayStop;
    QDoubleSpinBox *m_replaySpeed;
    QSlider *m_replayPosition;
    QLabel *m_replayStatus;
    
    // Timers and state
    QTimer *m_updateTimer;
    QTimer *m_logTimer;
    bool m_isRecording;
    bool m_isReplaying;
    QString m_currentLogFile;
    QString m_currentRecordingFile;
    QString m_currentReplayFile;
};

#endif // CINTERFACESWIDGET_H
#include "cinterfaceswidget.h"
#include <QApplication>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>

CInterfacesWidget::CInterfacesWidget(QWidget *parent)
    : QDockWidget("🎛️ System Interfaces", parent)
    , m_tabWidget(nullptr)
    , m_updateTimer(new QTimer(this))
    , m_logTimer(new QTimer(this))
    , m_isRecording(false)
    , m_isReplaying(false)
{
    setupUI();
    applyModernTheme();
    
    // Setup update timers
    connect(m_updateTimer, &QTimer::timeout, this, &CInterfacesWidget::updateLogDisplay);
    m_updateTimer->start(1000); // Update every second
    
    connect(m_logTimer, &QTimer::timeout, this, [this]() {
        if (m_loggingEnabled && m_loggingEnabled->isChecked()) {
            QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
            QString logEntry = QString("[%1] System operational - All controllers active").arg(timestamp);
            if (m_logDisplay) {
                m_logDisplay->append(logEntry);
            }
        }
    });
    m_logTimer->start(5000); // Log every 5 seconds when enabled
}

CInterfacesWidget::~CInterfacesWidget()
{
}

void CInterfacesWidget::setupUI()
{
    // Create main widget and layout
    QWidget *mainWidget = new QWidget(this);
    setWidget(mainWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(6);
    
    // Create tab widget
    m_tabWidget = new QTabWidget(mainWidget);
    mainLayout->addWidget(m_tabWidget);
    
    // Setup all controller tabs
    setupServoController();
    setupRadarController();
    setupGunController();
    setupMissileController();
    setupEotsController();
    setupLoggingPanel();
    setupRecordingPanel();
    setupReplayPanel();
    
    // Add system tab that contains logging, recording, and replay
    m_systemTab = new QWidget();
    QVBoxLayout *systemLayout = new QVBoxLayout(m_systemTab);
    
    // Create sub-tabs for system functions
    QTabWidget *systemSubTabs = new QTabWidget();
    
    // Logging tab
    QWidget *loggingWidget = new QWidget();
    QVBoxLayout *loggingLayout = new QVBoxLayout(loggingWidget);
    
    QGroupBox *loggingGroup = new QGroupBox("📝 System Logging");
    QGridLayout *loggingGridLayout = new QGridLayout(loggingGroup);
    
    loggingGridLayout->addWidget(m_loggingEnabled, 0, 0);
    loggingGridLayout->addWidget(new QLabel("Log Level:"), 0, 1);
    loggingGridLayout->addWidget(m_logLevel, 0, 2);
    loggingGridLayout->addWidget(m_logSave, 1, 0);
    loggingGridLayout->addWidget(m_logClear, 1, 1);
    
    loggingLayout->addWidget(loggingGroup);
    loggingLayout->addWidget(m_logDisplay);
    
    // Recording tab
    QWidget *recordingWidget = new QWidget();
    QVBoxLayout *recordingLayout = new QVBoxLayout(recordingWidget);
    
    QGroupBox *recordingGroup = new QGroupBox("🎥 Screen Recording");
    QGridLayout *recordingGridLayout = new QGridLayout(recordingGroup);
    
    recordingGridLayout->addWidget(m_recordingEnabled, 0, 0);
    recordingGridLayout->addWidget(new QLabel("Quality:"), 0, 1);
    recordingGridLayout->addWidget(m_recordingQuality, 0, 2);
    recordingGridLayout->addWidget(m_recordingSave, 1, 0);
    recordingGridLayout->addWidget(m_recordingStop, 1, 1);
    recordingGridLayout->addWidget(m_recordingStatus, 2, 0, 1, 3);
    
    recordingLayout->addWidget(recordingGroup);
    recordingLayout->addStretch();
    
    // Replay tab
    QWidget *replayWidget = new QWidget();
    QVBoxLayout *replayLayout = new QVBoxLayout(replayWidget);
    
    QGroupBox *replayGroup = new QGroupBox("⏯️ Session Replay");
    QGridLayout *replayGridLayout = new QGridLayout(replayGroup);
    
    replayGridLayout->addWidget(m_replayLoad, 0, 0);
    replayGridLayout->addWidget(m_replayPlay, 0, 1);
    replayGridLayout->addWidget(m_replayPause, 0, 2);
    replayGridLayout->addWidget(m_replayStop, 0, 3);
    replayGridLayout->addWidget(new QLabel("Speed:"), 1, 0);
    replayGridLayout->addWidget(m_replaySpeed, 1, 1);
    replayGridLayout->addWidget(new QLabel("Position:"), 2, 0);
    replayGridLayout->addWidget(m_replayPosition, 2, 1, 1, 3);
    replayGridLayout->addWidget(m_replayStatus, 3, 0, 1, 4);
    
    replayLayout->addWidget(replayGroup);
    replayLayout->addStretch();
    
    // Add sub-tabs
    systemSubTabs->addTab(loggingWidget, "📝 Logging");
    systemSubTabs->addTab(recordingWidget, "🎥 Recording");
    systemSubTabs->addTab(replayWidget, "⏯️ Replay");
    
    systemLayout->addWidget(systemSubTabs);
    
    m_tabWidget->addTab(m_systemTab, "🖥️ System");
}

void CInterfacesWidget::setupServoController()
{
    m_servoTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_servoTab);
    
    // Position Control Group
    QGroupBox *positionGroup = new QGroupBox("🎯 Position Control");
    QGridLayout *positionLayout = new QGridLayout(positionGroup);
    
    // Azimuth control
    positionLayout->addWidget(new QLabel("Azimuth (°):"), 0, 0);
    m_servoAzimuth = new QDoubleSpinBox();
    m_servoAzimuth->setRange(-180.0, 180.0);
    m_servoAzimuth->setSingleStep(0.1);
    m_servoAzimuth->setSuffix("°");
    positionLayout->addWidget(m_servoAzimuth, 0, 1);
    
    // Elevation control
    positionLayout->addWidget(new QLabel("Elevation (°):"), 1, 0);
    m_servoElevation = new QDoubleSpinBox();
    m_servoElevation->setRange(-90.0, 90.0);
    m_servoElevation->setSingleStep(0.1);
    m_servoElevation->setSuffix("°");
    positionLayout->addWidget(m_servoElevation, 1, 1);
    
    // Speed control
    positionLayout->addWidget(new QLabel("Speed:"), 2, 0);
    m_servoSpeed = new QSlider(Qt::Horizontal);
    m_servoSpeed->setRange(1, 100);
    m_servoSpeed->setValue(50);
    positionLayout->addWidget(m_servoSpeed, 2, 1);
    
    layout->addWidget(positionGroup);
    
    // Control Group
    QGroupBox *controlGroup = new QGroupBox("⚙️ Control");
    QGridLayout *controlLayout = new QGridLayout(controlGroup);
    
    // Mode selection
    controlLayout->addWidget(new QLabel("Mode:"), 0, 0);
    m_servoMode = new QComboBox();
    m_servoMode->addItems({"Manual", "Auto Track", "Scan", "Standby"});
    controlLayout->addWidget(m_servoMode, 0, 1);
    
    // Control buttons
    m_servoHome = new QPushButton("🏠 Home");
    m_servoStop = new QPushButton("⏹️ Stop");
    controlLayout->addWidget(m_servoHome, 1, 0);
    controlLayout->addWidget(m_servoStop, 1, 1);
    
    layout->addWidget(controlGroup);
    
    // Status Group
    QGroupBox *statusGroup = new QGroupBox("📊 Status");
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
    
    m_servoStatus = new QLabel("Status: Ready");
    m_servoProgress = new QProgressBar();
    m_servoProgress->setRange(0, 100);
    m_servoProgress->setValue(0);
    
    statusLayout->addWidget(m_servoStatus);
    statusLayout->addWidget(m_servoProgress);
    
    layout->addWidget(statusGroup);
    layout->addStretch();
    
    // Connect signals
    connect(m_servoAzimuth, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &CInterfacesWidget::onServoAzimuthChanged);
    connect(m_servoElevation, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &CInterfacesWidget::onServoElevationChanged);
    connect(m_servoSpeed, &QSlider::valueChanged, this, &CInterfacesWidget::onServoSpeedChanged);
    connect(m_servoHome, &QPushButton::clicked, this, &CInterfacesWidget::onServoHomeClicked);
    connect(m_servoStop, &QPushButton::clicked, this, &CInterfacesWidget::onServoStopClicked);
    connect(m_servoMode, &QComboBox::currentTextChanged, this, &CInterfacesWidget::onServoModeChanged);
    
    m_tabWidget->addTab(m_servoTab, "🎯 Servo");
}

void CInterfacesWidget::setupRadarController()
{
    m_radarTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_radarTab);
    
    // Power and Mode Group
    QGroupBox *powerGroup = new QGroupBox("⚡ Power & Mode");
    QGridLayout *powerLayout = new QGridLayout(powerGroup);
    
    m_radarPower = new QCheckBox("Radar Power");
    m_radarMode = new QComboBox();
    m_radarMode->addItems({"Search", "Track", "Weather", "Navigation", "Test"});
    
    powerLayout->addWidget(m_radarPower, 0, 0);
    powerLayout->addWidget(new QLabel("Mode:"), 0, 1);
    powerLayout->addWidget(m_radarMode, 0, 2);
    
    layout->addWidget(powerGroup);
    
    // Configuration Group
    QGroupBox *configGroup = new QGroupBox("⚙️ Configuration");
    QGridLayout *configLayout = new QGridLayout(configGroup);
    
    // Range control
    configLayout->addWidget(new QLabel("Range (km):"), 0, 0);
    m_radarRange = new QSpinBox();
    m_radarRange->setRange(1, 500);
    m_radarRange->setValue(50);
    m_radarRange->setSuffix(" km");
    configLayout->addWidget(m_radarRange, 0, 1);
    
    // Scan rate
    configLayout->addWidget(new QLabel("Scan Rate:"), 1, 0);
    m_radarScanRate = new QSlider(Qt::Horizontal);
    m_radarScanRate->setRange(1, 10);
    m_radarScanRate->setValue(5);
    configLayout->addWidget(m_radarScanRate, 1, 1);
    
    // Gain control
    configLayout->addWidget(new QLabel("Gain:"), 2, 0);
    m_radarGain = new QSlider(Qt::Horizontal);
    m_radarGain->setRange(0, 100);
    m_radarGain->setValue(75);
    configLayout->addWidget(m_radarGain, 2, 1);
    
    layout->addWidget(configGroup);
    
    // Status Group
    QGroupBox *statusGroup = new QGroupBox("📊 Status");
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
    
    m_radarStatus = new QLabel("Status: Offline");
    m_radarSignalStrength = new QProgressBar();
    m_radarSignalStrength->setRange(0, 100);
    m_radarSignalStrength->setValue(0);
    
    statusLayout->addWidget(m_radarStatus);
    statusLayout->addWidget(new QLabel("Signal Strength:"));
    statusLayout->addWidget(m_radarSignalStrength);
    
    layout->addWidget(statusGroup);
    layout->addStretch();
    
    // Connect signals
    connect(m_radarPower, &QCheckBox::toggled, this, &CInterfacesWidget::onRadarPowerToggled);
    connect(m_radarMode, &QComboBox::currentTextChanged, this, &CInterfacesWidget::onRadarModeChanged);
    connect(m_radarRange, QOverload<int>::of(&QSpinBox::valueChanged), this, &CInterfacesWidget::onRadarRangeChanged);
    connect(m_radarScanRate, &QSlider::valueChanged, this, &CInterfacesWidget::onRadarScanRateChanged);
    connect(m_radarGain, &QSlider::valueChanged, this, &CInterfacesWidget::onRadarGainChanged);
    
    m_tabWidget->addTab(m_radarTab, "📡 Radar");
}

void CInterfacesWidget::setupGunController()
{
    m_gunTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_gunTab);
    
    // Power and Safety Group
    QGroupBox *safetyGroup = new QGroupBox("🔒 Safety & Power");
    QGridLayout *safetyLayout = new QGridLayout(safetyGroup);
    
    m_gunPower = new QCheckBox("Gun Power");
    m_gunSafety = new QCheckBox("Safety Lock");
    m_gunSafety->setChecked(true); // Default to safe
    
    safetyLayout->addWidget(m_gunPower, 0, 0);
    safetyLayout->addWidget(m_gunSafety, 0, 1);
    
    layout->addWidget(safetyGroup);
    
    // Control Group
    QGroupBox *controlGroup = new QGroupBox("🎯 Control");
    QGridLayout *controlLayout = new QGridLayout(controlGroup);
    
    // Mode selection
    controlLayout->addWidget(new QLabel("Mode:"), 0, 0);
    m_gunMode = new QComboBox();
    m_gunMode->addItems({"Manual", "Auto", "Burst", "Single"});
    controlLayout->addWidget(m_gunMode, 0, 1);
    
    // Position controls
    controlLayout->addWidget(new QLabel("Elevation (°):"), 1, 0);
    m_gunElevation = new QDoubleSpinBox();
    m_gunElevation->setRange(-10.0, 85.0);
    m_gunElevation->setSingleStep(0.1);
    m_gunElevation->setSuffix("°");
    controlLayout->addWidget(m_gunElevation, 1, 1);
    
    controlLayout->addWidget(new QLabel("Azimuth (°):"), 2, 0);
    m_gunAzimuth = new QDoubleSpinBox();
    m_gunAzimuth->setRange(-180.0, 180.0);
    m_gunAzimuth->setSingleStep(0.1);
    m_gunAzimuth->setSuffix("°");
    controlLayout->addWidget(m_gunAzimuth, 2, 1);
    
    // Fire button
    m_gunFire = new QPushButton("🔥 FIRE");
    m_gunFire->setEnabled(false); // Disabled by default
    controlLayout->addWidget(m_gunFire, 3, 0, 1, 2);
    
    layout->addWidget(controlGroup);
    
    // Status Group
    QGroupBox *statusGroup = new QGroupBox("📊 Status");
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
    
    m_gunStatus = new QLabel("Status: Safe");
    m_gunAmmo = new QProgressBar();
    m_gunAmmo->setRange(0, 100);
    m_gunAmmo->setValue(100);
    
    statusLayout->addWidget(m_gunStatus);
    statusLayout->addWidget(new QLabel("Ammunition:"));
    statusLayout->addWidget(m_gunAmmo);
    
    layout->addWidget(statusGroup);
    layout->addStretch();
    
    // Connect signals
    connect(m_gunPower, &QCheckBox::toggled, this, &CInterfacesWidget::onGunPowerToggled);
    connect(m_gunMode, &QComboBox::currentTextChanged, this, &CInterfacesWidget::onGunModeChanged);
    connect(m_gunElevation, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CInterfacesWidget::onGunElevationChanged);
    connect(m_gunAzimuth, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CInterfacesWidget::onGunAzimuthChanged);
    connect(m_gunFire, &QPushButton::clicked, this, &CInterfacesWidget::onGunFireClicked);
    connect(m_gunSafety, &QCheckBox::toggled, this, &CInterfacesWidget::onGunSafetyToggled);
    
    m_tabWidget->addTab(m_gunTab, "🔫 Gun");
}

void CInterfacesWidget::setupMissileController()
{
    m_missileTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_missileTab);
    
    // Power and Type Group
    QGroupBox *configGroup = new QGroupBox("⚡ Configuration");
    QGridLayout *configLayout = new QGridLayout(configGroup);
    
    m_missilePower = new QCheckBox("Missile System Power");
    configLayout->addWidget(m_missilePower, 0, 0);
    
    configLayout->addWidget(new QLabel("Missile Type:"), 1, 0);
    m_missileType = new QComboBox();
    m_missileType->addItems({"Air-to-Air", "Air-to-Ground", "Anti-Ship", "SEAD"});
    configLayout->addWidget(m_missileType, 1, 1);
    
    layout->addWidget(configGroup);
    
    // Control Group
    QGroupBox *controlGroup = new QGroupBox("🚀 Launch Control");
    QGridLayout *controlLayout = new QGridLayout(controlGroup);
    
    m_missileTargetLock = new QCheckBox("Target Lock");
    m_missileLaunch = new QPushButton("🚀 LAUNCH");
    m_missileAbort = new QPushButton("⛔ ABORT");
    
    m_missileLaunch->setEnabled(false);
    m_missileAbort->setEnabled(false);
    
    controlLayout->addWidget(m_missileTargetLock, 0, 0);
    controlLayout->addWidget(m_missileLaunch, 1, 0);
    controlLayout->addWidget(m_missileAbort, 1, 1);
    
    layout->addWidget(controlGroup);
    
    // Status Group
    QGroupBox *statusGroup = new QGroupBox("📊 Status");
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
    
    m_missileStatus = new QLabel("Status: Offline");
    m_missileReadiness = new QProgressBar();
    m_missileReadiness->setRange(0, 100);
    m_missileReadiness->setValue(0);
    
    statusLayout->addWidget(m_missileStatus);
    statusLayout->addWidget(new QLabel("System Readiness:"));
    statusLayout->addWidget(m_missileReadiness);
    
    layout->addWidget(statusGroup);
    layout->addStretch();
    
    // Connect signals
    connect(m_missilePower, &QCheckBox::toggled, this, &CInterfacesWidget::onMissilePowerToggled);
    connect(m_missileType, &QComboBox::currentTextChanged, this, &CInterfacesWidget::onMissileTypeChanged);
    connect(m_missileLaunch, &QPushButton::clicked, this, &CInterfacesWidget::onMissileLaunchClicked);
    connect(m_missileAbort, &QPushButton::clicked, this, &CInterfacesWidget::onMissileAbortClicked);
    connect(m_missileTargetLock, &QCheckBox::toggled, this, &CInterfacesWidget::onMissileTargetLockToggled);
    
    m_tabWidget->addTab(m_missileTab, "🚀 Missile");
}

void CInterfacesWidget::setupEotsController()
{
    m_eotsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_eotsTab);
    
    // Power and Mode Group
    QGroupBox *powerGroup = new QGroupBox("⚡ Power & Mode");
    QGridLayout *powerLayout = new QGridLayout(powerGroup);
    
    m_eotsPower = new QCheckBox("EOTS Power");
    powerLayout->addWidget(m_eotsPower, 0, 0);
    
    powerLayout->addWidget(new QLabel("Mode:"), 0, 1);
    m_eotsMode = new QComboBox();
    m_eotsMode->addItems({"IR", "TV", "Laser", "Multi-Spectral"});
    powerLayout->addWidget(m_eotsMode, 0, 2);
    
    layout->addWidget(powerGroup);
    
    // Control Group
    QGroupBox *controlGroup = new QGroupBox("🔍 Optical Control");
    QGridLayout *controlLayout = new QGridLayout(controlGroup);
    
    // Zoom control
    controlLayout->addWidget(new QLabel("Zoom Level:"), 0, 0);
    m_eotsZoom = new QSlider(Qt::Horizontal);
    m_eotsZoom->setRange(1, 50);
    m_eotsZoom->setValue(1);
    controlLayout->addWidget(m_eotsZoom, 0, 1);
    
    // Tracking
    m_eotsTracking = new QCheckBox("Auto Tracking");
    controlLayout->addWidget(m_eotsTracking, 1, 0);
    
    // Calibration
    m_eotsCalibrate = new QPushButton("🎯 Calibrate");
    controlLayout->addWidget(m_eotsCalibrate, 1, 1);
    
    layout->addWidget(controlGroup);
    
    // Status Group
    QGroupBox *statusGroup = new QGroupBox("📊 Status");
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
    
    m_eotsStatus = new QLabel("Status: Offline");
    statusLayout->addWidget(m_eotsStatus);
    
    layout->addWidget(statusGroup);
    layout->addStretch();
    
    // Connect signals
    connect(m_eotsPower, &QCheckBox::toggled, this, &CInterfacesWidget::onEotsPowerToggled);
    connect(m_eotsMode, &QComboBox::currentTextChanged, this, &CInterfacesWidget::onEotsModeChanged);
    connect(m_eotsZoom, &QSlider::valueChanged, this, &CInterfacesWidget::onEotsZoomChanged);
    connect(m_eotsTracking, &QCheckBox::toggled, this, &CInterfacesWidget::onEotsTrackingToggled);
    connect(m_eotsCalibrate, &QPushButton::clicked, this, &CInterfacesWidget::onEotsCalibrateClicked);
    
    m_tabWidget->addTab(m_eotsTab, "👁️ EOTS");
}

void CInterfacesWidget::setupLoggingPanel()
{
    // Create logging components
    m_loggingEnabled = new QCheckBox("Enable Logging");
    m_logLevel = new QComboBox();
    m_logLevel->addItems({"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"});
    m_logLevel->setCurrentText("INFO");
    
    m_logSave = new QPushButton("💾 Save Log");
    m_logClear = new QPushButton("🗑️ Clear Log");
    
    m_logDisplay = new QTextEdit();
    m_logDisplay->setMaximumHeight(200);
    m_logDisplay->setReadOnly(true);
    m_logDisplay->setStyleSheet("background-color: #000000; color: #00ff00; font-family: 'Courier New';");
    
    // Connect signals
    connect(m_loggingEnabled, &QCheckBox::toggled, this, &CInterfacesWidget::onLoggingToggled);
    connect(m_logLevel, &QComboBox::currentTextChanged, this, &CInterfacesWidget::onLogLevelChanged);
    connect(m_logSave, &QPushButton::clicked, this, &CInterfacesWidget::onLogSaveClicked);
    connect(m_logClear, &QPushButton::clicked, this, &CInterfacesWidget::onLogClearClicked);
}

void CInterfacesWidget::setupRecordingPanel()
{
    // Create recording components
    m_recordingEnabled = new QCheckBox("Enable Recording");
    m_recordingQuality = new QComboBox();
    m_recordingQuality->addItems({"720p", "1080p", "1440p", "4K"});
    m_recordingQuality->setCurrentText("1080p");
    
    m_recordingSave = new QPushButton("💾 Save Recording");
    m_recordingStop = new QPushButton("⏹️ Stop Recording");
    m_recordingStatus = new QLabel("Status: Ready");
    
    m_recordingSave->setEnabled(false);
    m_recordingStop->setEnabled(false);
    
    // Connect signals
    connect(m_recordingEnabled, &QCheckBox::toggled, this, &CInterfacesWidget::onRecordingToggled);
    connect(m_recordingQuality, &QComboBox::currentTextChanged, this, &CInterfacesWidget::onRecordingQualityChanged);
    connect(m_recordingSave, &QPushButton::clicked, this, &CInterfacesWidget::onRecordingSaveClicked);
    connect(m_recordingStop, &QPushButton::clicked, this, &CInterfacesWidget::onRecordingStopClicked);
}

void CInterfacesWidget::setupReplayPanel()
{
    // Create replay components
    m_replayLoad = new QPushButton("📁 Load Session");
    m_replayPlay = new QPushButton("▶️ Play");
    m_replayPause = new QPushButton("⏸️ Pause");
    m_replayStop = new QPushButton("⏹️ Stop");
    
    m_replaySpeed = new QDoubleSpinBox();
    m_replaySpeed->setRange(0.1, 5.0);
    m_replaySpeed->setSingleStep(0.1);
    m_replaySpeed->setValue(1.0);
    m_replaySpeed->setSuffix("x");
    
    m_replayPosition = new QSlider(Qt::Horizontal);
    m_replayPosition->setRange(0, 100);
    m_replayPosition->setValue(0);
    
    m_replayStatus = new QLabel("Status: No session loaded");
    
    // Initially disable controls
    m_replayPlay->setEnabled(false);
    m_replayPause->setEnabled(false);
    m_replayStop->setEnabled(false);
    m_replaySpeed->setEnabled(false);
    m_replayPosition->setEnabled(false);
    
    // Connect signals
    connect(m_replayLoad, &QPushButton::clicked, this, &CInterfacesWidget::onReplayLoadClicked);
    connect(m_replayPlay, &QPushButton::clicked, this, &CInterfacesWidget::onReplayPlayClicked);
    connect(m_replayPause, &QPushButton::clicked, this, &CInterfacesWidget::onReplayPauseClicked);
    connect(m_replayStop, &QPushButton::clicked, this, &CInterfacesWidget::onReplayStopClicked);
    connect(m_replaySpeed, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CInterfacesWidget::onReplaySpeedChanged);
    connect(m_replayPosition, &QSlider::valueChanged, this, &CInterfacesWidget::onReplayPositionChanged);
}

void CInterfacesWidget::applyModernTheme()
{
    setStyleSheet(
        "QDockWidget {"
        "   background-color: #1a202c;"
        "   color: #ffffff;"
        "   border: 2px solid #4a5568;"
        "   border-radius: 8px;"
        "}"
        "QDockWidget::title {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "   color: white;"
        "   padding: 8px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "}"
        "QTabWidget::pane {"
        "   border: 2px solid #4a5568;"
        "   border-radius: 8px;"
        "   background-color: #2d3748;"
        "}"
        "QTabBar::tab {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4a5568, stop:1 #2d3748);"
        "   color: #ffffff;"
        "   padding: 8px 16px;"
        "   margin-right: 2px;"
        "   border-top-left-radius: 6px;"
        "   border-top-right-radius: 6px;"
        "   font-weight: 500;"
        "}"
        "QTabBar::tab:selected {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #667eea, stop:1 #764ba2);"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        "QTabBar::tab:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #5a67d8, stop:1 #6b46c1);"
        "}"
        "QGroupBox {"
        "   background-color: #2d3748;"
        "   border: 2px solid #4a5568;"
        "   border-radius: 8px;"
        "   margin-top: 12px;"
        "   padding-top: 12px;"
        "   font-weight: bold;"
        "   color: #ffffff;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top left;"
        "   padding: 4px 8px;"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "   border-radius: 4px;"
        "   color: white;"
        "   font-size: 12px;"
        "}"
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #667eea, stop:1 #764ba2);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 8px 12px;"
        "   font-weight: bold;"
        "   font-size: 11px;"
        "   min-height: 28px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #5568d3, stop:1 #6b3fa0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4c51bf, stop:1 #5a32a3);"
        "}"
        "QPushButton:disabled {"
        "   background-color: #4a5568;"
        "   color: #a0aec0;"
        "}"
        "QLabel {"
        "   color: #ffffff;"
        "   font-weight: 500;"
        "}"
        "QSpinBox, QDoubleSpinBox, QComboBox {"
        "   background-color: #4a5568;"
        "   color: #ffffff;"
        "   border: 2px solid #667eea;"
        "   border-radius: 4px;"
        "   padding: 4px 8px;"
        "   font-weight: 500;"
        "}"
        "QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {"
        "   border-color: #764ba2;"
        "}"
        "QSlider::groove:horizontal {"
        "   border: 1px solid #4a5568;"
        "   height: 8px;"
        "   background: #2d3748;"
        "   border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "   border: 1px solid #4a5568;"
        "   width: 18px;"
        "   margin: -5px 0;"
        "   border-radius: 9px;"
        "}"
        "QProgressBar {"
        "   border: 2px solid #4a5568;"
        "   border-radius: 4px;"
        "   background-color: #2d3748;"
        "   text-align: center;"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        "QProgressBar::chunk {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "   border-radius: 2px;"
        "}"
        "QCheckBox {"
        "   color: #ffffff;"
        "   font-weight: 500;"
        "}"
        "QCheckBox::indicator {"
        "   width: 18px;"
        "   height: 18px;"
        "}"
        "QCheckBox::indicator:unchecked {"
        "   border: 2px solid #4a5568;"
        "   border-radius: 3px;"
        "   background-color: #2d3748;"
        "}"
        "QCheckBox::indicator:checked {"
        "   border: 2px solid #667eea;"
        "   border-radius: 3px;"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "}"
        "QTextEdit {"
        "   border: 2px solid #4a5568;"
        "   border-radius: 4px;"
        "   background-color: #1a202c;"
        "   color: #ffffff;"
        "   selection-background-color: #667eea;"
        "}"
    );
}

// Servo Controller Slots
void CInterfacesWidget::onServoAzimuthChanged(double value)
{
    if (m_servoStatus) {
        m_servoStatus->setText(QString("Status: Moving to Az: %1°").arg(value, 0, 'f', 1));
    }
    emit servoPositionChanged(value, m_servoElevation->value());
}

void CInterfacesWidget::onServoElevationChanged(double value)
{
    if (m_servoStatus) {
        m_servoStatus->setText(QString("Status: Moving to El: %1°").arg(value, 0, 'f', 1));
    }
    emit servoPositionChanged(m_servoAzimuth->value(), value);
}

void CInterfacesWidget::onServoSpeedChanged(int value)
{
    if (m_servoProgress) {
        m_servoProgress->setValue(value);
    }
}

void CInterfacesWidget::onServoHomeClicked()
{
    m_servoAzimuth->setValue(0.0);
    m_servoElevation->setValue(0.0);
    if (m_servoStatus) {
        m_servoStatus->setText("Status: Homing...");
    }
}

void CInterfacesWidget::onServoStopClicked()
{
    if (m_servoStatus) {
        m_servoStatus->setText("Status: Stopped");
    }
}

void CInterfacesWidget::onServoModeChanged(const QString &mode)
{
    if (m_servoStatus) {
        m_servoStatus->setText(QString("Status: Mode - %1").arg(mode));
    }
    emit servoModeChanged(mode);
}

// Radar Controller Slots
void CInterfacesWidget::onRadarPowerToggled(bool enabled)
{
    if (m_radarStatus) {
        m_radarStatus->setText(enabled ? "Status: Online" : "Status: Offline");
    }
    if (m_radarSignalStrength) {
        m_radarSignalStrength->setValue(enabled ? 85 : 0);
    }
    
    emit radarConfigChanged(enabled, m_radarMode->currentText(), 
                           m_radarRange->value(), m_radarScanRate->value(), 
                           m_radarGain->value());
}

void CInterfacesWidget::onRadarModeChanged(const QString &mode)
{
    if (m_radarStatus && m_radarPower->isChecked()) {
        m_radarStatus->setText(QString("Status: %1 Mode").arg(mode));
    }
    
    emit radarConfigChanged(m_radarPower->isChecked(), mode, 
                           m_radarRange->value(), m_radarScanRate->value(), 
                           m_radarGain->value());
}

void CInterfacesWidget::onRadarRangeChanged(int range)
{
    emit radarConfigChanged(m_radarPower->isChecked(), m_radarMode->currentText(), 
                           range, m_radarScanRate->value(), 
                           m_radarGain->value());
}

void CInterfacesWidget::onRadarScanRateChanged(int rate)
{
    emit radarConfigChanged(m_radarPower->isChecked(), m_radarMode->currentText(), 
                           m_radarRange->value(), rate, 
                           m_radarGain->value());
}

void CInterfacesWidget::onRadarGainChanged(int gain)
{
    emit radarConfigChanged(m_radarPower->isChecked(), m_radarMode->currentText(), 
                           m_radarRange->value(), m_radarScanRate->value(), 
                           gain);
}

// Gun Controller Slots
void CInterfacesWidget::onGunPowerToggled(bool enabled)
{
    if (m_gunStatus) {
        m_gunStatus->setText(enabled ? "Status: Armed" : "Status: Safe");
    }
    
    // Update fire button state based on power and safety
    if (m_gunFire) {
        m_gunFire->setEnabled(enabled && !m_gunSafety->isChecked());
    }
    
    emit gunConfigChanged(enabled, m_gunMode->currentText(), 
                         m_gunElevation->value(), m_gunAzimuth->value());
}

void CInterfacesWidget::onGunModeChanged(const QString &mode)
{
    if (m_gunStatus && m_gunPower->isChecked()) {
        m_gunStatus->setText(QString("Status: %1 Mode").arg(mode));
    }
    
    emit gunConfigChanged(m_gunPower->isChecked(), mode, 
                         m_gunElevation->value(), m_gunAzimuth->value());
}

void CInterfacesWidget::onGunElevationChanged(double elevation)
{
    emit gunConfigChanged(m_gunPower->isChecked(), m_gunMode->currentText(), 
                         elevation, m_gunAzimuth->value());
}

void CInterfacesWidget::onGunAzimuthChanged(double azimuth)
{
    emit gunConfigChanged(m_gunPower->isChecked(), m_gunMode->currentText(), 
                         m_gunElevation->value(), azimuth);
}

void CInterfacesWidget::onGunFireClicked()
{
    if (m_gunAmmo) {
        int currentAmmo = m_gunAmmo->value();
        if (currentAmmo > 0) {
            m_gunAmmo->setValue(currentAmmo - 1);
        }
    }
    
    if (m_gunStatus) {
        m_gunStatus->setText("Status: FIRING!");
        QTimer::singleShot(1000, [this]() {
            if (m_gunStatus) {
                m_gunStatus->setText("Status: Ready");
            }
        });
    }
    
    emit gunFired();
}

void CInterfacesWidget::onGunSafetyToggled(bool enabled)
{
    if (m_gunFire) {
        m_gunFire->setEnabled(m_gunPower->isChecked() && !enabled);
    }
    
    if (m_gunStatus) {
        m_gunStatus->setText(enabled ? "Status: Safety ON" : "Status: Safety OFF");
    }
}

// Missile Controller Slots
void CInterfacesWidget::onMissilePowerToggled(bool enabled)
{
    if (m_missileStatus) {
        m_missileStatus->setText(enabled ? "Status: System Online" : "Status: Offline");
    }
    
    if (m_missileReadiness) {
        m_missileReadiness->setValue(enabled ? 95 : 0);
    }
    
    // Enable/disable launch controls
    if (m_missileLaunch) {
        m_missileLaunch->setEnabled(enabled && m_missileTargetLock->isChecked());
    }
    
    emit missileConfigChanged(enabled, m_missileType->currentText());
}

void CInterfacesWidget::onMissileTypeChanged(const QString &type)
{
    if (m_missileStatus && m_missilePower->isChecked()) {
        m_missileStatus->setText(QString("Status: %1 Ready").arg(type));
    }
    
    emit missileConfigChanged(m_missilePower->isChecked(), type);
}

void CInterfacesWidget::onMissileLaunchClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Missile Launch Confirmation", 
        "Are you sure you want to launch the missile?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (m_missileStatus) {
            m_missileStatus->setText("Status: MISSILE LAUNCHED!");
        }
        
        // Disable launch button temporarily
        if (m_missileLaunch) {
            m_missileLaunch->setEnabled(false);
        }
        
        // Re-enable after 5 seconds
        QTimer::singleShot(5000, [this]() {
            if (m_missileLaunch && m_missilePower->isChecked() && m_missileTargetLock->isChecked()) {
                m_missileLaunch->setEnabled(true);
            }
            if (m_missileStatus) {
                m_missileStatus->setText("Status: Ready");
            }
        });
        
        emit missileLaunched();
    }
}

void CInterfacesWidget::onMissileAbortClicked()
{
    if (m_missileStatus) {
        m_missileStatus->setText("Status: Launch Aborted");
    }
    
    emit missileAborted();
}

void CInterfacesWidget::onMissileTargetLockToggled(bool locked)
{
    if (m_missileLaunch) {
        m_missileLaunch->setEnabled(m_missilePower->isChecked() && locked);
    }
    
    if (m_missileAbort) {
        m_missileAbort->setEnabled(locked);
    }
    
    if (m_missileStatus) {
        m_missileStatus->setText(locked ? "Status: Target Locked" : "Status: No Target Lock");
    }
}

// EOTS Controller Slots
void CInterfacesWidget::onEotsPowerToggled(bool enabled)
{
    if (m_eotsStatus) {
        m_eotsStatus->setText(enabled ? "Status: EOTS Online" : "Status: Offline");
    }
    
    emit eotsConfigChanged(enabled, m_eotsMode->currentText(), 
                          m_eotsZoom->value(), m_eotsTracking->isChecked());
}

void CInterfacesWidget::onEotsModeChanged(const QString &mode)
{
    if (m_eotsStatus && m_eotsPower->isChecked()) {
        m_eotsStatus->setText(QString("Status: %1 Mode").arg(mode));
    }
    
    emit eotsConfigChanged(m_eotsPower->isChecked(), mode, 
                          m_eotsZoom->value(), m_eotsTracking->isChecked());
}

void CInterfacesWidget::onEotsZoomChanged(int zoom)
{
    emit eotsConfigChanged(m_eotsPower->isChecked(), m_eotsMode->currentText(), 
                          zoom, m_eotsTracking->isChecked());
}

void CInterfacesWidget::onEotsTrackingToggled(bool enabled)
{
    if (m_eotsStatus && m_eotsPower->isChecked()) {
        m_eotsStatus->setText(enabled ? "Status: Auto Tracking" : "Status: Manual Mode");
    }
    
    emit eotsConfigChanged(m_eotsPower->isChecked(), m_eotsMode->currentText(), 
                          m_eotsZoom->value(), enabled);
}

void CInterfacesWidget::onEotsCalibrateClicked()
{
    if (m_eotsStatus) {
        m_eotsStatus->setText("Status: Calibrating...");
        
        QTimer::singleShot(3000, [this]() {
            if (m_eotsStatus) {
                m_eotsStatus->setText("Status: Calibration Complete");
            }
        });
    }
}

// Logging Slots
void CInterfacesWidget::onLoggingToggled(bool enabled)
{
    if (enabled) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
        m_currentLogFile = QString("radar_log_%1.txt").arg(timestamp);
        
        if (m_logDisplay) {
            m_logDisplay->append(QString("[%1] Logging started - File: %2")
                               .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                               .arg(m_currentLogFile));
        }
    } else {
        if (m_logDisplay) {
            m_logDisplay->append(QString("[%1] Logging stopped")
                               .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
        }
    }
    
    emit loggingStateChanged(enabled, m_logLevel->currentText());
}

void CInterfacesWidget::onLogLevelChanged(const QString &level)
{
    if (m_loggingEnabled->isChecked()) {
        if (m_logDisplay) {
            m_logDisplay->append(QString("[%1] Log level changed to: %2")
                               .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                               .arg(level));
        }
    }
    
    emit loggingStateChanged(m_loggingEnabled->isChecked(), level);
}

void CInterfacesWidget::onLogSaveClicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save Log File", 
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + m_currentLogFile,
        "Text Files (*.txt)");
    
    if (!fileName.isEmpty() && m_logDisplay) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << m_logDisplay->toPlainText();
            file.close();
            
            m_logDisplay->append(QString("[%1] Log saved to: %2")
                               .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                               .arg(fileName));
        }
    }
}

void CInterfacesWidget::onLogClearClicked()
{
    if (m_logDisplay) {
        m_logDisplay->clear();
        m_logDisplay->append(QString("[%1] Log cleared")
                           .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
    }
}

void CInterfacesWidget::updateLogDisplay()
{
    // This method is called by timer to update log display
    // Add any periodic log updates here
}

// Screen Recording Slots
void CInterfacesWidget::onRecordingToggled(bool enabled)
{
    m_isRecording = enabled;
    
    if (enabled) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
        m_currentRecordingFile = QString("radar_recording_%1.mp4").arg(timestamp);
        
        if (m_recordingStatus) {
            m_recordingStatus->setText(QString("Recording: %1 (%2)")
                                     .arg(m_currentRecordingFile)
                                     .arg(m_recordingQuality->currentText()));
        }
        
        if (m_recordingSave) m_recordingSave->setEnabled(false);
        if (m_recordingStop) m_recordingStop->setEnabled(true);
    } else {
        if (m_recordingStatus) {
            m_recordingStatus->setText("Recording stopped");
        }
        
        if (m_recordingSave) m_recordingSave->setEnabled(true);
        if (m_recordingStop) m_recordingStop->setEnabled(false);
    }
    
    emit recordingStateChanged(enabled, m_recordingQuality->currentText());
}

void CInterfacesWidget::onRecordingQualityChanged(const QString &quality)
{
    if (m_isRecording && m_recordingStatus) {
        m_recordingStatus->setText(QString("Recording: %1 (%2)")
                                 .arg(m_currentRecordingFile)
                                 .arg(quality));
    }
    
    emit recordingStateChanged(m_recordingEnabled->isChecked(), quality);
}

void CInterfacesWidget::onRecordingSaveClicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save Recording", 
        QStandardPaths::writableLocation(QStandardPaths::MoviesLocation) + "/" + m_currentRecordingFile,
        "Video Files (*.mp4 *.avi)");
    
    if (!fileName.isEmpty() && m_recordingStatus) {
        m_recordingStatus->setText(QString("Recording saved to: %1").arg(fileName));
    }
}

void CInterfacesWidget::onRecordingStopClicked()
{
    if (m_recordingEnabled) {
        m_recordingEnabled->setChecked(false);
    }
}

// Replay System Slots
void CInterfacesWidget::onReplayLoadClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, "Load Session File",
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        "Session Files (*.session *.log)");
    
    if (!fileName.isEmpty()) {
        m_currentReplayFile = fileName;
        
        // Enable replay controls
        if (m_replayPlay) m_replayPlay->setEnabled(true);
        if (m_replaySpeed) m_replaySpeed->setEnabled(true);
        if (m_replayPosition) m_replayPosition->setEnabled(true);
        
        if (m_replayStatus) {
            m_replayStatus->setText(QString("Loaded: %1").arg(QFileInfo(fileName).baseName()));
        }
    }
}

void CInterfacesWidget::onReplayPlayClicked()
{
    m_isReplaying = true;
    
    if (m_replayPlay) m_replayPlay->setEnabled(false);
    if (m_replayPause) m_replayPause->setEnabled(true);
    if (m_replayStop) m_replayStop->setEnabled(true);
    
    if (m_replayStatus) {
        m_replayStatus->setText("Playing session...");
    }
    
    emit replayStateChanged("play", m_replaySpeed->value());
}

void CInterfacesWidget::onReplayPauseClicked()
{
    if (m_replayPlay) m_replayPlay->setEnabled(true);
    if (m_replayPause) m_replayPause->setEnabled(false);
    
    if (m_replayStatus) {
        m_replayStatus->setText("Paused");
    }
    
    emit replayStateChanged("pause", m_replaySpeed->value());
}

void CInterfacesWidget::onReplayStopClicked()
{
    m_isReplaying = false;
    
    if (m_replayPlay) m_replayPlay->setEnabled(true);
    if (m_replayPause) m_replayPause->setEnabled(false);
    if (m_replayStop) m_replayStop->setEnabled(false);
    if (m_replayPosition) m_replayPosition->setValue(0);
    
    if (m_replayStatus) {
        m_replayStatus->setText("Stopped");
    }
    
    emit replayStateChanged("stop", m_replaySpeed->value());
}

void CInterfacesWidget::onReplaySpeedChanged(double speed)
{
    if (m_isReplaying) {
        emit replayStateChanged("speed", speed);
    }
}

void CInterfacesWidget::onReplayPositionChanged(int position)
{
    if (m_isReplaying) {
        emit replayStateChanged("seek", position);
    }
}
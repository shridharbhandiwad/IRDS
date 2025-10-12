#include "csimulationwidget.h"
#include <QApplication>
#include <QDateTime>
#include <QNetworkDatagram>
#include <QDebug>
#include <QtMath>

CSimulationWidget::CSimulationWidget(QWidget *parent)
    : QDockWidget("Simulation Control", parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_simulationTimer(new QTimer(this))
    , m_udpSocket(new QUdpSocket(this))
    , m_isRunning(false)
    , m_isPaused(false)
    , m_simulationTime(0)
    , m_nextTrackId(1000)
    , m_maxRange(5000.0)
    , m_updateRate(1000)
{
    setupUI();
    applyModernTheme();
    
    // Initialize scenarios
    m_scenarios = {
        {"Air Defense", 8, 8000.0, true, "Multiple aircraft approaching from different vectors"},
        {"Naval Patrol", 4, 6000.0, false, "Ships on patrol routes"},
        {"Mixed Traffic", 12, 10000.0, true, "Combined air and surface contacts"},
        {"Training Exercise", 6, 4000.0, true, "Controlled training scenario"},
        {"High Density", 20, 7000.0, true, "High traffic density scenario"}
    };
    
    // Populate scenario combo
    for (const auto& scenario : m_scenarios) {
        m_scenarioCombo->addItem(scenario.name);
    }
    
    // Connect timer
    connect(m_simulationTimer, &QTimer::timeout, this, &CSimulationWidget::onSimulationTick);
    
    // Set initial values
    m_trackCountSpin->setValue(8);
    m_rangeSpin->setValue(5000.0);
    m_updateRateSlider->setValue(1000);
    
    updateSimulationStatus();
}

CSimulationWidget::~CSimulationWidget()
{
    if (m_isRunning) {
        onStopSimulation();
    }
}

void CSimulationWidget::setupUI()
{
    m_centralWidget = new QWidget();
    setWidget(m_centralWidget);
    
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(10);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // Control Group
    m_controlGroup = new QGroupBox("Simulation Control");
    QHBoxLayout *controlLayout = new QHBoxLayout(m_controlGroup);
    
    m_startButton = new QPushButton("▶ Start");
    m_stopButton = new QPushButton("⏹ Stop");
    m_pauseButton = new QPushButton("⏸ Pause");
    m_resetButton = new QPushButton("🔄 Reset");
    
    m_startButton->setMinimumHeight(35);
    m_stopButton->setMinimumHeight(35);
    m_pauseButton->setMinimumHeight(35);
    m_resetButton->setMinimumHeight(35);
    
    controlLayout->addWidget(m_startButton);
    controlLayout->addWidget(m_pauseButton);
    controlLayout->addWidget(m_stopButton);
    controlLayout->addWidget(m_resetButton);
    
    // Track Generation Group
    m_trackGenGroup = new QGroupBox("Track Generation");
    QGridLayout *trackGenLayout = new QGridLayout(m_trackGenGroup);
    
    trackGenLayout->addWidget(new QLabel("Track Count:"), 0, 0);
    m_trackCountSpin = new QSpinBox();
    m_trackCountSpin->setRange(1, 50);
    m_trackCountSpin->setValue(8);
    trackGenLayout->addWidget(m_trackCountSpin, 0, 1);
    
    trackGenLayout->addWidget(new QLabel("Max Range (m):"), 1, 0);
    m_rangeSpin = new QDoubleSpinBox();
    m_rangeSpin->setRange(1000.0, MAX_SIMULATION_RANGE);
    m_rangeSpin->setValue(5000.0);
    m_rangeSpin->setSuffix(" m");
    trackGenLayout->addWidget(m_rangeSpin, 1, 1);
    
    m_generateButton = new QPushButton("🎯 Generate Tracks");
    m_clearButton = new QPushButton("🗑 Clear All");
    trackGenLayout->addWidget(m_generateButton, 2, 0);
    trackGenLayout->addWidget(m_clearButton, 2, 1);
    
    // Simulation Parameters Group
    m_paramGroup = new QGroupBox("Parameters");
    QGridLayout *paramLayout = new QGridLayout(m_paramGroup);
    
    paramLayout->addWidget(new QLabel("Update Rate:"), 0, 0);
    m_updateRateSlider = new QSlider(Qt::Horizontal);
    m_updateRateSlider->setRange(MIN_UPDATE_RATE, MAX_UPDATE_RATE);
    m_updateRateSlider->setValue(1000);
    m_updateRateLabel = new QLabel("1000 ms");
    paramLayout->addWidget(m_updateRateSlider, 0, 1);
    paramLayout->addWidget(m_updateRateLabel, 0, 2);
    
    paramLayout->addWidget(new QLabel("Scenario:"), 1, 0);
    m_scenarioCombo = new QComboBox();
    paramLayout->addWidget(m_scenarioCombo, 1, 1, 1, 2);
    
    m_randomMotionCheck = new QCheckBox("Random Motion");
    m_randomMotionCheck->setChecked(true);
    paramLayout->addWidget(m_randomMotionCheck, 2, 0, 1, 2);
    
    m_collisionAvoidanceCheck = new QCheckBox("Collision Avoidance");
    m_collisionAvoidanceCheck->setChecked(false);
    paramLayout->addWidget(m_collisionAvoidanceCheck, 3, 0, 1, 2);
    
    // Status Group
    m_statusGroup = new QGroupBox("Status");
    QGridLayout *statusLayout = new QGridLayout(m_statusGroup);
    
    m_activeTracksLabel = new QLabel("Active Tracks: 0");
    m_simulationTimeLabel = new QLabel("Simulation Time: 00:00:00");
    statusLayout->addWidget(m_activeTracksLabel, 0, 0);
    statusLayout->addWidget(m_simulationTimeLabel, 0, 1);
    
    statusLayout->addWidget(new QLabel("CPU Usage:"), 1, 0);
    m_cpuUsageBar = new QProgressBar();
    m_cpuUsageBar->setRange(0, 100);
    m_cpuUsageBar->setValue(15);
    statusLayout->addWidget(m_cpuUsageBar, 1, 1);
    
    m_logText = new QTextEdit();
    m_logText->setMaximumHeight(100);
    m_logText->setReadOnly(true);
    statusLayout->addWidget(m_logText, 2, 0, 1, 2);
    
    // Add all groups to main layout
    m_mainLayout->addWidget(m_controlGroup);
    m_mainLayout->addWidget(m_trackGenGroup);
    m_mainLayout->addWidget(m_paramGroup);
    m_mainLayout->addWidget(m_statusGroup);
    m_mainLayout->addStretch();
    
    // Connect signals
    connect(m_startButton, &QPushButton::clicked, this, &CSimulationWidget::onStartSimulation);
    connect(m_stopButton, &QPushButton::clicked, this, &CSimulationWidget::onStopSimulation);
    connect(m_pauseButton, &QPushButton::clicked, this, &CSimulationWidget::onPauseSimulation);
    connect(m_resetButton, &QPushButton::clicked, this, &CSimulationWidget::onResetSimulation);
    connect(m_generateButton, &QPushButton::clicked, this, &CSimulationWidget::onGenerateTrack);
    connect(m_clearButton, &QPushButton::clicked, this, &CSimulationWidget::onClearAllTracks);
    
    connect(m_trackCountSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &CSimulationWidget::onTrackCountChanged);
    connect(m_rangeSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CSimulationWidget::onRangeChanged);
    connect(m_updateRateSlider, &QSlider::valueChanged, this, &CSimulationWidget::onUpdateRateChanged);
    connect(m_scenarioCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CSimulationWidget::onScenarioChanged);
}

void CSimulationWidget::applyModernTheme()
{
    setStyleSheet(R"(
        QDockWidget {
            background-color: #1e1e2e;
            color: #cdd6f4;
            border: 1px solid #45475a;
        }
        
        QDockWidget::title {
            background-color: #313244;
            color: #f38ba8;
            padding: 8px;
            font-weight: bold;
            font-size: 12px;
        }
        
        QGroupBox {
            font-weight: bold;
            border: 2px solid #45475a;
            border-radius: 8px;
            margin-top: 10px;
            padding-top: 10px;
            background-color: #181825;
        }
        
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 8px 0 8px;
            color: #89b4fa;
            font-size: 11px;
        }
        
        QPushButton {
            background-color: #45475a;
            border: 1px solid #6c7086;
            border-radius: 6px;
            color: #cdd6f4;
            font-weight: bold;
            padding: 8px 16px;
            min-width: 80px;
        }
        
        QPushButton:hover {
            background-color: #585b70;
            border-color: #89b4fa;
        }
        
        QPushButton:pressed {
            background-color: #313244;
        }
        
        QPushButton:disabled {
            background-color: #313244;
            color: #6c7086;
            border-color: #45475a;
        }
        
        QSpinBox, QDoubleSpinBox, QComboBox {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 4px;
            padding: 4px 8px;
            color: #cdd6f4;
            min-height: 20px;
        }
        
        QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {
            border-color: #89b4fa;
        }
        
        QSlider::groove:horizontal {
            border: 1px solid #45475a;
            height: 6px;
            background-color: #313244;
            border-radius: 3px;
        }
        
        QSlider::handle:horizontal {
            background-color: #89b4fa;
            border: 1px solid #6c7086;
            width: 16px;
            margin: -6px 0;
            border-radius: 8px;
        }
        
        QSlider::handle:horizontal:hover {
            background-color: #74c7ec;
        }
        
        QCheckBox {
            color: #cdd6f4;
            spacing: 8px;
        }
        
        QCheckBox::indicator {
            width: 16px;
            height: 16px;
            border: 1px solid #45475a;
            border-radius: 3px;
            background-color: #313244;
        }
        
        QCheckBox::indicator:checked {
            background-color: #a6e3a1;
            border-color: #40a02b;
        }
        
        QProgressBar {
            border: 1px solid #45475a;
            border-radius: 4px;
            text-align: center;
            background-color: #313244;
            color: #cdd6f4;
        }
        
        QProgressBar::chunk {
            background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #a6e3a1, stop:0.5 #40a02b, stop:1 #a6e3a1);
            border-radius: 3px;
        }
        
        QTextEdit {
            background-color: #181825;
            border: 1px solid #45475a;
            border-radius: 4px;
            color: #cdd6f4;
            font-family: 'Consolas', 'Monaco', monospace;
            font-size: 9px;
        }
        
        QLabel {
            color: #cdd6f4;
            font-size: 10px;
        }
    )");
}

void CSimulationWidget::onStartSimulation()
{
    if (m_isPaused) {
        m_isPaused = false;
        m_simulationTimer->start(m_updateRate);
        m_logText->append(QString("[%1] Simulation resumed").arg(QTime::currentTime().toString()));
    } else {
        m_isRunning = true;
        m_isPaused = false;
        m_simulationTimer->start(m_updateRate);
        m_logText->append(QString("[%1] Simulation started with %2 tracks").arg(QTime::currentTime().toString()).arg(m_activeTracks.size()));
    }
    
    m_startButton->setEnabled(false);
    m_pauseButton->setEnabled(true);
    m_stopButton->setEnabled(true);
    updateSimulationStatus();
}

void CSimulationWidget::onStopSimulation()
{
    m_isRunning = false;
    m_isPaused = false;
    m_simulationTimer->stop();
    m_logText->append(QString("[%1] Simulation stopped").arg(QTime::currentTime().toString()));
    
    m_startButton->setEnabled(true);
    m_pauseButton->setEnabled(false);
    m_stopButton->setEnabled(false);
    updateSimulationStatus();
}

void CSimulationWidget::onPauseSimulation()
{
    if (m_isRunning && !m_isPaused) {
        m_isPaused = true;
        m_simulationTimer->stop();
        m_logText->append(QString("[%1] Simulation paused").arg(QTime::currentTime().toString()));
        
        m_startButton->setEnabled(true);
        m_pauseButton->setEnabled(false);
    }
    updateSimulationStatus();
}

void CSimulationWidget::onResetSimulation()
{
    onStopSimulation();
    m_activeTracks.clear();
    m_trackVelocities.clear();
    m_simulationTime = 0;
    m_nextTrackId = 1000;
    m_logText->clear();
    m_logText->append(QString("[%1] Simulation reset").arg(QTime::currentTime().toString()));
    updateSimulationStatus();
}

void CSimulationWidget::onGenerateTrack()
{
    int trackCount = m_trackCountSpin->value();
    m_maxRange = m_rangeSpin->value();
    
    // Clear existing tracks
    m_activeTracks.clear();
    m_trackVelocities.clear();
    
    // Generate new tracks
    for (int i = 0; i < trackCount; ++i) {
        generateRandomTrack();
    }
    
    m_logText->append(QString("[%1] Generated %2 tracks within %3m range").arg(QTime::currentTime().toString()).arg(trackCount).arg(m_maxRange));
    updateSimulationStatus();
}

void CSimulationWidget::onClearAllTracks()
{
    m_activeTracks.clear();
    m_trackVelocities.clear();
    m_logText->append(QString("[%1] All tracks cleared").arg(QTime::currentTime().toString()));
    updateSimulationStatus();
}

void CSimulationWidget::onSimulationTick()
{
    if (!m_isRunning || m_isPaused) return;
    
    m_simulationTime += m_updateRate;
    
    // Update all active tracks
    for (auto it = m_activeTracks.begin(); it != m_activeTracks.end(); ++it) {
        updateTrackPosition(it.key());
        sendTrackData(it.value());
    }
    
    // Simulate CPU usage (random between 10-30%)
    int cpuUsage = 10 + QRandomGenerator::global()->bounded(20);
    m_cpuUsageBar->setValue(cpuUsage);
    
    updateSimulationStatus();
}

void CSimulationWidget::onTrackCountChanged(int count)
{
    Q_UNUSED(count)
    // Update UI or validation if needed
}

void CSimulationWidget::onRangeChanged(double range)
{
    m_maxRange = range;
}

void CSimulationWidget::onUpdateRateChanged(int rate)
{
    m_updateRate = rate;
    m_updateRateLabel->setText(QString("%1 ms").arg(rate));
    
    if (m_isRunning && !m_isPaused) {
        m_simulationTimer->setInterval(rate);
    }
}

void CSimulationWidget::onScenarioChanged(int index)
{
    if (index >= 0 && index < m_scenarios.size()) {
        loadScenario(index);
    }
}

void CSimulationWidget::generateRandomTrack()
{
    stTrackRecvInfo track;
    track.usMsgId = 0x1001;
    track.nTrkId = m_nextTrackId++;
    
    // Generate random position within range and different azimuth angles
    double azimuth = QRandomGenerator::global()->generateDouble() * 2.0 * M_PI;
    double range = QRandomGenerator::global()->generateDouble() * m_maxRange;
    
    track.x = static_cast<float>(range * cos(azimuth));
    track.y = static_cast<float>(range * sin(azimuth));
    track.z = static_cast<float>(QRandomGenerator::global()->bounded(100, 10000)); // Altitude 100-10000m
    
    track.heading = static_cast<float>(QRandomGenerator::global()->generateDouble() * 360.0);
    track.velocity = static_cast<float>(QRandomGenerator::global()->bounded(50, 500)); // 50-500 m/s
    
    // Random identity
    int identityRand = QRandomGenerator::global()->bounded(4);
    switch (identityRand) {
        case 0: track.nTrackIden = TRACK_IDENTITY_UNKNOWN; break;
        case 1: track.nTrackIden = TRACK_IDENTITY_FRIEND; break;
        case 2: track.nTrackIden = TRACK_IDENTITY_HOSTILE; break;
        default: track.nTrackIden = TRACK_IDENTITY_DEFAULT; break;
    }
    
    m_activeTracks[track.nTrkId] = track;
    
    // Generate random velocity vector for movement
    double velAzimuth = QRandomGenerator::global()->generateDouble() * 2.0 * M_PI;
    double velMagnitude = track.velocity * 0.1; // Scale down for reasonable movement
    m_trackVelocities[track.nTrkId] = QPointF(velMagnitude * cos(velAzimuth), velMagnitude * sin(velAzimuth));
}

void CSimulationWidget::updateTrackPosition(int trackId)
{
    if (!m_activeTracks.contains(trackId) || !m_trackVelocities.contains(trackId)) {
        return;
    }
    
    stTrackRecvInfo &track = m_activeTracks[trackId];
    QPointF &velocity = m_trackVelocities[trackId];
    
    // Update position based on velocity and time
    double deltaTime = m_updateRate / 1000.0; // Convert to seconds
    track.x += static_cast<float>(velocity.x() * deltaTime);
    track.y += static_cast<float>(velocity.y() * deltaTime);
    
    // Add some random motion if enabled
    if (m_randomMotionCheck->isChecked()) {
        double randomX = (QRandomGenerator::global()->generateDouble() - 0.5) * 10.0;
        double randomY = (QRandomGenerator::global()->generateDouble() - 0.5) * 10.0;
        track.x += static_cast<float>(randomX);
        track.y += static_cast<float>(randomY);
    }
    
    // Check bounds and wrap around or remove track if too far
    double currentRange = sqrt(track.x * track.x + track.y * track.y);
    if (currentRange > m_maxRange * 1.5) {
        // Respawn track at edge with inward velocity
        double newAzimuth = QRandomGenerator::global()->generateDouble() * 2.0 * M_PI;
        track.x = static_cast<float>(m_maxRange * cos(newAzimuth));
        track.y = static_cast<float>(m_maxRange * sin(newAzimuth));
        
        // Set velocity toward center with some randomness
        double centerAzimuth = atan2(-track.y, -track.x) + (QRandomGenerator::global()->generateDouble() - 0.5) * 0.5;
        double velMagnitude = track.velocity * 0.1;
        velocity = QPointF(velMagnitude * cos(centerAzimuth), velMagnitude * sin(centerAzimuth));
    }
    
    // Update heading based on velocity
    track.heading = static_cast<float>(atan2(velocity.y(), velocity.x()) * 180.0 / M_PI);
    if (track.heading < 0) track.heading += 360.0f;
}

void CSimulationWidget::sendTrackData(const stTrackRecvInfo& track)
{
    QByteArray data(reinterpret_cast<const char*>(&track), sizeof(stTrackRecvInfo));
    m_udpSocket->writeDatagram(data, QHostAddress::LocalHost, UDP_PORT);
}

void CSimulationWidget::updateSimulationStatus()
{
    m_activeTracksLabel->setText(QString("Active Tracks: %1").arg(m_activeTracks.size()));
    
    int hours = m_simulationTime / 3600000;
    int minutes = (m_simulationTime % 3600000) / 60000;
    int seconds = (m_simulationTime % 60000) / 1000;
    m_simulationTimeLabel->setText(QString("Simulation Time: %1:%2:%3")
                                   .arg(hours, 2, 10, QChar('0'))
                                   .arg(minutes, 2, 10, QChar('0'))
                                   .arg(seconds, 2, 10, QChar('0')));
}

void CSimulationWidget::loadScenario(int scenarioIndex)
{
    if (scenarioIndex < 0 || scenarioIndex >= m_scenarios.size()) return;
    
    const SimulationScenario &scenario = m_scenarios[scenarioIndex];
    
    m_trackCountSpin->setValue(scenario.defaultTrackCount);
    m_rangeSpin->setValue(scenario.defaultRange);
    m_randomMotionCheck->setChecked(scenario.hasRandomMotion);
    
    m_logText->append(QString("[%1] Loaded scenario: %2 - %3")
                      .arg(QTime::currentTime().toString())
                      .arg(scenario.name)
                      .arg(scenario.description));
}
#include "cscreenrecorderwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStorageInfo>
#include <QDebug>

CScreenRecorderWidget::CScreenRecorderWidget(QWidget *parent)
    : QDockWidget("Screen Recorder", parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_recordingTimer(new QTimer(this))
    , m_captureTimer(new QTimer(this))
    , m_isRecording(false)
    , m_isPaused(false)
    , m_recordingTime(0)
    , m_frameRate(DEFAULT_FRAME_RATE)
    , m_quality(75)
{
    setupUI();
    applyModernTheme();
    
    // Setup recordings directory
    m_recordingsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/RadarDisplay/Recordings";
    QDir().mkpath(m_recordingsPath);
    
    // Connect timers
    connect(m_recordingTimer, &QTimer::timeout, this, &CScreenRecorderWidget::onRecordingTimer);
    connect(m_captureTimer, &QTimer::timeout, this, &CScreenRecorderWidget::captureFrame);
    
    // Set initial values
    m_frameRateSlider->setValue(DEFAULT_FRAME_RATE);
    m_qualityCombo->setCurrentIndex(2); // Medium quality
    
    updateRecordingsList();
    updateRecordingStatus();
}

CScreenRecorderWidget::~CScreenRecorderWidget()
{
    if (m_isRecording) {
        onStopRecording();
    }
}

void CScreenRecorderWidget::setupUI()
{
    m_centralWidget = new QWidget();
    setWidget(m_centralWidget);
    
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(10);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // Recording Control Group
    m_recordGroup = new QGroupBox("Recording Control");
    QHBoxLayout *recordLayout = new QHBoxLayout(m_recordGroup);
    
    m_startRecordButton = new QPushButton("🔴 Record");
    m_pauseRecordButton = new QPushButton("⏸ Pause");
    m_stopRecordButton = new QPushButton("⏹ Stop");
    m_screenshotButton = new QPushButton("📷 Screenshot");
    
    m_startRecordButton->setMinimumHeight(35);
    m_pauseRecordButton->setMinimumHeight(35);
    m_stopRecordButton->setMinimumHeight(35);
    m_screenshotButton->setMinimumHeight(35);
    
    recordLayout->addWidget(m_startRecordButton);
    recordLayout->addWidget(m_pauseRecordButton);
    recordLayout->addWidget(m_stopRecordButton);
    recordLayout->addWidget(m_screenshotButton);
    
    // Recording Settings Group
    m_settingsGroup = new QGroupBox("Recording Settings");
    QGridLayout *settingsLayout = new QGridLayout(m_settingsGroup);
    
    settingsLayout->addWidget(new QLabel("Quality:"), 0, 0);
    m_qualityCombo = new QComboBox();
    m_qualityCombo->addItems({"Low (50%)", "Medium (75%)", "High (90%)", "Ultra (100%)"});
    settingsLayout->addWidget(m_qualityCombo, 0, 1);
    
    settingsLayout->addWidget(new QLabel("Frame Rate:"), 1, 0);
    m_frameRateSlider = new QSlider(Qt::Horizontal);
    m_frameRateSlider->setRange(MIN_FRAME_RATE, MAX_FRAME_RATE);
    m_frameRateSlider->setValue(DEFAULT_FRAME_RATE);
    m_frameRateLabel = new QLabel("10 FPS");
    settingsLayout->addWidget(m_frameRateSlider, 1, 1);
    settingsLayout->addWidget(m_frameRateLabel, 1, 2);
    
    m_audioRecordCheck = new QCheckBox("Record Audio");
    m_audioRecordCheck->setChecked(false);
    m_audioRecordCheck->setEnabled(false); // Not implemented yet
    settingsLayout->addWidget(m_audioRecordCheck, 2, 0, 1, 2);
    
    m_cursorRecordCheck = new QCheckBox("Record Cursor");
    m_cursorRecordCheck->setChecked(true);
    settingsLayout->addWidget(m_cursorRecordCheck, 3, 0, 1, 2);
    
    // Recordings Management Group
    m_recordingsGroup = new QGroupBox("Recorded Sessions");
    QVBoxLayout *recordingsLayout = new QVBoxLayout(m_recordingsGroup);
    
    m_recordingsList = new QListWidget();
    m_recordingsList->setMaximumHeight(120);
    recordingsLayout->addWidget(m_recordingsList);
    
    QHBoxLayout *recordingButtonsLayout = new QHBoxLayout();
    m_playButton = new QPushButton("▶ Play");
    m_deleteButton = new QPushButton("🗑 Delete");
    m_openFolderButton = new QPushButton("📁 Open Folder");
    
    recordingButtonsLayout->addWidget(m_playButton);
    recordingButtonsLayout->addWidget(m_deleteButton);
    recordingButtonsLayout->addWidget(m_openFolderButton);
    recordingsLayout->addLayout(recordingButtonsLayout);
    
    // Status Group
    m_statusGroup = new QGroupBox("Status");
    QGridLayout *statusLayout = new QGridLayout(m_statusGroup);
    
    m_recordingStatusLabel = new QLabel("Status: Ready");
    m_recordingTimeLabel = new QLabel("Recording Time: 00:00:00");
    statusLayout->addWidget(m_recordingStatusLabel, 0, 0);
    statusLayout->addWidget(m_recordingTimeLabel, 0, 1);
    
    statusLayout->addWidget(new QLabel("Disk Space:"), 1, 0);
    m_diskSpaceBar = new QProgressBar();
    m_diskSpaceBar->setRange(0, 100);
    statusLayout->addWidget(m_diskSpaceBar, 1, 1);
    
    m_logText = new QTextEdit();
    m_logText->setMaximumHeight(80);
    m_logText->setReadOnly(true);
    statusLayout->addWidget(m_logText, 2, 0, 1, 2);
    
    // Add all groups to main layout
    m_mainLayout->addWidget(m_recordGroup);
    m_mainLayout->addWidget(m_settingsGroup);
    m_mainLayout->addWidget(m_recordingsGroup);
    m_mainLayout->addWidget(m_statusGroup);
    m_mainLayout->addStretch();
    
    // Connect signals
    connect(m_startRecordButton, &QPushButton::clicked, this, &CScreenRecorderWidget::onStartRecording);
    connect(m_stopRecordButton, &QPushButton::clicked, this, &CScreenRecorderWidget::onStopRecording);
    connect(m_pauseRecordButton, &QPushButton::clicked, this, &CScreenRecorderWidget::onPauseRecording);
    connect(m_screenshotButton, &QPushButton::clicked, this, &CScreenRecorderWidget::onTakeScreenshot);
    
    connect(m_playButton, &QPushButton::clicked, this, &CScreenRecorderWidget::onPlayRecording);
    connect(m_deleteButton, &QPushButton::clicked, this, &CScreenRecorderWidget::onDeleteRecording);
    connect(m_openFolderButton, &QPushButton::clicked, this, &CScreenRecorderWidget::onOpenRecordingsFolder);
    
    connect(m_qualityCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CScreenRecorderWidget::onQualityChanged);
    connect(m_frameRateSlider, &QSlider::valueChanged, this, &CScreenRecorderWidget::onFrameRateChanged);
    connect(m_recordingsList, &QListWidget::itemSelectionChanged, this, &CScreenRecorderWidget::onRecordingSelectionChanged);
    
    // Initial button states
    m_pauseRecordButton->setEnabled(false);
    m_stopRecordButton->setEnabled(false);
    m_playButton->setEnabled(false);
    m_deleteButton->setEnabled(false);
}

void CScreenRecorderWidget::applyModernTheme()
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
        
        QComboBox, QListWidget {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 4px;
            padding: 4px 8px;
            color: #cdd6f4;
        }
        
        QComboBox:focus, QListWidget:focus {
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

void CScreenRecorderWidget::onStartRecording()
{
    if (m_isPaused) {
        m_isPaused = false;
        m_captureTimer->start(1000 / m_frameRate);
        m_recordingTimer->start(1000);
        m_logText->append(QString("[%1] Recording resumed").arg(QTime::currentTime().toString()));
    } else {
        m_isRecording = true;
        m_isPaused = false;
        m_recordingTime = 0;
        m_recordedFrames.clear();
        
        // Generate filename
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        m_currentRecordingFile = QString("Recording_%1").arg(timestamp);
        
        m_captureTimer->start(1000 / m_frameRate);
        m_recordingTimer->start(1000);
        
        m_logText->append(QString("[%1] Recording started: %2").arg(QTime::currentTime().toString(), m_currentRecordingFile));
    }
    
    m_startRecordButton->setEnabled(false);
    m_pauseRecordButton->setEnabled(true);
    m_stopRecordButton->setEnabled(true);
    updateRecordingStatus();
}

void CScreenRecorderWidget::onStopRecording()
{
    m_isRecording = false;
    m_isPaused = false;
    m_captureTimer->stop();
    m_recordingTimer->stop();
    
    if (!m_recordedFrames.isEmpty()) {
        saveRecordingSession();
        updateRecordingsList();
    }
    
    m_logText->append(QString("[%1] Recording stopped. %2 frames captured").arg(QTime::currentTime().toString()).arg(m_recordedFrames.size()));
    
    m_startRecordButton->setEnabled(true);
    m_pauseRecordButton->setEnabled(false);
    m_stopRecordButton->setEnabled(false);
    updateRecordingStatus();
}

void CScreenRecorderWidget::onPauseRecording()
{
    if (m_isRecording && !m_isPaused) {
        m_isPaused = true;
        m_captureTimer->stop();
        m_recordingTimer->stop();
        m_logText->append(QString("[%1] Recording paused").arg(QTime::currentTime().toString()));
        
        m_startRecordButton->setEnabled(true);
        m_pauseRecordButton->setEnabled(false);
    }
    updateRecordingStatus();
}

void CScreenRecorderWidget::onTakeScreenshot()
{
    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        QPixmap screenshot = screen->grabWindow(0);
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        QString filename = QString("%1/Screenshot_%2.png").arg(m_recordingsPath, timestamp);
        
        if (screenshot.save(filename)) {
            m_logText->append(QString("[%1] Screenshot saved: %2").arg(QTime::currentTime().toString(), filename));
        } else {
            m_logText->append(QString("[%1] Failed to save screenshot").arg(QTime::currentTime().toString()));
        }
    }
}

void CScreenRecorderWidget::onOpenRecordingsFolder()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_recordingsPath));
}

void CScreenRecorderWidget::onPlayRecording()
{
    QListWidgetItem *item = m_recordingsList->currentItem();
    if (!item) return;
    
    QString filename = item->data(Qt::UserRole).toString();
    loadRecordingSession(filename);
}

void CScreenRecorderWidget::onDeleteRecording()
{
    QListWidgetItem *item = m_recordingsList->currentItem();
    if (!item) return;
    
    int ret = QMessageBox::question(this, "Delete Recording", 
                                   "Are you sure you want to delete this recording?",
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        QString filename = item->data(Qt::UserRole).toString();
        QString fullPath = QString("%1/%2").arg(m_recordingsPath, filename);
        
        if (QFile::remove(fullPath)) {
            m_logText->append(QString("[%1] Recording deleted: %2").arg(QTime::currentTime().toString(), filename));
            updateRecordingsList();
        } else {
            m_logText->append(QString("[%1] Failed to delete recording: %2").arg(QTime::currentTime().toString(), filename));
        }
    }
}

void CScreenRecorderWidget::onRecordingTimer()
{
    m_recordingTime++;
    updateRecordingStatus();
}

void CScreenRecorderWidget::onQualityChanged(int quality)
{
    switch (quality) {
        case 0: m_quality = 50; break;   // Low
        case 1: m_quality = 75; break;   // Medium
        case 2: m_quality = 90; break;   // High
        case 3: m_quality = 100; break;  // Ultra
        default: m_quality = 75; break;
    }
}

void CScreenRecorderWidget::onFrameRateChanged(int fps)
{
    m_frameRate = fps;
    m_frameRateLabel->setText(QString("%1 FPS").arg(fps));
    
    if (m_isRecording && !m_isPaused) {
        m_captureTimer->setInterval(1000 / m_frameRate);
    }
}

void CScreenRecorderWidget::onRecordingSelectionChanged()
{
    bool hasSelection = m_recordingsList->currentItem() != nullptr;
    m_playButton->setEnabled(hasSelection);
    m_deleteButton->setEnabled(hasSelection);
}

void CScreenRecorderWidget::updateRecordingsList()
{
    m_recordingsList->clear();
    
    QDir recordingsDir(m_recordingsPath);
    QStringList filters;
    filters << "*.json";
    QFileInfoList files = recordingsDir.entryInfoList(filters, QDir::Files, QDir::Time);
    
    for (const QFileInfo &fileInfo : files) {
        QFile file(fileInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            QJsonObject obj = doc.object();
            
            QString displayName = QString("%1 (%2s, %3 frames)")
                                  .arg(obj["name"].toString())
                                  .arg(obj["duration"].toInt())
                                  .arg(obj["frameCount"].toInt());
            
            QListWidgetItem *item = new QListWidgetItem(displayName);
            item->setData(Qt::UserRole, fileInfo.fileName());
            m_recordingsList->addItem(item);
        }
    }
}

void CScreenRecorderWidget::captureFrame()
{
    if (!m_isRecording || m_isPaused) return;
    
    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        QPixmap frame = screen->grabWindow(0);
        
        // Scale based on quality setting
        if (m_quality < 100) {
            QSize newSize = frame.size() * (m_quality / 100.0);
            frame = frame.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        
        m_recordedFrames.append(frame);
    }
}

void CScreenRecorderWidget::saveRecordingSession()
{
    if (m_recordedFrames.isEmpty()) return;
    
    // Save metadata
    QJsonObject sessionObj;
    sessionObj["name"] = m_currentRecordingFile;
    sessionObj["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    sessionObj["duration"] = m_recordingTime;
    sessionObj["frameCount"] = m_recordedFrames.size();
    sessionObj["frameRate"] = m_frameRate;
    sessionObj["quality"] = m_quality;
    
    QJsonDocument doc(sessionObj);
    QString metadataFile = QString("%1/%2.json").arg(m_recordingsPath, m_currentRecordingFile);
    
    QFile file(metadataFile);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
    
    // Save frames (simplified - in a real implementation, you'd save as video)
    QString framesDir = QString("%1/%2_frames").arg(m_recordingsPath, m_currentRecordingFile);
    QDir().mkpath(framesDir);
    
    for (int i = 0; i < m_recordedFrames.size(); ++i) {
        QString framePath = QString("%1/frame_%2.png").arg(framesDir).arg(i, 6, 10, QChar('0'));
        m_recordedFrames[i].save(framePath);
    }
}

void CScreenRecorderWidget::loadRecordingSession(const QString& filename)
{
    QString metadataFile = QString("%1/%2").arg(m_recordingsPath, filename);
    
    QFile file(metadataFile);
    if (!file.open(QIODevice::ReadOnly)) {
        m_logText->append(QString("[%1] Failed to load recording: %2").arg(QTime::currentTime().toString(), filename));
        return;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();
    
    m_logText->append(QString("[%1] Playing recording: %2 (%3s, %4 frames)")
                      .arg(QTime::currentTime().toString())
                      .arg(obj["name"].toString())
                      .arg(obj["duration"].toInt())
                      .arg(obj["frameCount"].toInt()));
    
    // In a real implementation, you would implement a replay viewer here
    QMessageBox::information(this, "Recording Playback", 
                           QString("Recording playback not fully implemented.\n\nRecording Details:\n"
                                  "Name: %1\nDuration: %2 seconds\nFrames: %3\nFrame Rate: %4 FPS")
                           .arg(obj["name"].toString())
                           .arg(obj["duration"].toInt())
                           .arg(obj["frameCount"].toInt())
                           .arg(obj["frameRate"].toInt()));
}

void CScreenRecorderWidget::updateRecordingStatus()
{
    if (m_isRecording) {
        if (m_isPaused) {
            m_recordingStatusLabel->setText("Status: Paused");
        } else {
            m_recordingStatusLabel->setText("Status: Recording");
        }
    } else {
        m_recordingStatusLabel->setText("Status: Ready");
    }
    
    int hours = m_recordingTime / 3600;
    int minutes = (m_recordingTime % 3600) / 60;
    int seconds = m_recordingTime % 60;
    m_recordingTimeLabel->setText(QString("Recording Time: %1:%2:%3")
                                  .arg(hours, 2, 10, QChar('0'))
                                  .arg(minutes, 2, 10, QChar('0'))
                                  .arg(seconds, 2, 10, QChar('0')));
    
    // Update disk space
    QStorageInfo storage(m_recordingsPath);
    if (storage.isValid()) {
        qint64 available = storage.bytesAvailable();
        qint64 total = storage.bytesTotal();
        int usedPercent = static_cast<int>((total - available) * 100 / total);
        m_diskSpaceBar->setValue(usedPercent);
    }
}
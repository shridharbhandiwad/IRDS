#include "cvideoplayerwindow.h"
#include <QMouseEvent>
#include <QScreen>
#include <QApplication>
#include <QDebug>

CVideoPlayerWindow::CVideoPlayerWindow(QWidget *parent)
    : QWidget(parent)
    , m_isPlaying(false)
    , m_isMaximized(false)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setWindowTitle("📹 Screen Recording Replay");
    
    setupUI();
    applyModernStyle();
    
    // Set default size
    resize(640, 480);
}

CVideoPlayerWindow::~CVideoPlayerWindow()
{
}

void CVideoPlayerWindow::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    
    createTitleBar();
    createVideoArea();
    createControlsArea();
}

void CVideoPlayerWindow::createTitleBar()
{
    m_titleBar = new QWidget(this);
    m_titleBar->setFixedHeight(40);
    m_titleBar->setObjectName("titleBar");
    
    QHBoxLayout *titleLayout = new QHBoxLayout(m_titleBar);
    titleLayout->setContentsMargins(10, 0, 10, 0);
    titleLayout->setSpacing(5);
    
    // Title icon and label
    m_titleLabel = new QLabel("📹 Video Replay");
    m_titleLabel->setObjectName("titleLabel");
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(11);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    
    titleLayout->addWidget(m_titleLabel);
    titleLayout->addStretch();
    
    // Window control buttons
    m_minimizeButton = new QPushButton("−");
    m_minimizeButton->setFixedSize(30, 30);
    m_minimizeButton->setObjectName("minimizeButton");
    m_minimizeButton->setCursor(Qt::PointingHandCursor);
    connect(m_minimizeButton, &QPushButton::clicked, this, &CVideoPlayerWindow::showMinimized);
    
    m_maximizeButton = new QPushButton("□");
    m_maximizeButton->setFixedSize(30, 30);
    m_maximizeButton->setObjectName("maximizeButton");
    m_maximizeButton->setCursor(Qt::PointingHandCursor);
    connect(m_maximizeButton, &QPushButton::clicked, this, [this]() {
        if (m_isMaximized) {
            setGeometry(m_normalGeometry);
            m_maximizeButton->setText("□");
            m_isMaximized = false;
        } else {
            m_normalGeometry = geometry();
            QScreen *screen = QApplication::primaryScreen();
            setGeometry(screen->availableGeometry());
            m_maximizeButton->setText("❐");
            m_isMaximized = true;
        }
    });
    
    m_closeButton = new QPushButton("×");
    m_closeButton->setFixedSize(30, 30);
    m_closeButton->setObjectName("closeButton");
    m_closeButton->setCursor(Qt::PointingHandCursor);
    connect(m_closeButton, &QPushButton::clicked, this, &CVideoPlayerWindow::close);
    
    titleLayout->addWidget(m_minimizeButton);
    titleLayout->addWidget(m_maximizeButton);
    titleLayout->addWidget(m_closeButton);
    
    m_mainLayout->addWidget(m_titleBar);
}

void CVideoPlayerWindow::createVideoArea()
{
    m_videoWidget = new QWidget(this);
    m_videoWidget->setObjectName("videoWidget");
    m_videoWidget->setMinimumHeight(300);
    
    QVBoxLayout *videoLayout = new QVBoxLayout(m_videoWidget);
    videoLayout->setContentsMargins(0, 0, 0, 0);
    
    // Placeholder for video display
    m_videoPlaceholder = new QLabel("🎬 No video loaded\n\nClick 'Load Video' to select a recording");
    m_videoPlaceholder->setObjectName("videoPlaceholder");
    m_videoPlaceholder->setAlignment(Qt::AlignCenter);
    QFont placeholderFont = m_videoPlaceholder->font();
    placeholderFont.setPointSize(14);
    m_videoPlaceholder->setFont(placeholderFont);
    videoLayout->addWidget(m_videoPlaceholder);
    
    m_mainLayout->addWidget(m_videoWidget);
}

void CVideoPlayerWindow::createControlsArea()
{
    m_controlsWidget = new QWidget(this);
    m_controlsWidget->setObjectName("controlsWidget");
    m_controlsWidget->setFixedHeight(100);
    
    QVBoxLayout *controlsLayout = new QVBoxLayout(m_controlsWidget);
    controlsLayout->setContentsMargins(15, 10, 15, 10);
    controlsLayout->setSpacing(10);
    
    // Progress slider
    QHBoxLayout *progressLayout = new QHBoxLayout();
    
    m_timeLabel = new QLabel("00:00");
    m_timeLabel->setFixedWidth(50);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    
    m_progressSlider = new QSlider(Qt::Horizontal);
    m_progressSlider->setRange(0, 100);
    m_progressSlider->setValue(0);
    m_progressSlider->setEnabled(false);
    connect(m_progressSlider, &QSlider::sliderMoved, this, &CVideoPlayerWindow::seekVideo);
    
    m_durationLabel = new QLabel("00:00");
    m_durationLabel->setFixedWidth(50);
    m_durationLabel->setAlignment(Qt::AlignCenter);
    
    progressLayout->addWidget(m_timeLabel);
    progressLayout->addWidget(m_progressSlider);
    progressLayout->addWidget(m_durationLabel);
    
    controlsLayout->addLayout(progressLayout);
    
    // Playback buttons
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    
    m_loadButton = new QPushButton("📂 Load Video");
    m_loadButton->setMinimumHeight(35);
    m_loadButton->setMinimumWidth(120);
    m_loadButton->setCursor(Qt::PointingHandCursor);
    connect(m_loadButton, &QPushButton::clicked, this, [this]() {
        QString videoPath = QFileDialog::getOpenFileName(
            this,
            "Select Video Recording",
            QDir::homePath(),
            "Video Files (*.mp4 *.avi *.mkv *.mov);;All Files (*.*)"
        );
        if (!videoPath.isEmpty()) {
            loadVideo(videoPath);
        }
    });
    
    m_playButton = new QPushButton("▶ Play");
    m_playButton->setMinimumHeight(35);
    m_playButton->setMinimumWidth(100);
    m_playButton->setCursor(Qt::PointingHandCursor);
    m_playButton->setEnabled(false);
    connect(m_playButton, &QPushButton::clicked, this, &CVideoPlayerWindow::playVideo);
    
    m_pauseButton = new QPushButton("⏸ Pause");
    m_pauseButton->setMinimumHeight(35);
    m_pauseButton->setMinimumWidth(100);
    m_pauseButton->setCursor(Qt::PointingHandCursor);
    m_pauseButton->setEnabled(false);
    connect(m_pauseButton, &QPushButton::clicked, this, &CVideoPlayerWindow::pauseVideo);
    
    m_stopButton = new QPushButton("⏹ Stop");
    m_stopButton->setMinimumHeight(35);
    m_stopButton->setMinimumWidth(100);
    m_stopButton->setCursor(Qt::PointingHandCursor);
    m_stopButton->setEnabled(false);
    connect(m_stopButton, &QPushButton::clicked, this, &CVideoPlayerWindow::stopVideo);
    
    buttonsLayout->addWidget(m_loadButton);
    buttonsLayout->addWidget(m_playButton);
    buttonsLayout->addWidget(m_pauseButton);
    buttonsLayout->addWidget(m_stopButton);
    buttonsLayout->addStretch();
    
    controlsLayout->addLayout(buttonsLayout);
    
    m_mainLayout->addWidget(m_controlsWidget);
}

void CVideoPlayerWindow::applyModernStyle()
{
    setStyleSheet(
        "CVideoPlayerWindow {"
        "   background-color: #1e293b;"
        "   border: 2px solid #475569;"
        "   border-radius: 12px;"
        "}"
        "QWidget#titleBar {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "       stop:0 #667eea, stop:0.5 #764ba2, stop:1 #667eea);"
        "   border-top-left-radius: 10px;"
        "   border-top-right-radius: 10px;"
        "}"
        "QLabel#titleLabel {"
        "   color: white;"
        "   padding: 5px;"
        "}"
        "QPushButton#minimizeButton, QPushButton#maximizeButton, QPushButton#closeButton {"
        "   background-color: rgba(255, 255, 255, 0.1);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 15px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton#minimizeButton:hover, QPushButton#maximizeButton:hover {"
        "   background-color: rgba(255, 255, 255, 0.2);"
        "}"
        "QPushButton#closeButton:hover {"
        "   background-color: #ef4444;"
        "}"
        "QWidget#videoWidget {"
        "   background-color: #0f172a;"
        "   border: none;"
        "}"
        "QLabel#videoPlaceholder {"
        "   color: #94a3b8;"
        "   background-color: #0f172a;"
        "}"
        "QWidget#controlsWidget {"
        "   background-color: #1e293b;"
        "   border-top: 1px solid #475569;"
        "   border-bottom-left-radius: 10px;"
        "   border-bottom-right-radius: 10px;"
        "}"
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #667eea, stop:1 #764ba2);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "   font-size: 11px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #5568d3, stop:1 #6b3fa0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #4c51bf, stop:1 #5a32a3);"
        "}"
        "QPushButton:disabled {"
        "   background-color: #4a5568;"
        "   color: #a0aec0;"
        "}"
        "QSlider::groove:horizontal {"
        "   background: #334155;"
        "   height: 6px;"
        "   border-radius: 3px;"
        "}"
        "QSlider::handle:horizontal {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "       stop:0 #667eea, stop:1 #764ba2);"
        "   width: 16px;"
        "   height: 16px;"
        "   margin: -5px 0;"
        "   border-radius: 8px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "       stop:0 #667eea, stop:1 #764ba2);"
        "   border-radius: 3px;"
        "}"
        "QLabel {"
        "   color: #e2e8f0;"
        "   font-size: 10px;"
        "}"
    );
}

void CVideoPlayerWindow::loadVideo(const QString &videoPath)
{
    m_currentVideoPath = videoPath;
    
    // Update UI
    m_videoPlaceholder->setText(QString("📹 Loaded: %1\n\nReady to play")
        .arg(QFileInfo(videoPath).fileName()));
    
    m_playButton->setEnabled(true);
    m_progressSlider->setEnabled(true);
    
    // Reset state
    m_progressSlider->setValue(0);
    m_timeLabel->setText("00:00");
    m_durationLabel->setText("05:30"); // Example duration
    
    emit videoLoaded(videoPath);
    
    qDebug() << "[VideoPlayer] Loaded video:" << videoPath;
}

void CVideoPlayerWindow::playVideo()
{
    if (m_currentVideoPath.isEmpty()) return;
    
    m_isPlaying = true;
    m_playButton->setEnabled(false);
    m_pauseButton->setEnabled(true);
    m_stopButton->setEnabled(true);
    
    m_videoPlaceholder->setText(QString("▶ Playing: %1")
        .arg(QFileInfo(m_currentVideoPath).fileName()));
    
    emit playbackStateChanged(true);
    
    qDebug() << "[VideoPlayer] Playing video";
}

void CVideoPlayerWindow::pauseVideo()
{
    m_isPlaying = false;
    m_playButton->setEnabled(true);
    m_pauseButton->setEnabled(false);
    
    m_videoPlaceholder->setText(QString("⏸ Paused: %1")
        .arg(QFileInfo(m_currentVideoPath).fileName()));
    
    emit playbackStateChanged(false);
    
    qDebug() << "[VideoPlayer] Paused video";
}

void CVideoPlayerWindow::stopVideo()
{
    m_isPlaying = false;
    m_playButton->setEnabled(true);
    m_pauseButton->setEnabled(false);
    m_stopButton->setEnabled(false);
    
    m_progressSlider->setValue(0);
    m_timeLabel->setText("00:00");
    
    m_videoPlaceholder->setText(QString("⏹ Stopped: %1\n\nClick Play to resume")
        .arg(QFileInfo(m_currentVideoPath).fileName()));
    
    emit playbackStateChanged(false);
    
    qDebug() << "[VideoPlayer] Stopped video";
}

void CVideoPlayerWindow::seekVideo(int position)
{
    qDebug() << "[VideoPlayer] Seeking to position:" << position;
    
    // Update time label (simulated)
    int seconds = (position * 330) / 100; // Assuming 5:30 duration
    int mins = seconds / 60;
    int secs = seconds % 60;
    m_timeLabel->setText(QString("%1:%2")
        .arg(mins, 2, 10, QChar('0'))
        .arg(secs, 2, 10, QChar('0')));
}

void CVideoPlayerWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Only allow dragging from title bar
        if (event->pos().y() <= m_titleBar->height()) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void CVideoPlayerWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (!m_dragPosition.isNull() && !m_isMaximized) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
    }
}

void CVideoPlayerWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = QPoint();
    }
}

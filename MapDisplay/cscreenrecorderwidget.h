#ifndef CSCREENRECORDERWIDGET_H
#define CSCREENRECORDERWIDGET_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QSlider>
#include <QCheckBox>
#include <QGroupBox>
#include <QTimer>
#include <QProgressBar>
#include <QTextEdit>
#include <QListWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QPixmap>
#include <QScreen>
#include <QApplication>
#include <QDateTime>

class CScreenRecorderWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CScreenRecorderWidget(QWidget *parent = nullptr);
    ~CScreenRecorderWidget();

private slots:
    void onStartRecording();
    void onStopRecording();
    void onPauseRecording();
    void onTakeScreenshot();
    void onOpenRecordingsFolder();
    void onPlayRecording();
    void onDeleteRecording();
    void onRecordingTimer();
    void onQualityChanged(int quality);
    void onFrameRateChanged(int fps);
    void onRecordingSelectionChanged();

private:
    void setupUI();
    void applyModernTheme();
    void updateRecordingsList();
    void captureFrame();
    void saveRecordingSession();
    void loadRecordingSession(const QString& filename);
    void updateRecordingStatus();

    // UI Components
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    
    // Recording Control Group
    QGroupBox *m_recordGroup;
    QPushButton *m_startRecordButton;
    QPushButton *m_stopRecordButton;
    QPushButton *m_pauseRecordButton;
    QPushButton *m_screenshotButton;
    
    // Recording Settings Group
    QGroupBox *m_settingsGroup;
    QComboBox *m_qualityCombo;
    QSlider *m_frameRateSlider;
    QLabel *m_frameRateLabel;
    QCheckBox *m_audioRecordCheck;
    QCheckBox *m_cursorRecordCheck;
    
    // Recordings Management Group
    QGroupBox *m_recordingsGroup;
    QListWidget *m_recordingsList;
    QPushButton *m_playButton;
    QPushButton *m_deleteButton;
    QPushButton *m_openFolderButton;
    
    // Status Group
    QGroupBox *m_statusGroup;
    QLabel *m_recordingStatusLabel;
    QLabel *m_recordingTimeLabel;
    QProgressBar *m_diskSpaceBar;
    QTextEdit *m_logText;
    
    // Recording State
    QTimer *m_recordingTimer;
    QTimer *m_captureTimer;
    
    bool m_isRecording;
    bool m_isPaused;
    int m_recordingTime;
    int m_frameRate;
    int m_quality;
    
    QString m_recordingsPath;
    QString m_currentRecordingFile;
    QList<QPixmap> m_recordedFrames;
    
    // Recording session data
    struct RecordingSession {
        QString filename;
        QDateTime timestamp;
        int duration;
        int frameCount;
        QString description;
    };
    
    QList<RecordingSession> m_recordingSessions;
    
    // Constants
    static constexpr int MIN_FRAME_RATE = 1;
    static constexpr int MAX_FRAME_RATE = 60;
    static constexpr int DEFAULT_FRAME_RATE = 10;
};

#endif // CSCREENRECORDERWIDGET_H
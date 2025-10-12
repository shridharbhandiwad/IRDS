#ifndef CVIDEOPLAYERWINDOW_H
#define CVIDEOPLAYERWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QFileDialog>
#include <QStyle>

/**
 * @brief Floating window for video replay with playback controls
 * 
 * Features:
 * - Video display area (simulated for now, can be replaced with QMediaPlayer later)
 * - Playback controls (play/pause/stop)
 * - Progress slider
 * - Minimize/Maximize/Close buttons in title bar
 */
class CVideoPlayerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CVideoPlayerWindow(QWidget *parent = nullptr);
    ~CVideoPlayerWindow();

public slots:
    void loadVideo(const QString &videoPath);
    void playVideo();
    void pauseVideo();
    void stopVideo();
    void seekVideo(int position);

signals:
    void videoLoaded(const QString &path);
    void playbackStateChanged(bool isPlaying);

private:
    void setupUI();
    void createTitleBar();
    void createVideoArea();
    void createControlsArea();
    void applyModernStyle();
    
    // Title bar widgets
    QWidget *m_titleBar;
    QLabel *m_titleLabel;
    QPushButton *m_minimizeButton;
    QPushButton *m_maximizeButton;
    QPushButton *m_closeButton;
    
    // Video area
    QWidget *m_videoWidget;
    QLabel *m_videoPlaceholder;
    
    // Controls
    QWidget *m_controlsWidget;
    QPushButton *m_playButton;
    QPushButton *m_pauseButton;
    QPushButton *m_stopButton;
    QPushButton *m_loadButton;
    QSlider *m_progressSlider;
    QLabel *m_timeLabel;
    QLabel *m_durationLabel;
    
    // State
    bool m_isPlaying;
    bool m_isMaximized;
    QString m_currentVideoPath;
    QPoint m_dragPosition;
    QRect m_normalGeometry;
    
    // Window dragging
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    
    // Main layouts
    QVBoxLayout *m_mainLayout;
};

#endif // CVIDEOPLAYERWINDOW_H

#ifndef CANALYTICSPANELWIDGET_H
#define CANALYTICSPANELWIDGET_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QComboBox>

class CAnalyticsPanelWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CAnalyticsPanelWidget(QWidget *parent = nullptr);
    ~CAnalyticsPanelWidget();

    /**
     * @brief Set the selected track ID for detailed analytics
     * @param trackId Track ID to analyze, -1 for all tracks
     */
    void setSelectedTrack(int trackId);

private slots:
    void updateAnalytics();
    void onRefreshRequested();
    void onViewModeChanged(int index);

private:
    void setupUI();
    void updateAllTracksStats();
    void updateSelectedTrackStats();
    void applyModernTheme();

    // UI Components
    QWidget *m_mainWidget;
    QVBoxLayout *m_mainLayout;
    
    // View mode selector
    QComboBox *m_viewModeCombo;
    
    // All Tracks Statistics Group
    QGroupBox *m_allTracksGroup;
    QLabel *m_totalTracksLabel;
    QLabel *m_friendlyCountLabel;
    QLabel *m_hostileCountLabel;
    QLabel *m_unknownCountLabel;
    QLabel *m_avgRangeLabel;
    QLabel *m_avgVelocityLabel;
    QLabel *m_avgHeadingLabel;
    QLabel *m_maxRangeLabel;
    QLabel *m_minRangeLabel;
    
    // Selected Track Statistics Group
    QGroupBox *m_selectedTrackGroup;
    QLabel *m_selectedIdLabel;
    QLabel *m_selectedRangeLabel;
    QLabel *m_selectedAzimuthLabel;
    QLabel *m_selectedElevationLabel;
    QLabel *m_selectedHeadingLabel;
    QLabel *m_selectedVelocityLabel;
    QLabel *m_selectedLatLabel;
    QLabel *m_selectedLonLabel;
    QLabel *m_selectedAltLabel;
    QLabel *m_selectedSnrLabel;
    QLabel *m_selectedIdentityLabel;
    
    // Performance Metrics Group
    QGroupBox *m_performanceGroup;
    QLabel *m_updateRateLabel;
    QLabel *m_dataRateLabel;
    QLabel *m_uptimeLabel;
    
    // Control buttons
    QPushButton *m_refreshButton;
    
    // Timer for automatic updates
    QTimer *m_updateTimer;
    
    // Current selected track
    int m_selectedTrackId;
    
    // Performance tracking
    int m_updateCount;
    QDateTime m_startTime;
};

#endif // CANALYTICSPANELWIDGET_H

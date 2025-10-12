#include "canalyticspanelwidget.h"
#include "../cdatawarehouse.h"
#include <QGridLayout>
#include <QScrollArea>
#include <QDateTime>
#include <cmath>

CAnalyticsPanelWidget::CAnalyticsPanelWidget(QWidget *parent)
    : QDockWidget(parent)
    , m_selectedTrackId(-1)
    , m_updateCount(0)
    , m_startTime(QDateTime::currentDateTime())
{
    setWindowTitle("📊 Analytics Panel");
    setObjectName("AnalyticsPanel");
    
    setupUI();
    applyModernTheme();
    
    // Setup update timer (update every second)
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &CAnalyticsPanelWidget::updateAnalytics);
    m_updateTimer->start(1000);
}

CAnalyticsPanelWidget::~CAnalyticsPanelWidget()
{
}

void CAnalyticsPanelWidget::setupUI()
{
    m_mainWidget = new QWidget(this);
    m_mainLayout = new QVBoxLayout(m_mainWidget);
    m_mainLayout->setSpacing(10);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // View mode selector
    QHBoxLayout *viewModeLayout = new QHBoxLayout();
    QLabel *viewLabel = new QLabel("📈 View Mode:", m_mainWidget);
    viewLabel->setStyleSheet("font-weight: bold; font-size: 12px;");
    m_viewModeCombo = new QComboBox(m_mainWidget);
    m_viewModeCombo->addItem("🌐 All Tracks");
    m_viewModeCombo->addItem("🎯 Selected Track");
    m_viewModeCombo->addItem("📊 Both Views");
    m_viewModeCombo->setCurrentIndex(2); // Both views by default
    connect(m_viewModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CAnalyticsPanelWidget::onViewModeChanged);
    viewModeLayout->addWidget(viewLabel);
    viewModeLayout->addWidget(m_viewModeCombo, 1);
    m_mainLayout->addLayout(viewModeLayout);
    
    // === All Tracks Statistics Group ===
    m_allTracksGroup = new QGroupBox("🌐 All Tracks Statistics", m_mainWidget);
    QGridLayout *allTracksLayout = new QGridLayout(m_allTracksGroup);
    allTracksLayout->setSpacing(8);
    allTracksLayout->setContentsMargins(12, 18, 12, 12);
    
    int row = 0;
    
    // Total tracks
    QLabel *totalLabel = new QLabel("Total Tracks:", m_allTracksGroup);
    totalLabel->setStyleSheet("font-weight: bold;");
    m_totalTracksLabel = new QLabel("0", m_allTracksGroup);
    m_totalTracksLabel->setStyleSheet("color: #10b981; font-size: 14px; font-weight: bold;");
    allTracksLayout->addWidget(totalLabel, row, 0);
    allTracksLayout->addWidget(m_totalTracksLabel, row, 1);
    row++;
    
    // Friendly count
    QLabel *friendlyLabel = new QLabel("✓ Friendly:", m_allTracksGroup);
    m_friendlyCountLabel = new QLabel("0", m_allTracksGroup);
    m_friendlyCountLabel->setStyleSheet("color: #10b981;");
    allTracksLayout->addWidget(friendlyLabel, row, 0);
    allTracksLayout->addWidget(m_friendlyCountLabel, row, 1);
    row++;
    
    // Hostile count
    QLabel *hostileLabel = new QLabel("✖ Hostile:", m_allTracksGroup);
    m_hostileCountLabel = new QLabel("0", m_allTracksGroup);
    m_hostileCountLabel->setStyleSheet("color: #ef4444;");
    allTracksLayout->addWidget(hostileLabel, row, 0);
    allTracksLayout->addWidget(m_hostileCountLabel, row, 1);
    row++;
    
    // Unknown count
    QLabel *unknownLabel = new QLabel("? Unknown:", m_allTracksGroup);
    m_unknownCountLabel = new QLabel("0", m_allTracksGroup);
    m_unknownCountLabel->setStyleSheet("color: #f59e0b;");
    allTracksLayout->addWidget(unknownLabel, row, 0);
    allTracksLayout->addWidget(m_unknownCountLabel, row, 1);
    row++;
    
    // Separator
    QFrame *line1 = new QFrame(m_allTracksGroup);
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    allTracksLayout->addWidget(line1, row, 0, 1, 2);
    row++;
    
    // Average range
    QLabel *avgRangeLabel = new QLabel("Avg Range:", m_allTracksGroup);
    m_avgRangeLabel = new QLabel("0.0 km", m_allTracksGroup);
    allTracksLayout->addWidget(avgRangeLabel, row, 0);
    allTracksLayout->addWidget(m_avgRangeLabel, row, 1);
    row++;
    
    // Max/Min range
    QLabel *maxRangeLabel = new QLabel("Max Range:", m_allTracksGroup);
    m_maxRangeLabel = new QLabel("0.0 km", m_allTracksGroup);
    allTracksLayout->addWidget(maxRangeLabel, row, 0);
    allTracksLayout->addWidget(m_maxRangeLabel, row, 1);
    row++;
    
    QLabel *minRangeLabel = new QLabel("Min Range:", m_allTracksGroup);
    m_minRangeLabel = new QLabel("0.0 km", m_allTracksGroup);
    allTracksLayout->addWidget(minRangeLabel, row, 0);
    allTracksLayout->addWidget(m_minRangeLabel, row, 1);
    row++;
    
    // Average velocity
    QLabel *avgVelLabel = new QLabel("Avg Velocity:", m_allTracksGroup);
    m_avgVelocityLabel = new QLabel("0.0 m/s", m_allTracksGroup);
    allTracksLayout->addWidget(avgVelLabel, row, 0);
    allTracksLayout->addWidget(m_avgVelocityLabel, row, 1);
    row++;
    
    // Average heading
    QLabel *avgHeadLabel = new QLabel("Avg Heading:", m_allTracksGroup);
    m_avgHeadingLabel = new QLabel("0.0°", m_allTracksGroup);
    allTracksLayout->addWidget(avgHeadLabel, row, 0);
    allTracksLayout->addWidget(m_avgHeadingLabel, row, 1);
    
    m_mainLayout->addWidget(m_allTracksGroup);
    
    // === Selected Track Statistics Group ===
    m_selectedTrackGroup = new QGroupBox("🎯 Selected Track Details", m_mainWidget);
    QGridLayout *selectedLayout = new QGridLayout(m_selectedTrackGroup);
    selectedLayout->setSpacing(8);
    selectedLayout->setContentsMargins(12, 18, 12, 12);
    
    row = 0;
    
    // Track ID
    QLabel *idLabel = new QLabel("Track ID:", m_selectedTrackGroup);
    idLabel->setStyleSheet("font-weight: bold;");
    m_selectedIdLabel = new QLabel("None", m_selectedTrackGroup);
    m_selectedIdLabel->setStyleSheet("color: #10b981; font-size: 14px; font-weight: bold;");
    selectedLayout->addWidget(idLabel, row, 0);
    selectedLayout->addWidget(m_selectedIdLabel, row, 1);
    row++;
    
    // Identity
    QLabel *identityLabel = new QLabel("Identity:", m_selectedTrackGroup);
    m_selectedIdentityLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(identityLabel, row, 0);
    selectedLayout->addWidget(m_selectedIdentityLabel, row, 1);
    row++;
    
    // Separator
    QFrame *line2 = new QFrame(m_selectedTrackGroup);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    selectedLayout->addWidget(line2, row, 0, 1, 2);
    row++;
    
    // Range
    QLabel *rangeLabel = new QLabel("Range:", m_selectedTrackGroup);
    m_selectedRangeLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(rangeLabel, row, 0);
    selectedLayout->addWidget(m_selectedRangeLabel, row, 1);
    row++;
    
    // Azimuth
    QLabel *azLabel = new QLabel("Azimuth:", m_selectedTrackGroup);
    m_selectedAzimuthLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(azLabel, row, 0);
    selectedLayout->addWidget(m_selectedAzimuthLabel, row, 1);
    row++;
    
    // Elevation
    QLabel *elLabel = new QLabel("Elevation:", m_selectedTrackGroup);
    m_selectedElevationLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(elLabel, row, 0);
    selectedLayout->addWidget(m_selectedElevationLabel, row, 1);
    row++;
    
    // Heading
    QLabel *headLabel = new QLabel("Heading:", m_selectedTrackGroup);
    m_selectedHeadingLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(headLabel, row, 0);
    selectedLayout->addWidget(m_selectedHeadingLabel, row, 1);
    row++;
    
    // Velocity
    QLabel *velLabel = new QLabel("Velocity:", m_selectedTrackGroup);
    m_selectedVelocityLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(velLabel, row, 0);
    selectedLayout->addWidget(m_selectedVelocityLabel, row, 1);
    row++;
    
    // SNR
    QLabel *snrLabel = new QLabel("SNR:", m_selectedTrackGroup);
    m_selectedSnrLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(snrLabel, row, 0);
    selectedLayout->addWidget(m_selectedSnrLabel, row, 1);
    row++;
    
    // Separator
    QFrame *line3 = new QFrame(m_selectedTrackGroup);
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);
    selectedLayout->addWidget(line3, row, 0, 1, 2);
    row++;
    
    // Latitude
    QLabel *latLabel = new QLabel("Latitude:", m_selectedTrackGroup);
    m_selectedLatLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(latLabel, row, 0);
    selectedLayout->addWidget(m_selectedLatLabel, row, 1);
    row++;
    
    // Longitude
    QLabel *lonLabel = new QLabel("Longitude:", m_selectedTrackGroup);
    m_selectedLonLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(lonLabel, row, 0);
    selectedLayout->addWidget(m_selectedLonLabel, row, 1);
    row++;
    
    // Altitude
    QLabel *altLabel = new QLabel("Altitude:", m_selectedTrackGroup);
    m_selectedAltLabel = new QLabel("-", m_selectedTrackGroup);
    selectedLayout->addWidget(altLabel, row, 0);
    selectedLayout->addWidget(m_selectedAltLabel, row, 1);
    
    m_mainLayout->addWidget(m_selectedTrackGroup);
    
    // === Performance Metrics Group ===
    m_performanceGroup = new QGroupBox("⚡ Performance Metrics", m_mainWidget);
    QGridLayout *perfLayout = new QGridLayout(m_performanceGroup);
    perfLayout->setSpacing(8);
    perfLayout->setContentsMargins(12, 18, 12, 12);
    
    row = 0;
    
    QLabel *updateRateLabel = new QLabel("Update Rate:", m_performanceGroup);
    m_updateRateLabel = new QLabel("0 Hz", m_performanceGroup);
    perfLayout->addWidget(updateRateLabel, row, 0);
    perfLayout->addWidget(m_updateRateLabel, row, 1);
    row++;
    
    QLabel *dataRateLabel = new QLabel("Data Rate:", m_performanceGroup);
    m_dataRateLabel = new QLabel("0 tracks/s", m_performanceGroup);
    perfLayout->addWidget(dataRateLabel, row, 0);
    perfLayout->addWidget(m_dataRateLabel, row, 1);
    row++;
    
    QLabel *uptimeLabel = new QLabel("Uptime:", m_performanceGroup);
    m_uptimeLabel = new QLabel("0s", m_performanceGroup);
    perfLayout->addWidget(uptimeLabel, row, 0);
    perfLayout->addWidget(m_uptimeLabel, row, 1);
    
    m_mainLayout->addWidget(m_performanceGroup);
    
    // Refresh button
    m_refreshButton = new QPushButton("🔄 Refresh Now", m_mainWidget);
    connect(m_refreshButton, &QPushButton::clicked, this, &CAnalyticsPanelWidget::onRefreshRequested);
    m_mainLayout->addWidget(m_refreshButton);
    
    // Add stretch to push everything to the top
    m_mainLayout->addStretch();
    
    // Create scroll area for all content
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(m_mainWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    setWidget(scrollArea);
}

void CAnalyticsPanelWidget::applyModernTheme()
{
    QString theme = 
        "QDockWidget {"
        "   background-color: #0f172a;"
        "   color: #ffffff;"
        "   font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QDockWidget::title {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "   padding: 8px;"
        "   color: white;"
        "   font-weight: bold;"
        "   font-size: 13px;"
        "}"
        "QGroupBox {"
        "   background-color: #1e293b;"
        "   border: 2px solid #475569;"
        "   border-radius: 8px;"
        "   margin-top: 12px;"
        "   padding-top: 12px;"
        "   font-weight: bold;"
        "   color: #ffffff;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top left;"
        "   padding: 6px 12px;"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "   border-radius: 6px;"
        "   color: white;"
        "   font-size: 12px;"
        "   left: 10px;"
        "}"
        "QLabel {"
        "   color: #e2e8f0;"
        "   font-size: 11px;"
        "   padding: 2px;"
        "}"
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #667eea, stop:1 #764ba2);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 10px;"
        "   font-weight: bold;"
        "   font-size: 12px;"
        "   min-height: 28px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #5568d3, stop:1 #6b3fa0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4c51bf, stop:1 #5a32a3);"
        "}"
        "QComboBox {"
        "   background-color: #1e293b;"
        "   color: #ffffff;"
        "   border: 2px solid #475569;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "   font-size: 11px;"
        "}"
        "QComboBox:hover {"
        "   border: 2px solid #667eea;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #1e293b;"
        "   color: #ffffff;"
        "   selection-background-color: #667eea;"
        "   border: 2px solid #475569;"
        "}"
        "QScrollArea {"
        "   background-color: #0f172a;"
        "   border: none;"
        "}"
        "QScrollBar:vertical {"
        "   background-color: #1e293b;"
        "   width: 12px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background-color: #475569;"
        "   border-radius: 6px;"
        "   min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "   background-color: #667eea;"
        "}"
        "QFrame[frameShape=\"4\"] {" // HLine
        "   color: #475569;"
        "}";
    
    setStyleSheet(theme);
}

void CAnalyticsPanelWidget::setSelectedTrack(int trackId)
{
    m_selectedTrackId = trackId;
    updateAnalytics();
}

void CAnalyticsPanelWidget::updateAnalytics()
{
    m_updateCount++;
    
    int viewMode = m_viewModeCombo->currentIndex();
    
    // Update visibility based on view mode
    m_allTracksGroup->setVisible(viewMode == 0 || viewMode == 2);
    m_selectedTrackGroup->setVisible(viewMode == 1 || viewMode == 2);
    
    if (viewMode == 0 || viewMode == 2) {
        updateAllTracksStats();
    }
    
    if (viewMode == 1 || viewMode == 2) {
        updateSelectedTrackStats();
    }
    
    // Update performance metrics
    qint64 uptimeSeconds = m_startTime.secsTo(QDateTime::currentDateTime());
    m_uptimeLabel->setText(QString("%1s").arg(uptimeSeconds));
    
    if (uptimeSeconds > 0) {
        double updateRate = m_updateCount / static_cast<double>(uptimeSeconds);
        m_updateRateLabel->setText(QString("%1 Hz").arg(updateRate, 0, 'f', 2));
    }
}

void CAnalyticsPanelWidget::updateAllTracksStats()
{
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    
    int totalTracks = tracks.count();
    int friendlyCount = 0;
    int hostileCount = 0;
    int unknownCount = 0;
    
    double totalRange = 0.0;
    double maxRange = 0.0;
    double minRange = std::numeric_limits<double>::max();
    double totalVelocity = 0.0;
    double totalHeading = 0.0;
    
    for (const stTrackDisplayInfo &track : tracks) {
        // Count by identity
        switch (track.nTrackIden) {
            case 2: // TRACK_IDENTITY_FRIEND
                friendlyCount++;
                break;
            case 3: // TRACK_IDENTITY_HOSTILE
                hostileCount++;
                break;
            default: // Unknown or default
                unknownCount++;
                break;
        }
        
        // Calculate statistics
        totalRange += track.range;
        maxRange = std::max(maxRange, track.range);
        minRange = std::min(minRange, track.range);
        totalVelocity += track.velocity;
        totalHeading += track.heading;
    }
    
    // Update labels
    m_totalTracksLabel->setText(QString::number(totalTracks));
    m_friendlyCountLabel->setText(QString::number(friendlyCount));
    m_hostileCountLabel->setText(QString::number(hostileCount));
    m_unknownCountLabel->setText(QString::number(unknownCount));
    
    if (totalTracks > 0) {
        double avgRange = totalRange / totalTracks;
        double avgVelocity = totalVelocity / totalTracks;
        double avgHeading = totalHeading / totalTracks;
        
        m_avgRangeLabel->setText(QString("%1 km").arg(avgRange / 1000.0, 0, 'f', 2));
        m_maxRangeLabel->setText(QString("%1 km").arg(maxRange / 1000.0, 0, 'f', 2));
        m_minRangeLabel->setText(QString("%1 km").arg(minRange / 1000.0, 0, 'f', 2));
        m_avgVelocityLabel->setText(QString("%1 m/s").arg(avgVelocity, 0, 'f', 1));
        m_avgHeadingLabel->setText(QString("%1°").arg(avgHeading, 0, 'f', 1));
        
        // Update data rate
        m_dataRateLabel->setText(QString("%1 tracks/s").arg(totalTracks));
    } else {
        m_avgRangeLabel->setText("0.0 km");
        m_maxRangeLabel->setText("0.0 km");
        m_minRangeLabel->setText("0.0 km");
        m_avgVelocityLabel->setText("0.0 m/s");
        m_avgHeadingLabel->setText("0.0°");
        m_dataRateLabel->setText("0 tracks/s");
    }
}

void CAnalyticsPanelWidget::updateSelectedTrackStats()
{
    if (m_selectedTrackId < 0) {
        m_selectedIdLabel->setText("None Selected");
        m_selectedIdentityLabel->setText("-");
        m_selectedRangeLabel->setText("-");
        m_selectedAzimuthLabel->setText("-");
        m_selectedElevationLabel->setText("-");
        m_selectedHeadingLabel->setText("-");
        m_selectedVelocityLabel->setText("-");
        m_selectedSnrLabel->setText("-");
        m_selectedLatLabel->setText("-");
        m_selectedLonLabel->setText("-");
        m_selectedAltLabel->setText("-");
        return;
    }
    
    // Find the selected track
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    bool found = false;
    
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == m_selectedTrackId) {
            found = true;
            
            // Update all labels
            m_selectedIdLabel->setText(QString::number(track.nTrkId));
            
            // Identity with color
            QString identityStr;
            QString identityColor;
            switch (track.nTrackIden) {
                case 2: // TRACK_IDENTITY_FRIEND
                    identityStr = "✓ Friendly";
                    identityColor = "color: #10b981;";
                    break;
                case 3: // TRACK_IDENTITY_HOSTILE
                    identityStr = "✖ Hostile";
                    identityColor = "color: #ef4444;";
                    break;
                default:
                    identityStr = "? Unknown";
                    identityColor = "color: #f59e0b;";
                    break;
            }
            m_selectedIdentityLabel->setText(identityStr);
            m_selectedIdentityLabel->setStyleSheet(identityColor + " font-weight: bold;");
            
            m_selectedRangeLabel->setText(QString("%1 km").arg(track.range / 1000.0, 0, 'f', 2));
            m_selectedAzimuthLabel->setText(QString("%1°").arg(track.azimuth, 0, 'f', 2));
            m_selectedElevationLabel->setText(QString("%1°").arg(track.elevation, 0, 'f', 2));
            m_selectedHeadingLabel->setText(QString("%1°").arg(track.heading, 0, 'f', 1));
            m_selectedVelocityLabel->setText(QString("%1 m/s").arg(track.velocity, 0, 'f', 1));
            m_selectedSnrLabel->setText(QString("%1 dB").arg(track.snr, 0, 'f', 1));
            m_selectedLatLabel->setText(QString("%1°").arg(track.lat, 0, 'f', 5));
            m_selectedLonLabel->setText(QString("%1°").arg(track.lon, 0, 'f', 5));
            m_selectedAltLabel->setText(QString("%1 m").arg(track.alt, 0, 'f', 1));
            
            break;
        }
    }
    
    if (!found) {
        m_selectedIdLabel->setText(QString("Track #%1 Not Found").arg(m_selectedTrackId));
        m_selectedIdentityLabel->setText("-");
        m_selectedRangeLabel->setText("-");
        m_selectedAzimuthLabel->setText("-");
        m_selectedElevationLabel->setText("-");
        m_selectedHeadingLabel->setText("-");
        m_selectedVelocityLabel->setText("-");
        m_selectedSnrLabel->setText("-");
        m_selectedLatLabel->setText("-");
        m_selectedLonLabel->setText("-");
        m_selectedAltLabel->setText("-");
    }
}

void CAnalyticsPanelWidget::onRefreshRequested()
{
    updateAnalytics();
}

void CAnalyticsPanelWidget::onViewModeChanged(int index)
{
    Q_UNUSED(index);
    updateAnalytics();
}

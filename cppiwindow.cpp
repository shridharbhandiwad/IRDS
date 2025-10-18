#include "cppiwindow.h"
#include "MapDisplay/cmapcanvas.h"
#include "MapDisplay/ctracktablewidget.h"
#include "cdatawarehouse.h"
#include <QApplication>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QSplitter>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>

CPPIWindow::CPPIWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_settingsLayout(nullptr)
    , m_mapCanvas(nullptr)
    , m_trackTable(nullptr)
    , m_trackContextMenu(nullptr)
    , m_selectedTrackId(-1)
    , m_gridVisible(true)
    , m_compassVisible(true)
    , m_mapEnabled(true)
    , m_mapExpanded(false)
    , m_tableExpanded(false)
    , m_maxHistoryPoints(50)
    , m_statusTimer(new QTimer(this))
    , m_settings(new QSettings("RadarDisplay", "PPIWindow", this))
{
    setWindowTitle("🎯 PPI Display - Map & Tracks");
    setMinimumSize(1200, 800);
    
    setupUI();
    applyLightTheme();
    createTrackContextMenu();
    
    // Setup status timer
    connect(m_statusTimer, &QTimer::timeout, this, &CPPIWindow::updateStatusBar);
    m_statusTimer->start(1000);
    
    loadSettings();
}

CPPIWindow::~CPPIWindow()
{
    saveSettings();
}

void CPPIWindow::setupUI()
{
    // Create central widget with splitter
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setContentsMargins(8, 8, 8, 8);
    m_mainLayout->setSpacing(8);
    
    // Setup components
    setupSettingsToolbar();
    
    // Create horizontal splitter for map and track table
    m_splitter = new QSplitter(Qt::Horizontal, this);
    m_splitter->setChildrenCollapsible(true);
    
    setupMapCanvas();
    setupTrackTable();
    
    // Add to splitter
    m_splitter->addWidget(m_mapCanvas);
    m_splitter->addWidget(m_trackTable);
    
    // Set splitter proportions (70% map, 30% table)
    m_normalSplitterSizes = {700, 300};
    m_splitter->setSizes(m_normalSplitterSizes);
    m_splitter->setStretchFactor(0, 7);
    m_splitter->setStretchFactor(1, 3);
    
    m_mainLayout->addWidget(m_splitter);
    
    // Setup status bar
    statusBar()->setStyleSheet(
        "QStatusBar {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f8fafc, stop:1 #e2e8f0);"
        "   color: #334155;"
        "   border-top: 2px solid #3b82f6;"
        "   font-size: 12px;"
        "   font-weight: 500;"
        "   padding: 6px;"
        "}"
    );
}

void CPPIWindow::setupSettingsToolbar()
{
    m_settingsLayout = new QHBoxLayout();
    m_settingsLayout->setSpacing(8);
    m_settingsLayout->setContentsMargins(4, 4, 4, 4);
    
    // Create settings buttons with light theme
    m_loadMapBtn = new QPushButton("📁 Load Map", this);
    m_disableMapBtn = new QPushButton("🚫 Disable Map", this);
    m_zoomFitBtn = new QPushButton("🔍 Zoom Fit", this);
    m_homeBtn = new QPushButton("🏠 Home", this);
    m_gridBtn = new QPushButton("📐 Grid", this);
    m_compassBtn = new QPushButton("🧭 Compass", this);
    m_expandMapBtn = new QPushButton("🗺️ Expand Map", this);
    m_expandTableBtn = new QPushButton("📊 Expand Table", this);
    m_settingsBtn = new QPushButton("⚙️ Settings", this);
    
    // Make toggle buttons checkable
    m_gridBtn->setCheckable(true);
    m_gridBtn->setChecked(m_gridVisible);
    m_compassBtn->setCheckable(true);
    m_compassBtn->setChecked(m_compassVisible);
    m_disableMapBtn->setCheckable(true);
    m_disableMapBtn->setChecked(!m_mapEnabled);
    m_expandMapBtn->setCheckable(true);
    m_expandMapBtn->setChecked(m_mapExpanded);
    m_expandTableBtn->setCheckable(true);
    m_expandTableBtn->setChecked(m_tableExpanded);
    
    // Status label
    m_statusLabel = new QLabel("Ready", this);
    m_statusLabel->setStyleSheet(
        "QLabel {"
        "   color: #64748b;"
        "   font-weight: 500;"
        "   padding: 4px 8px;"
        "}"
    );
    
    // Add buttons to layout
    m_settingsLayout->addWidget(m_loadMapBtn);
    m_settingsLayout->addWidget(m_disableMapBtn);
    m_settingsLayout->addWidget(m_zoomFitBtn);
    m_settingsLayout->addWidget(m_homeBtn);
    m_settingsLayout->addWidget(m_gridBtn);
    m_settingsLayout->addWidget(m_compassBtn);
    m_settingsLayout->addSpacing(10);
    m_settingsLayout->addWidget(m_expandMapBtn);
    m_settingsLayout->addWidget(m_expandTableBtn);
    m_settingsLayout->addStretch();
    m_settingsLayout->addWidget(m_statusLabel);
    m_settingsLayout->addWidget(m_settingsBtn);
    
    // Connect signals
    connect(m_loadMapBtn, &QPushButton::clicked, this, &CPPIWindow::onLoadNewMap);
    connect(m_disableMapBtn, &QPushButton::clicked, this, &CPPIWindow::onDisableMap);
    connect(m_zoomFitBtn, &QPushButton::clicked, this, &CPPIWindow::onZoomFitToScreen);
    connect(m_homeBtn, &QPushButton::clicked, this, &CPPIWindow::onMapHome);
    connect(m_gridBtn, &QPushButton::clicked, this, &CPPIWindow::onToggleGrid);
    connect(m_compassBtn, &QPushButton::clicked, this, &CPPIWindow::onToggleCompass);
    connect(m_expandMapBtn, &QPushButton::clicked, this, &CPPIWindow::onExpandMap);
    connect(m_expandTableBtn, &QPushButton::clicked, this, &CPPIWindow::onExpandTable);
    connect(m_settingsBtn, &QPushButton::clicked, this, &CPPIWindow::onSettings);
    
    m_mainLayout->addLayout(m_settingsLayout);
}

void CPPIWindow::setupMapCanvas()
{
    m_mapCanvas = new CMapCanvas(this);
    m_mapCanvas->setMinimumSize(800, 600);
    m_mapCanvas->Initialize();
    
    // Connect map canvas signals
    connect(m_mapCanvas, SIGNAL(signalMouseRead(QString)), 
            this, SLOT(updateStatusBar()));
    
    // Connect track layer right-click signal
    if (m_mapCanvas->getTrackLayer()) {
        connect(m_mapCanvas->getTrackLayer(), &CTrackLayer::trackRightClicked,
                this, &CPPIWindow::onTrackRightClicked);
    }
}

void CPPIWindow::setupTrackTable()
{
    m_trackTable = new CTrackTableWidget(this);
    m_trackTable->setMinimumWidth(300);
    m_trackTable->setMaximumWidth(500);
    
    // Connect track table signals
    connect(m_trackTable, &CTrackTableWidget::trackSelected,
            this, &CPPIWindow::onTrackSelected);
    connect(m_trackTable, &CTrackTableWidget::trackDoubleClicked,
            this, &CPPIWindow::onTrackDoubleClicked);
    connect(m_trackTable, &CTrackTableWidget::trackRightClicked,
            this, &CPPIWindow::onTrackRightClicked);
}

void CPPIWindow::applyLightTheme()
{
    // Light theme with two primary colors: Blue (#3b82f6) and Light Gray (#f8fafc)
    QString lightTheme = 
        "CPPIWindow {"
        "   background-color: #f8fafc;"
        "   color: #1e293b;"
        "}"
        "QWidget {"
        "   background-color: #f8fafc;"
        "   color: #1e293b;"
        "   font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3b82f6, stop:1 #2563eb);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 16px;"
        "   font-weight: 600;"
        "   font-size: 12px;"
        "   min-height: 28px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2563eb, stop:1 #1d4ed8);"
        "   transform: translateY(-1px);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1d4ed8, stop:1 #1e40af);"
        "}"
        "QPushButton:checked {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #059669, stop:1 #047857);"
        "   border: 2px solid #10b981;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #e2e8f0;"
        "   color: #94a3b8;"
        "}"
        "QLabel {"
        "   color: #334155;"
        "   font-weight: 500;"
        "}"
        "QSplitter {"
        "   background-color: #e2e8f0;"
        "}"
        "QSplitter::handle {"
        "   background-color: #cbd5e1;"
        "   width: 3px;"
        "   border-radius: 1px;"
        "}"
        "QSplitter::handle:hover {"
        "   background-color: #3b82f6;"
        "}";
    
    setStyleSheet(lightTheme);
}

void CPPIWindow::createTrackContextMenu()
{
    m_trackContextMenu = new QMenu(this);
    
    m_focusTrackAction = m_trackContextMenu->addAction("🎯 Focus Track");
    m_trackContextMenu->addSeparator();
    m_toggleHistoryAction = m_trackContextMenu->addAction("📍 Toggle History (Max 50)");
    m_highlightAction = m_trackContextMenu->addAction("✨ Highlight & Follow");
    m_trackContextMenu->addSeparator();
    m_loadImageAction = m_trackContextMenu->addAction("🖼️ Load Track Image");
    m_trackContextMenu->addSeparator();
    m_deleteTrackAction = m_trackContextMenu->addAction("🗑️ Delete Track");
    
    // Connect actions
    connect(m_focusTrackAction, &QAction::triggered, this, &CPPIWindow::onFocusTrack);
    connect(m_deleteTrackAction, &QAction::triggered, this, &CPPIWindow::onDeleteTrack);
    connect(m_loadImageAction, &QAction::triggered, this, &CPPIWindow::onLoadTrackImage);
    connect(m_toggleHistoryAction, &QAction::triggered, this, &CPPIWindow::onToggleTrackHistory);
    connect(m_highlightAction, &QAction::triggered, this, &CPPIWindow::onHighlightTrack);
    
    // Style the context menu
    m_trackContextMenu->setStyleSheet(
        "QMenu {"
        "   background-color: #ffffff;"
        "   color: #1e293b;"
        "   border: 2px solid #e2e8f0;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "}"
        "QMenu::item {"
        "   padding: 8px 24px;"
        "   border-radius: 4px;"
        "   font-weight: 500;"
        "}"
        "QMenu::item:selected {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3b82f6, stop:1 #2563eb);"
        "   color: white;"
        "}"
        "QMenu::separator {"
        "   height: 1px;"
        "   background-color: #e2e8f0;"
        "   margin: 4px 16px;"
        "}"
    );
}

void CPPIWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_H:
        onMapHome();
        break;
    case Qt::Key_G:
        onToggleGrid();
        break;
    case Qt::Key_C:
        onToggleCompass();
        break;
    case Qt::Key_F:
        onZoomFitToScreen();
        break;
    case Qt::Key_L:
        onLoadNewMap();
        break;
    case Qt::Key_M:
        onExpandMap();
        break;
    case Qt::Key_T:
        onExpandTable();
        break;
    case Qt::Key_S:
        onSettings();
        break;
    }
    QMainWindow::keyPressEvent(event);
}

void CPPIWindow::contextMenuEvent(QContextMenuEvent *event)
{
    if (m_selectedTrackId != -1) {
        m_trackContextMenu->exec(event->globalPos());
    }
}

// Settings toolbar slots
void CPPIWindow::onLoadNewMap()
{
    QString filter = "Map Files (*.tif *.tiff *.png *.bmp *.jpg *.jpeg *.TIF *.TIFF *.PNG *.BMP *.JPG *.JPEG)";
    QString mapPath = QFileDialog::getOpenFileName(
        this,
        "Load New Map",
        QString(),
        filter
    );
    
    if (!mapPath.isEmpty()) {
        m_mapCanvas->importRasterMap(mapPath);
        m_statusLabel->setText("Map loaded: " + QFileInfo(mapPath).baseName());
        emit newMapRequested(mapPath);
        
        // Auto zoom fit after loading
        QTimer::singleShot(500, this, &CPPIWindow::onZoomFitToScreen);
    }
}

void CPPIWindow::onDisableMap()
{
    m_mapEnabled = !m_mapEnabled;
    m_disableMapBtn->setChecked(!m_mapEnabled);
    
    // Enable/disable map in the canvas
    m_mapCanvas->enableMap(m_mapEnabled);
    
    if (m_mapEnabled) {
        m_statusLabel->setText("Map enabled - Showing map layers with PPI overlay");
        m_disableMapBtn->setText("🚫 Disable Map");
    } else {
        m_statusLabel->setText("Map disabled - PPI only mode");
        m_disableMapBtn->setText("✅ Enable Map");
    }
    
    qDebug() << "Map enabled:" << m_mapEnabled;
}

void CPPIWindow::onZoomFitToScreen()
{
    m_mapCanvas->zoomToFullExtent();
    m_statusLabel->setText("Zoomed to fit screen");
    qDebug() << "Zoom fit to screen requested";
}

void CPPIWindow::onMapHome()
{
    m_mapCanvas->mapHome();
    m_statusLabel->setText("Map reset to home view");
    emit mapHomeRequested();
}

void CPPIWindow::onToggleGrid()
{
    m_gridVisible = !m_gridVisible;
    m_gridBtn->setChecked(m_gridVisible);
    m_statusLabel->setText(m_gridVisible ? "Grid enabled" : "Grid disabled");
    
    // TODO: Implement actual grid toggle
    qDebug() << "Grid visibility:" << m_gridVisible;
}

void CPPIWindow::onToggleCompass()
{
    m_compassVisible = !m_compassVisible;
    m_compassBtn->setChecked(m_compassVisible);
    m_statusLabel->setText(m_compassVisible ? "Compass enabled" : "Compass disabled");
    
    // TODO: Implement actual compass toggle
    qDebug() << "Compass visibility:" << m_compassVisible;
}

void CPPIWindow::onExpandMap()
{
    m_mapExpanded = !m_mapExpanded;
    m_expandMapBtn->setChecked(m_mapExpanded);
    
    if (m_mapExpanded) {
        // Collapse table, expand map
        if (!m_tableExpanded) {
            m_normalSplitterSizes = m_splitter->sizes();
        }
        m_splitter->setSizes({1000, 0});
        m_expandMapBtn->setText("📊 Show Table");
        m_statusLabel->setText("Map expanded - Table hidden");
        
        // Ensure table expand is unchecked
        m_tableExpanded = false;
        m_expandTableBtn->setChecked(false);
        m_expandTableBtn->setText("🗺️ Expand Table");
    } else {
        // Restore normal view
        m_splitter->setSizes(m_normalSplitterSizes);
        m_expandMapBtn->setText("🗺️ Expand Map");
        m_statusLabel->setText("Normal view restored");
    }
}

void CPPIWindow::onExpandTable()
{
    m_tableExpanded = !m_tableExpanded;
    m_expandTableBtn->setChecked(m_tableExpanded);
    
    if (m_tableExpanded) {
        // Collapse map, expand table
        if (!m_mapExpanded) {
            m_normalSplitterSizes = m_splitter->sizes();
        }
        m_splitter->setSizes({0, 1000});
        m_expandTableBtn->setText("🗺️ Show Map");
        m_statusLabel->setText("Table expanded - Map hidden");
        
        // Ensure map expand is unchecked
        m_mapExpanded = false;
        m_expandMapBtn->setChecked(false);
        m_expandMapBtn->setText("🗺️ Expand Map");
    } else {
        // Restore normal view
        m_splitter->setSizes(m_normalSplitterSizes);
        m_expandTableBtn->setText("📊 Expand Table");
        m_statusLabel->setText("Normal view restored");
    }
}

void CPPIWindow::onSettings()
{
    QMessageBox::information(this, "Settings", 
        "PPI Display Settings:\n\n"
        "• H: Map Home\n"
        "• G: Toggle Grid\n"
        "• C: Toggle Compass\n"
        "• F: Zoom Fit\n"
        "• L: Load Map\n"
        "• S: Settings\n\n"
        "Expand Controls:\n"
        "• Expand Map: Hide table, show only map\n"
        "• Expand Table: Hide map, show only table\n\n"
        "Right-click on tracks for context menu.\n"
        "History points limited to " + QString::number(m_maxHistoryPoints) + " per track.");
}

// Track context menu slots
void CPPIWindow::onFocusTrack()
{
    if (m_selectedTrackId == -1) return;
    
    // Find track and center map on it
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == m_selectedTrackId) {
            QgsPointXY centerPoint(track.lon, track.lat);
            m_mapCanvas->setCenter(centerPoint);
            m_mapCanvas->refresh();
            
            m_statusLabel->setText(QString("Focused on Track #%1").arg(m_selectedTrackId));
            break;
        }
    }
}

void CPPIWindow::onDeleteTrack()
{
    if (m_selectedTrackId == -1) return;
    
    int ret = QMessageBox::question(this, "Delete Track",
        QString("Are you sure you want to delete Track #%1?").arg(m_selectedTrackId),
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        // TODO: Implement track deletion
        m_statusLabel->setText(QString("Track #%1 deleted").arg(m_selectedTrackId));
        qDebug() << "Delete track requested:" << m_selectedTrackId;
    }
}

void CPPIWindow::onLoadTrackImage()
{
    if (m_selectedTrackId == -1) return;
    
    QString filter = "Image Files (*.png *.jpg *.jpeg *.bmp *.gif *.PNG *.JPG *.JPEG *.BMP *.GIF)";
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        QString("Load Image for Track #%1").arg(m_selectedTrackId),
        QString(),
        filter
    );
    
    if (!imagePath.isEmpty()) {
        // TODO: Implement track image loading
        m_statusLabel->setText(QString("Image loaded for Track #%1").arg(m_selectedTrackId));
        qDebug() << "Load image for track" << m_selectedTrackId << ":" << imagePath;
    }
}

void CPPIWindow::onToggleTrackHistory()
{
    if (m_selectedTrackId == -1) return;
    
    // TODO: Implement track history toggle with max 50 points
    m_statusLabel->setText(QString("History toggled for Track #%1 (Max %2 points)")
                          .arg(m_selectedTrackId).arg(m_maxHistoryPoints));
    qDebug() << "Toggle history for track" << m_selectedTrackId;
}

void CPPIWindow::onHighlightTrack()
{
    if (m_selectedTrackId == -1) return;
    
    // TODO: Implement track highlighting and following
    m_statusLabel->setText(QString("Track #%1 highlighted and following").arg(m_selectedTrackId));
    qDebug() << "Highlight and follow track" << m_selectedTrackId;
}

// Track table interaction slots
void CPPIWindow::onTrackSelected(int trackId)
{
    m_selectedTrackId = trackId;
    emit trackSelected(trackId);
    
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == trackId) {
            statusBar()->showMessage(
                QString("Track #%1 | Range: %2 km | Heading: %3° | Pos: %4°, %5°")
                .arg(track.nTrkId)
                .arg(track.range / 1000.0, 0, 'f', 2)
                .arg(track.heading, 0, 'f', 1)
                .arg(track.lat, 0, 'f', 4)
                .arg(track.lon, 0, 'f', 4)
            );
            break;
        }
    }
}

void CPPIWindow::onTrackDoubleClicked(int trackId)
{
    m_selectedTrackId = trackId;
    emit trackDoubleClicked(trackId);
    
    // Auto focus on double click
    onFocusTrack();
}

void CPPIWindow::onTrackRightClicked(int trackId, const QPoint& globalPos)
{
    m_selectedTrackId = trackId;
    m_trackContextMenu->exec(globalPos);
}

void CPPIWindow::updateStatusBar()
{
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    QString statusMsg = QString("🎯 Active Tracks: %1 | Grid: %2 | Compass: %3 | Map: %4")
        .arg(tracks.count())
        .arg(m_gridVisible ? "ON" : "OFF")
        .arg(m_compassVisible ? "ON" : "OFF")
        .arg(m_mapEnabled ? "ON" : "OFF");
    
    statusBar()->showMessage(statusMsg);
}

void CPPIWindow::saveSettings()
{
    m_settings->setValue("geometry", saveGeometry());
    m_settings->setValue("windowState", saveState());
    m_settings->setValue("gridVisible", m_gridVisible);
    m_settings->setValue("compassVisible", m_compassVisible);
    m_settings->setValue("mapEnabled", m_mapEnabled);
    m_settings->setValue("mapExpanded", m_mapExpanded);
    m_settings->setValue("tableExpanded", m_tableExpanded);
    m_settings->setValue("maxHistoryPoints", m_maxHistoryPoints);
    
    // Save splitter sizes
    QByteArray splitterState = m_splitter->saveState();
    m_settings->setValue("splitterState", splitterState);
}

void CPPIWindow::loadSettings()
{
    restoreGeometry(m_settings->value("geometry").toByteArray());
    restoreState(m_settings->value("windowState").toByteArray());
    
    m_gridVisible = m_settings->value("gridVisible", true).toBool();
    m_compassVisible = m_settings->value("compassVisible", true).toBool();
    m_mapEnabled = m_settings->value("mapEnabled", true).toBool();
    m_mapExpanded = m_settings->value("mapExpanded", false).toBool();
    m_tableExpanded = m_settings->value("tableExpanded", false).toBool();
    m_maxHistoryPoints = m_settings->value("maxHistoryPoints", 50).toInt();
    
    // Restore splitter state
    QByteArray splitterState = m_settings->value("splitterState").toByteArray();
    if (!splitterState.isEmpty()) {
        m_splitter->restoreState(splitterState);
        m_normalSplitterSizes = m_splitter->sizes();
    }
    
    // Update UI state
    m_gridBtn->setChecked(m_gridVisible);
    m_compassBtn->setChecked(m_compassVisible);
    m_disableMapBtn->setChecked(!m_mapEnabled);
    m_disableMapBtn->setText(m_mapEnabled ? "🚫 Disable Map" : "✅ Enable Map");
    m_expandMapBtn->setChecked(m_mapExpanded);
    m_expandTableBtn->setChecked(m_tableExpanded);
    
    // Apply expand state
    if (m_mapExpanded) {
        m_expandMapBtn->setText("📊 Show Table");
    }
    if (m_tableExpanded) {
        m_expandTableBtn->setText("🗺️ Show Map");
    }
}
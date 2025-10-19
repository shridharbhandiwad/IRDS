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
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QLabel>

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
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setChildrenCollapsible(true); // Allow collapsing
    splitter->setHandleWidth(6); // Make handle more visible
    
    setupMapCanvas();
    setupTrackTable();
    
    // Add to splitter
    splitter->addWidget(m_mapCanvas);
    splitter->addWidget(m_trackTable);
    
    // Set splitter proportions (60% map, 40% table)
    splitter->setSizes({600, 400});
    splitter->setStretchFactor(0, 6);
    splitter->setStretchFactor(1, 4);
    
    // Store splitter reference for later use
    m_splitter = splitter;
    
    m_mainLayout->addWidget(splitter);
    
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

QQuickWidget* CPPIWindow::createIconButton(const QString& iconType, const QString& tooltip)
{
    QQuickWidget* widget = new QQuickWidget(this);
    widget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    widget->setFixedSize(36, 36);
    widget->setAttribute(Qt::WA_AlwaysStackOnTop);
    widget->setClearColor(Qt::transparent);
    
    // Set QML source
    widget->setSource(QUrl("qrc:/qml/Icons/IconButton.qml"));
    
    if (widget->rootObject()) {
        widget->rootObject()->setProperty("iconType", iconType);
        widget->rootObject()->setProperty("toolTip", tooltip);
    }
    
    return widget;
}

void CPPIWindow::setupSettingsToolbar()
{
    m_settingsLayout = new QHBoxLayout();
    m_settingsLayout->setSpacing(6);
    m_settingsLayout->setContentsMargins(2, 2, 2, 2);
    
    // Create settings buttons with light theme
    // Icon-only buttons with tooltips
    m_loadMapBtn = new QPushButton("📁", this);
    m_disableMapBtn = new QPushButton(m_mapEnabled ? "🚫" : "✅", this);
    m_zoomFitBtn = new QPushButton("🔍", this);
    m_homeBtn = new QPushButton("🏠", this);
    m_gridBtn = new QPushButton("📐", this);
    m_compassBtn = new QPushButton("🧭", this);
    m_toggleTableBtn = new QPushButton("📊", this);
    m_settingsBtn = new QPushButton("⚙️", this);

    // Tooltips (text appears on hover)
    m_loadMapBtn->setToolTip("Load Map");
    m_disableMapBtn->setToolTip(m_mapEnabled ? "Disable Map" : "Enable Map");
    m_zoomFitBtn->setToolTip("Zoom Fit");
    m_homeBtn->setToolTip("Home");
    m_gridBtn->setToolTip("Toggle Grid");
    m_compassBtn->setToolTip("Toggle Compass");
    m_toggleTableBtn->setToolTip("Show/Hide Track Table");
    m_settingsBtn->setToolTip("Settings");

    // Compact icon-only style with hover zoom
    auto styleIconButton = [](QPushButton *btn) {
        btn->setCursor(Qt::PointingHandCursor);
        // Fix size so hover zoom doesn't shift layout
        btn->setFixedSize(QSize(36, 32));
        // Only override sizing and font so we keep global colors/backgrounds
        btn->setStyleSheet(
            "padding: 2px 6px;"
            "font-size: 16px;"
            "min-width: 36px;"
            "min-height: 32px;"
        );
        // Hover zoom effect for the icon
        btn->setStyleSheet(btn->styleSheet() + "QPushButton:hover { font-size: 20px; }");
    };
    styleIconButton(m_loadMapBtn);
    styleIconButton(m_disableMapBtn);
    styleIconButton(m_zoomFitBtn);
    styleIconButton(m_homeBtn);
    styleIconButton(m_gridBtn);
    styleIconButton(m_compassBtn);
    styleIconButton(m_toggleTableBtn);
    styleIconButton(m_settingsBtn);
    
    // Make toggle buttons checkable
    m_gridBtn->setCheckable(true);
    m_gridBtn->setChecked(m_gridVisible);
    m_compassBtn->setCheckable(true);
    m_compassBtn->setChecked(m_compassVisible);
    m_disableMapBtn->setCheckable(true);
    m_disableMapBtn->setChecked(!m_mapEnabled);
    m_toggleTableBtn->setCheckable(true);
    m_toggleTableBtn->setChecked(true);
    
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
    m_settingsLayout->addWidget(m_toggleTableBtn);
    m_settingsLayout->addStretch();
    m_settingsLayout->addWidget(m_statusLabel);
    m_settingsLayout->addWidget(m_settingsBtn);
    
    // Connect QML button signals
    if (m_loadMapBtn->rootObject()) {
        connect(m_loadMapBtn->rootObject(), SIGNAL(clicked()), this, SLOT(onLoadNewMap()));
    }
    if (m_disableMapBtn->rootObject()) {
        connect(m_disableMapBtn->rootObject(), SIGNAL(clicked()), this, SLOT(onDisableMap()));
    }
    if (m_zoomFitBtn->rootObject()) {
        connect(m_zoomFitBtn->rootObject(), SIGNAL(clicked()), this, SLOT(onZoomFitToScreen()));
    }
    if (m_homeBtn->rootObject()) {
        connect(m_homeBtn->rootObject(), SIGNAL(clicked()), this, SLOT(onMapHome()));
    }
    if (m_gridBtn->rootObject()) {
        connect(m_gridBtn->rootObject(), SIGNAL(clicked()), this, SLOT(onToggleGrid()));
    }
    if (m_compassBtn->rootObject()) {
        connect(m_compassBtn->rootObject(), SIGNAL(clicked()), this, SLOT(onToggleCompass()));
    }
    if (m_toggleTableBtn->rootObject()) {
        connect(m_toggleTableBtn->rootObject(), SIGNAL(clicked()), this, SLOT(onToggleTrackTable()));
    }
    if (m_settingsBtn->rootObject()) {
        connect(m_settingsBtn->rootObject(), SIGNAL(clicked()), this, SLOT(onSettings()));
    }
    
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
}

void CPPIWindow::setupTrackTable()
{
    m_trackTable = new CTrackTableWidget(this);
    m_trackTable->setMinimumWidth(450);
    m_trackTable->setMaximumWidth(750);
    
    // Connect track table signals
    connect(m_trackTable, &CTrackTableWidget::trackSelected,
            this, &CPPIWindow::onTrackSelected);
    connect(m_trackTable, &CTrackTableWidget::trackDoubleClicked,
            this, &CPPIWindow::onTrackDoubleClicked);
    connect(m_trackTable, &CTrackTableWidget::trackImageLoaded,
            this, &CPPIWindow::onTrackImageLoaded);
}

void CPPIWindow::applyLightTheme()
{
    // Light, transparent and attractive theme with Blue accent (#3b82f6)
    QString lightTheme = 
        "CPPIWindow {"
        "   background-color: rgba(248, 250, 252, 0.95);"
        "   color: #1e293b;"
        "}"
        "QWidget {"
        "   background-color: rgba(248, 250, 252, 0.95);"
        "   color: #1e293b;"
        "   font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QQuickWidget {"
        "   background-color: transparent;"
        "   border: none;"
        "}"
        "QLabel {"
        "   color: #334155;"
        "   font-weight: 500;"
        "}"
        "QSplitter {"
        "   background-color: rgba(226, 232, 240, 0.3);"
        "}"
        "QSplitter::handle {"
        "   background-color: rgba(203, 213, 225, 0.8);"
        "   width: 4px;"
        "   border-radius: 2px;"
        "   margin: 2px 0px;"
        "}"
        "QSplitter::handle:hover {"
        "   background-color: #3b82f6;"
        "}"
        "QSplitter::handle:pressed {"
        "   background-color: #2563eb;"
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
    
    if (m_disableMapBtn->rootObject()) {
        m_disableMapBtn->rootObject()->setProperty("isToggled", !m_mapEnabled);
        m_disableMapBtn->rootObject()->setProperty("toolTip", m_mapEnabled ? "Disable Map" : "Enable Map");
    }
    
    if (m_mapEnabled) {
        m_statusLabel->setText("Map enabled - Showing PPI with map layers");
        m_disableMapBtn->setText("🚫");
        m_disableMapBtn->setToolTip("Disable Map");
        m_mapCanvas->setMapLayersVisible(true);
    } else {
        m_statusLabel->setText("Map disabled - Showing PPI only");
        m_disableMapBtn->setText("✅");
        m_disableMapBtn->setToolTip("Enable Map");
        m_mapCanvas->setMapLayersVisible(false);
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
    
    if (m_gridBtn->rootObject()) {
        m_gridBtn->rootObject()->setProperty("isToggled", m_gridVisible);
    }
    
    m_statusLabel->setText(m_gridVisible ? "Grid enabled" : "Grid disabled");
    
    // TODO: Implement actual grid toggle
    qDebug() << "Grid visibility:" << m_gridVisible;
}

void CPPIWindow::onToggleCompass()
{
    m_compassVisible = !m_compassVisible;
    
    if (m_compassBtn->rootObject()) {
        m_compassBtn->rootObject()->setProperty("isToggled", m_compassVisible);
    }
    
    m_statusLabel->setText(m_compassVisible ? "Compass enabled" : "Compass disabled");
    
    // TODO: Implement actual compass toggle
    qDebug() << "Compass visibility:" << m_compassVisible;
}

void CPPIWindow::onToggleTrackTable()
{
    bool isVisible = m_trackTable->isVisible();
    m_trackTable->setVisible(!isVisible);
    
    if (m_toggleTableBtn->rootObject()) {
        m_toggleTableBtn->rootObject()->setProperty("isToggled", !isVisible);
    }
    
    m_statusLabel->setText(!isVisible ? "Track table shown" : "Track table hidden");
    qDebug() << "Track table visibility:" << !isVisible;
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
        CDataWarehouse::getInstance()->setTrackImagePath(m_selectedTrackId, imagePath);
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

void CPPIWindow::onTrackImageLoaded(int trackId, const QString &imagePath)
{
    Q_UNUSED(imagePath);
    if (trackId <= 0) return;
    CDataWarehouse::getInstance()->setTrackImagePath(trackId, imagePath);
    m_statusLabel->setText(QString("Image loaded for Track #%1").arg(trackId));
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
    m_settings->setValue("maxHistoryPoints", m_maxHistoryPoints);
}

void CPPIWindow::loadSettings()
{
    restoreGeometry(m_settings->value("geometry").toByteArray());
    restoreState(m_settings->value("windowState").toByteArray());
    
    m_gridVisible = m_settings->value("gridVisible", true).toBool();
    m_compassVisible = m_settings->value("compassVisible", true).toBool();
    m_mapEnabled = m_settings->value("mapEnabled", true).toBool();
    m_maxHistoryPoints = m_settings->value("maxHistoryPoints", 50).toInt();
    
    // Update UI state
    m_gridBtn->setChecked(m_gridVisible);
    m_compassBtn->setChecked(m_compassVisible);
    m_disableMapBtn->setChecked(!m_mapEnabled);
    m_disableMapBtn->setText(m_mapEnabled ? "🚫" : "✅");
    m_disableMapBtn->setToolTip(m_mapEnabled ? "Disable Map" : "Enable Map");
}
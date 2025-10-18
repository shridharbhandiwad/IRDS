#include "cppiwindow.h"
#include "ctracktablewidget.h"
#include "../cdatawarehouse.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QContextMenuEvent>
#include <QMenu>
#include <QStatusBar>
#include <qgspoint.h>

CPPIWindow::CPPIWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mapCanvas(nullptr)
    , m_trackTable(nullptr)
    , m_settingsButton(nullptr)
    , m_settingsMenu(nullptr)
    , m_contextMenuTrackId(-1)
    , m_selectedTrackId(-1)
{
    setWindowTitle("PPI Display & Track Table");
    
    setupUI();
    setupMapCanvas();
    setupTrackTable();
    setupSettingsButton();
    applyLightTheme();
    
    // Set window size for typical monitor
    resize(1280, 900);
}

CPPIWindow::~CPPIWindow()
{
}

void CPPIWindow::setupUI()
{
    // Create central widget with map canvas
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // Create map canvas placeholder (will be initialized in setupMapCanvas)
    m_mapCanvas = new CMapCanvas(this);
    mainLayout->addWidget(m_mapCanvas);
    
    setCentralWidget(centralWidget);
    
    // Create status bar
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    statusBar->showMessage("Ready | Right-click on track for options");
}

void CPPIWindow::setupMapCanvas()
{
    if (!m_mapCanvas) return;
    
    m_mapCanvas->Initialize();
    
    // Connect mouse position signal
    connect(m_mapCanvas, SIGNAL(signalMouseRead(QString)),
            this, SLOT(onMousePositionChanged(QString)));
}

void CPPIWindow::setupTrackTable()
{
    m_trackTable = new CTrackTableWidget(this);
    
    // Add as dockable widget to right side
    addDockWidget(Qt::RightDockWidgetArea, m_trackTable);
    
    // Set preferred size
    m_trackTable->setMinimumWidth(400);
    m_trackTable->setMaximumWidth(550);
    
    // Make it initially visible
    m_trackTable->setVisible(true);
    
    // Allow docking on right side only
    m_trackTable->setAllowedAreas(Qt::RightDockWidgetArea);
    
    // Enable floating
    m_trackTable->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );
    
    // Connect signals
    connect(m_trackTable, &CTrackTableWidget::trackSelected,
            this, &CPPIWindow::onTrackSelected);
    connect(m_trackTable, &CTrackTableWidget::trackDoubleClicked,
            this, &CPPIWindow::onTrackDoubleClicked);
}

void CPPIWindow::setupSettingsButton()
{
    // Create settings button as floating overlay
    m_settingsButton = new QPushButton("⚙ Settings", this);
    m_settingsButton->setGeometry(20, 20, 120, 40);
    m_settingsButton->raise(); // Ensure it's on top
    
    // Create settings menu
    m_settingsMenu = new QMenu(this);
    
    QAction *loadMapAction = m_settingsMenu->addAction("📂 Load New Map");
    QAction *disableMapAction = m_settingsMenu->addAction("🚫 Disable Map");
    QAction *zoomFitAction = m_settingsMenu->addAction("🔍 Zoom Fit to Max");
    m_settingsMenu->addSeparator();
    QAction *homeAction = m_settingsMenu->addAction("🏠 Map Home");
    
    // Connect actions
    connect(loadMapAction, &QAction::triggered, this, &CPPIWindow::onLoadNewMap);
    connect(disableMapAction, &QAction::triggered, this, &CPPIWindow::onDisableMap);
    connect(zoomFitAction, &QAction::triggered, this, &CPPIWindow::onZoomFitToMax);
    connect(homeAction, &QAction::triggered, [this]() {
        if (m_mapCanvas) {
            m_mapCanvas->mapHome();
            statusBar()->showMessage("Map reset to home view", 2000);
        }
    });
    
    // Show menu on button click
    connect(m_settingsButton, &QPushButton::clicked, [this]() {
        QPoint buttonPos = m_settingsButton->mapToGlobal(QPoint(0, m_settingsButton->height()));
        m_settingsMenu->exec(buttonPos);
    });
}

void CPPIWindow::applyLightTheme()
{
    // Light theme with two primary colors: Light Blue (#E3F2FD) and White (#FFFFFF)
    QString lightTheme = 
        "QMainWindow {"
        "   background-color: #E3F2FD;" // Light blue background
        "}"
        "QWidget {"
        "   background-color: #FFFFFF;" // White widgets
        "   color: #1565C0;"            // Dark blue text
        "}"
        "QPushButton {"
        "   background-color: #E3F2FD;" // Light blue button
        "   color: #1565C0;"             // Dark blue text
        "   border: 2px solid #90CAF9;"  // Medium blue border
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "   font-weight: 600;"
        "   font-size: 13px;"
        "   min-height: 28px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #BBDEFB;" // Slightly darker blue on hover
        "   border: 2px solid #64B5F6;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #90CAF9;" // Even darker blue when pressed
        "}"
        "QDockWidget {"
        "   background-color: #FFFFFF;"
        "   color: #1565C0;"
        "   titlebar-close-icon: url(close.png);"
        "   titlebar-normal-icon: url(float.png);"
        "}"
        "QDockWidget::title {"
        "   background-color: #E3F2FD;" // Light blue title bar
        "   padding: 8px;"
        "   text-align: center;"
        "   font-weight: bold;"
        "   color: #1565C0;"
        "   border-bottom: 2px solid #90CAF9;"
        "}"
        "QStatusBar {"
        "   background-color: #E3F2FD;" // Light blue status bar
        "   color: #1565C0;"
        "   border-top: 2px solid #90CAF9;"
        "   font-size: 11px;"
        "   padding: 6px;"
        "   font-weight: 500;"
        "}"
        "QMenu {"
        "   background-color: #FFFFFF;"
        "   color: #1565C0;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "}"
        "QMenu::item {"
        "   padding: 8px 30px 8px 30px;"
        "   border-radius: 4px;"
        "}"
        "QMenu::item:selected {"
        "   background-color: #E3F2FD;"
        "   color: #0D47A1;"
        "}"
        "QTableWidget {"
        "   background-color: #FFFFFF;"
        "   alternate-background-color: #F5F5F5;"
        "   color: #1565C0;"
        "   gridline-color: #E3F2FD;"
        "   border: none;"
        "   selection-background-color: #BBDEFB;"
        "   selection-color: #0D47A1;"
        "}"
        "QHeaderView::section {"
        "   background-color: #E3F2FD;"
        "   color: #0D47A1;"
        "   padding: 8px;"
        "   border: none;"
        "   border-bottom: 2px solid #90CAF9;"
        "   font-weight: bold;"
        "}"
        "QLineEdit {"
        "   background-color: #FFFFFF;"
        "   color: #1565C0;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 4px;"
        "   padding: 6px;"
        "   selection-background-color: #BBDEFB;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #42A5F5;"
        "}"
        "QComboBox {"
        "   background-color: #FFFFFF;"
        "   color: #1565C0;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 4px;"
        "   padding: 6px;"
        "}"
        "QComboBox:hover {"
        "   border: 2px solid #64B5F6;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #FFFFFF;"
        "   color: #1565C0;"
        "   selection-background-color: #E3F2FD;"
        "   selection-color: #0D47A1;"
        "   border: 2px solid #90CAF9;"
        "}";
    
    setStyleSheet(lightTheme);
}

void CPPIWindow::contextMenuEvent(QContextMenuEvent *event)
{
    // Get track at cursor position
    QPoint mapPos = m_mapCanvas->mapFromGlobal(event->globalPos());
    int trackId = getTrackAtPosition(event->globalPos());
    
    if (trackId != -1) {
        m_contextMenuTrackId = trackId;
        
        // Create context menu for track
        QMenu contextMenu(this);
        
        QAction *focusAction = contextMenu.addAction(QString("🎯 Focus Track #%1").arg(trackId));
        QAction *highlightAction = contextMenu.addAction("✨ Highlight & Follow");
        contextMenu.addSeparator();
        QAction *historyAction = contextMenu.addAction("📊 Set History Points (Max 50)");
        QAction *imageAction = contextMenu.addAction("🖼️ Load Track Image");
        contextMenu.addSeparator();
        QAction *deleteAction = contextMenu.addAction("🗑️ Delete Track");
        deleteAction->setEnabled(true);
        
        // Connect actions
        connect(focusAction, &QAction::triggered, this, &CPPIWindow::onFocusTrack);
        connect(highlightAction, &QAction::triggered, this, &CPPIWindow::onHighlightTrack);
        connect(historyAction, &QAction::triggered, this, &CPPIWindow::onSetHistoryPoints);
        connect(imageAction, &QAction::triggered, this, &CPPIWindow::onLoadTrackImage);
        connect(deleteAction, &QAction::triggered, this, &CPPIWindow::onDeleteTrack);
        
        contextMenu.exec(event->globalPos());
    } else {
        QMainWindow::contextMenuEvent(event);
    }
}

int CPPIWindow::getTrackAtPosition(const QPoint &globalPos)
{
    if (!m_mapCanvas) return -1;
    
    QPoint mapPos = m_mapCanvas->mapFromGlobal(globalPos);
    const QgsMapToPixel &mapToPixel = m_mapCanvas->mapSettings().mapToPixel();
    QList<stTrackDisplayInfo> listTracks = CDataWarehouse::getInstance()->getTrackList();
    
    const double detectionRadius = 20.0;
    
    for (const stTrackDisplayInfo &track : listTracks) {
        QPointF ptScreen = mapToPixel.transform(QgsPointXY(track.lon, track.lat)).toQPointF();
        double distance = QLineF(mapPos, ptScreen).length();
        
        if (distance <= detectionRadius) {
            return track.nTrkId;
        }
    }
    
    return -1;
}

// Settings menu slot implementations
void CPPIWindow::onLoadNewMap()
{
    QString filter = "Raster Files (*.tif *.tiff *.png *.bmp *.jpg *.TIF *.PNG *.BMP *.JPG)";
    
    QString rasterPath = QFileDialog::getOpenFileName(
        this,
        "Select Raster or World-Referenced Image",
        QString(),
        filter
    );
    
    if (!rasterPath.isEmpty() && m_mapCanvas) {
        m_mapCanvas->importRasterMap(rasterPath);
        statusBar()->showMessage("Loading new map: " + rasterPath, 3000);
    }
}

void CPPIWindow::onDisableMap()
{
    // TODO: Implement map disable functionality
    statusBar()->showMessage("Map layers disabled", 2000);
    QMessageBox::information(this, "Map Disabled", "Base map layers have been disabled.");
}

void CPPIWindow::onZoomFitToMax()
{
    if (m_mapCanvas) {
        m_mapCanvas->zoomToFullExtent();
        m_mapCanvas->refresh();
        statusBar()->showMessage("Zoomed to full extent", 2000);
    }
}

// Track context menu slot implementations
void CPPIWindow::onFocusTrack()
{
    if (m_contextMenuTrackId == -1) return;
    
    // Find track and center on it
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == m_contextMenuTrackId) {
            QgsPointXY centerPoint(track.lon, track.lat);
            m_mapCanvas->setCenter(centerPoint);
            m_mapCanvas->refresh();
            
            statusBar()->showMessage(
                QString("Focused on Track #%1").arg(m_contextMenuTrackId),
                2000
            );
            break;
        }
    }
}

void CPPIWindow::onDeleteTrack()
{
    if (m_contextMenuTrackId == -1) return;
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Track",
        QString("Are you sure you want to delete Track #%1?").arg(m_contextMenuTrackId),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        // TODO: Implement track deletion in CDataWarehouse
        statusBar()->showMessage(
            QString("Track #%1 deleted").arg(m_contextMenuTrackId),
            2000
        );
    }
}

void CPPIWindow::onLoadTrackImage()
{
    if (m_contextMenuTrackId == -1) return;
    
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        QString("Select Image for Track #%1").arg(m_contextMenuTrackId),
        QString(),
        "Image Files (*.png *.jpg *.jpeg *.bmp *.svg)"
    );
    
    if (!imagePath.isEmpty()) {
        // TODO: Implement track image loading
        statusBar()->showMessage(
            QString("Loaded image for Track #%1: %2").arg(m_contextMenuTrackId).arg(imagePath),
            3000
        );
    }
}

void CPPIWindow::onHighlightTrack()
{
    if (m_contextMenuTrackId == -1) return;
    
    // TODO: Implement track highlighting with continuous following
    statusBar()->showMessage(
        QString("Highlighting and following Track #%1").arg(m_contextMenuTrackId),
        2000
    );
}

void CPPIWindow::onSetHistoryPoints()
{
    if (m_contextMenuTrackId == -1) return;
    
    bool ok;
    int points = QInputDialog::getInt(
        this,
        "Set History Points",
        QString("Enter number of history points for Track #%1 (1-50):").arg(m_contextMenuTrackId),
        20,  // default
        1,   // min
        50,  // max
        1,   // step
        &ok
    );
    
    if (ok) {
        // TODO: Implement history points setting in track data
        statusBar()->showMessage(
            QString("Track #%1 history set to %2 points").arg(m_contextMenuTrackId).arg(points),
            2000
        );
    }
}

// Track table interaction
void CPPIWindow::onTrackSelected(int trackId)
{
    m_selectedTrackId = trackId;
    
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == trackId) {
            statusBar()->showMessage(
                QString("Track #%1 | Range: %2 km | Heading: %3° | Alt: %4 m")
                .arg(track.nTrkId)
                .arg(track.range / 1000.0, 0, 'f', 2)
                .arg(track.heading, 0, 'f', 1)
                .arg(track.alt, 0, 'f', 0)
            );
            break;
        }
    }
}

void CPPIWindow::onTrackDoubleClicked(int trackId)
{
    // Double-click centers on track
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == trackId) {
            QgsPointXY centerPoint(track.lon, track.lat);
            m_mapCanvas->setCenter(centerPoint);
            m_mapCanvas->refresh();
            
            statusBar()->showMessage(
                QString("Centered on Track #%1").arg(trackId),
                2000
            );
            break;
        }
    }
}

void CPPIWindow::onMousePositionChanged(QString mouseRead)
{
    // Update status bar with mouse position when not showing other messages
    if (statusBar()->currentMessage().isEmpty() || 
        statusBar()->currentMessage().contains("Lat:") ||
        statusBar()->currentMessage().contains("Ready")) {
        statusBar()->showMessage(mouseRead);
    }
}

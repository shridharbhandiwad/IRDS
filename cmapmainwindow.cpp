//#include "cmapmainwindow.h"
//#include "ui_cmapmainwindow.h"
//#include "cdatawarehouse.h"
//#include <QFileDialog>

//CMapMainWindow::CMapMainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::CMapMainWindow)
//{
//    ui->setupUi(this);
//    ui->widgetMapCanvas->Initialize();
//    setWindowTitle("Radar Display");

//    ui->tableWidget->setRowCount(100);
//    for ( int i = 0; i < ui->tableWidget->rowCount(); i++ ) {
//        for ( int j = 0; j < ui->tableWidget->columnCount(); j++ ) {
//            QTableWidgetItem *item = new QTableWidgetItem("");
//            item->setForeground(QBrush(Qt::white));
//            item->setFont(QFont("century",12,80,false));
//            item->setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(i,j,item);
//        }
//    }

//    connect(&_m_updateTimer, &QTimer::timeout, this, [this]() {
//           updateTrackTable();  // Trigger repaint
//       });
//    _m_updateTimer.start(1000);


//    ui->widget_TextualControl->setVisible(false);
//    connect(ui->widgetMapCanvas, SIGNAL(signalMouseRead(QString)), this, SLOT(slotMouseRead(QString)));
//}

//CMapMainWindow::~CMapMainWindow()
//{
//    delete ui;
//}

//void CMapMainWindow::keyPressEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_F:
//        ui->widget_TextualControl->setVisible(!ui->widget_TextualControl->isVisible());
//        break;
//    case Qt::Key_H:
//        ui->widgetMapCanvas->mapHome();;;
//        break;

//   }
//    QMainWindow::keyPressEvent(event);
//}

//void CMapMainWindow::slotMouseRead( QString mouseRead ) {
//    ui->statusBar->showMessage(mouseRead);
//}

//void CMapMainWindow::on_pushButton_MapHome_clicked()
//{
//    ui->widgetMapCanvas->mapHome();
//}

//void CMapMainWindow::on_pushButton_OpenMaps_clicked()
//{
//    QString filter = "Raster Files (*.tif *.tiff *.png *.bmp *.jpg *.TIF *.tiff *.PNG *.BMP *.JPG)";

//    QString rasterPath = QFileDialog::getOpenFileName(
//                this,
//                "Select Raster or World-Referenced Image",
//                QString(),
//                filter
//                );

//    if (rasterPath.isEmpty())
//        return;

//    //ui->widgetMapCanvas->openRasterMap(rasterPath);
//    ui->widgetMapCanvas->importRasterMap(rasterPath);
//}

//void CMapMainWindow::on_pushButton_FLUSH_clicked()
//{

//}

//void CMapMainWindow::on_pushButton_EXIT_clicked()
//{
//    exit(0);
//}


//void CMapMainWindow::updateTrackTable() {
//    QList<stTrackDisplayInfo> listTracks = CDataWarehouse::getInstance()->getTrackList();

//    //ui->tableWidget->clear();
//    int row = 0;
//    for (const stTrackDisplayInfo &track : listTracks) {
//        ui->tableWidget->item(row, 0)->setText(QString::number(track.nTrkId));
//        ui->tableWidget->item(row, 1)->setText(QString::number(track.range, 'f', 0));
//        ui->tableWidget->item(row, 2)->setText(QString::number(track.azimuth, 'f', 2));
//        ui->tableWidget->item(row, 3)->setText(QString::number(track.elevation, 'f', 1));
//        ui->tableWidget->item(row, 4)->setText(QString::number(track.heading, 'f', 1));
//        ui->tableWidget->item(row, 5)->setText(QString::number(track.velocity, 'f', 1));
//        ui->tableWidget->item(row, 6)->setText(QString::number(track.snr, 'f', 1));
//        ++row;
//    }
//}



//#include "cmapmainwindow.h"
//#include "ui_cmapmainwindow.h"
//#include "cdatawarehouse.h"
//#include "MapDisplay/ctracktablewidget.h"
//#include <QFileDialog>
//#include <QDebug>
//#include <qgspoint.h>

//CMapMainWindow::CMapMainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::CMapMainWindow)
//{
//    ui->setupUi(this);
//    ui->widgetMapCanvas->Initialize();
//    setWindowTitle("Radar Display");

//    // Setup rich dockable track table
//    setupTrackTable();

//    // Hide the old table widget if it exists in UI
//    if (ui->tableWidget) {
//        ui->tableWidget->setVisible(false);
//    }

//    ui->widget_TextualControl->setVisible(false);
//    connect(ui->widgetMapCanvas, SIGNAL(signalMouseRead(QString)), this, SLOT(slotMouseRead(QString)));

//    // Apply modern dark theme to main window
//    applyModernTheme();

//    // Start update timer for status bar
//    connect(&_m_updateTimer, &QTimer::timeout, this, &CMapMainWindow::updateTrackTable);
//    _m_updateTimer.start(1000);
//}

//CMapMainWindow::~CMapMainWindow()
//{
//    delete ui;
//}

//void CMapMainWindow::setupTrackTable()
//{
//    m_trackTable = new CTrackTableWidget(this);

//    // Add as dockable widget to right side
//    addDockWidget(Qt::RightDockWidgetArea, m_trackTable);

//    // Make it initially visible
//    m_trackTable->setVisible(true);

//    // Allow docking on all sides
//    m_trackTable->setAllowedAreas(Qt::AllDockWidgetAreas);

//    // Enable floating
//    m_trackTable->setFeatures(
//        QDockWidget::DockWidgetClosable |
//        QDockWidget::DockWidgetMovable |
//        QDockWidget::DockWidgetFloatable
//    );

//    // Connect signals for track interaction
//    connect(m_trackTable, &CTrackTableWidget::trackSelected,
//            this, &CMapMainWindow::onTrackSelected);
//    connect(m_trackTable, &CTrackTableWidget::trackDoubleClicked,
//            this, &CMapMainWindow::onTrackDoubleClicked);
//}

//void CMapMainWindow::applyModernTheme()
//{
//    // Modern dark theme for the entire application
//    setStyleSheet(
//        "QMainWindow {"
//        "   background-color: #1a202c;"
//        "}"
//        "QWidget {"
//        "   background-color: #1a202c;"
//        "   color: #ffffff;"
//        "}"
//        "QPushButton {"
//        "   background-color: #667eea;"
//        "   color: white;"
//        "   border: none;"
//        "   border-radius: 8px;"
//        "   padding: 10px 16px;"
//        "   font-weight: bold;"
//        "   font-size: 12px;"
//        "   min-height: 32px;"
//        "}"
//        "QPushButton:hover {"
//        "   background-color: #5568d3;"
//        "}"
//        "QPushButton:pressed {"
//        "   background-color: #4c51bf;"
//        "}"
//        "QPushButton:disabled {"
//        "   background-color: #4a5568;"
//        "   color: #a0aec0;"
//        "}"
//        "QStatusBar {"
//        "   background-color: #2d3748;"
//        "   color: #ffffff;"
//        "   border-top: 2px solid #667eea;"
//        "   font-size: 11px;"
//        "   padding: 4px;"
//        "}"
//        "QMenuBar {"
//        "   background-color: #2d3748;"
//        "   color: #ffffff;"
//        "   border-bottom: 2px solid #667eea;"
//        "}"
//        "QMenuBar::item {"
//        "   background-color: transparent;"
//        "   padding: 8px 12px;"
//        "}"
//        "QMenuBar::item:selected {"
//        "   background-color: #667eea;"
//        "}"
//        "QMenu {"
//        "   background-color: #2d3748;"
//        "   color: #ffffff;"
//        "   border: 2px solid #4a5568;"
//        "}"
//        "QMenu::item:selected {"
//        "   background-color: #667eea;"
//        "}"
//        "QToolBar {"
//        "   background-color: #2d3748;"
//        "   border: none;"
//        "   spacing: 8px;"
//        "   padding: 4px;"
//        "}"
//        "QGroupBox {"
//        "   background-color: #2d3748;"
//        "   border: 2px solid #4a5568;"
//        "   border-radius: 8px;"
//        "   margin-top: 12px;"
//        "   padding-top: 12px;"
//        "   font-weight: bold;"
//        "   color: #ffffff;"
//        "}"
//        "QGroupBox::title {"
//        "   subcontrol-origin: margin;"
//        "   subcontrol-position: top left;"
//        "   padding: 4px 8px;"
//        "   background-color: #667eea;"
//        "   border-radius: 4px;"
//        "   color: white;"
//        "}"
//    );
//}

//void CMapMainWindow::keyPressEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_F:
//        ui->widget_TextualControl->setVisible(!ui->widget_TextualControl->isVisible());
//        break;
//    case Qt::Key_H:
//        ui->widgetMapCanvas->mapHome();
//        break;
//    case Qt::Key_T:
//        // Toggle track table visibility with 'T' key
//        m_trackTable->setVisible(!m_trackTable->isVisible());
//        break;
//    }
//    QMainWindow::keyPressEvent(event);
//}

//void CMapMainWindow::slotMouseRead(QString mouseRead)
//{
//    ui->statusBar->showMessage(mouseRead);
//}

//void CMapMainWindow::on_pushButton_MapHome_clicked()
//{
//    ui->widgetMapCanvas->mapHome();
//}

//void CMapMainWindow::on_pushButton_OpenMaps_clicked()
//{
//    QString filter = "Raster Files (*.tif *.tiff *.png *.bmp *.jpg *.TIF *.tiff *.PNG *.BMP *.JPG)";

//    QString rasterPath = QFileDialog::getOpenFileName(
//                this,
//                "Select Raster or World-Referenced Image",
//                QString(),
//                filter
//                );

//    if (rasterPath.isEmpty())
//        return;

//    ui->widgetMapCanvas->importRasterMap(rasterPath);
//}

//void CMapMainWindow::on_pushButton_FLUSH_clicked()
//{
//    // Clear implementation if needed
//}

//void CMapMainWindow::on_pushButton_EXIT_clicked()
//{
//    exit(0);
//}

//void CMapMainWindow::updateTrackTable()
//{
//    // This method is now handled by CTrackTableWidget automatically
//    // Keep this for backward compatibility if needed
//    QList<stTrackDisplayInfo> listTracks = CDataWarehouse::getInstance()->getTrackList();

//    // Update status bar with track count
//    ui->statusBar->showMessage(
//        QString("Active Tracks: %1 | Press 'T' to toggle track table | Press 'H' for home | Press 'F' for controls")
//        .arg(listTracks.count())
//    );
//}

//void CMapMainWindow::onTrackSelected(int trackId)
//{
//    qDebug() << "Track selected:" << trackId;

//    // Find track info
//    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
//    for (const stTrackDisplayInfo &track : tracks) {
//        if (track.nTrkId == trackId) {
//            // Update status bar with selected track info
//            ui->statusBar->showMessage(
//                QString("Selected Track #%1 | Range: %2 km | Heading: %3°")
//                .arg(track.nTrkId)
//                .arg(track.range / 1000.0, 0, 'f', 2)
//                .arg(track.heading, 0, 'f', 1)
//            );
//            break;
//        }
//    }
//}

//void CMapMainWindow::onTrackDoubleClicked(int trackId)
//{
//    qDebug() << "Track double-clicked:" << trackId;

//    // Find track and center map on it
//    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
//    for (const stTrackDisplayInfo &track : tracks) {
//        if (track.nTrkId == trackId) {
//            // Center map on track using QGIS methods
//            QgsPointXY centerPoint(track.lon, track.lat);
//            ui->widgetMapCanvas->setCenter(centerPoint);
//            ui->widgetMapCanvas->refresh();

//            ui->statusBar->showMessage(
//                QString("Centered on Track #%1 (Lat: %2°, Lon: %3°)")
//                .arg(track.nTrkId)
//                .arg(track.lat, 0, 'f', 5)
//                .arg(track.lon, 0, 'f', 5),
//                3000
//            );
//            break;
//        }
//    }
//}


#include "cmapmainwindow.h"
#include "ui_cmapmainwindow.h"
#include "cppiwindow.h"
#include "ccontrolswindow.h"
#include "cdatawarehouse.h"
#include <QFileDialog>
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <QGuiApplication>
#include <QScreen>

CMapMainWindow::CMapMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMapMainWindow),
    m_ppiWindow(nullptr),
    m_controlsWindow(nullptr),
    m_isDualMonitor(false),
    m_isFullscreen(false),
    m_settings(new QSettings("RadarDisplay", "MainWindow", this))
{
    ui->setupUi(this);
    setWindowTitle("🎯 Radar Display - Window Manager");
    
    setupMonitors();
    setupDualWindows();
    connectWindowSignals();
    connectManagerButtons();
    
    loadWindowSettings();
    
    // Update status
    ui->statusBar->showMessage(QString("Ready | Monitors: %1 | Dual Monitor: %2")
                              .arg(m_screens.count())
                              .arg(m_isDualMonitor ? "Available" : "Not Available"));
    
    // Auto-arrange for dual monitor if available
    if (m_isDualMonitor) {
        QTimer::singleShot(500, this, &CMapMainWindow::onArrangeDualMonitor);
    }
}

CMapMainWindow::~CMapMainWindow()
{
    saveWindowSettings();
    delete ui;
}

void CMapMainWindow::setupDualWindows()
{
    // Create PPI window (Map + Track Table)
    m_ppiWindow = new CPPIWindow();
    m_ppiWindow->setWindowTitle("🎯 PPI Display - Map & Tracks");
    
    // Create Controls window (All control panels)
    m_controlsWindow = new CControlsWindow();
    m_controlsWindow->setWindowTitle("🎛️ Control Center - System Management");
    
    // Show both windows
    m_ppiWindow->show();
    m_controlsWindow->show();
}

void CMapMainWindow::connectWindowSignals()
{
    // Connect PPI window signals
    connect(m_ppiWindow, &CPPIWindow::trackSelected,
            this, &CMapMainWindow::onTrackSelected);
    connect(m_ppiWindow, &CPPIWindow::trackDoubleClicked,
            this, &CMapMainWindow::onTrackDoubleClicked);
    connect(m_ppiWindow, &CPPIWindow::mapHomeRequested,
            this, &CMapMainWindow::onMapHomeRequested);
    connect(m_ppiWindow, &CPPIWindow::newMapRequested,
            this, &CMapMainWindow::onNewMapRequested);
    
    // Connect Controls window signals
    connect(m_controlsWindow, &CControlsWindow::mapHomeRequested,
            this, &CMapMainWindow::onMapHomeRequested);
    connect(m_controlsWindow, &CControlsWindow::openMapsRequested,
            this, &CMapMainWindow::onOpenMapsRequested);
    connect(m_controlsWindow, &CControlsWindow::flushRequested,
            this, &CMapMainWindow::onFlushRequested);
    connect(m_controlsWindow, &CControlsWindow::exitRequested,
            this, &CMapMainWindow::onExitRequested);
    connect(m_controlsWindow, &CControlsWindow::zoomChanged,
            this, &CMapMainWindow::onZoomChanged);
    connect(m_controlsWindow, &CControlsWindow::opacityChanged,
            this, &CMapMainWindow::onOpacityChanged);
    connect(m_controlsWindow, &CControlsWindow::trackSizeChanged,
            this, &CMapMainWindow::onTrackSizeChanged);
    connect(m_controlsWindow, &CControlsWindow::trackFilterChanged,
            this, &CMapMainWindow::onTrackFilterChanged);
    connect(m_controlsWindow, &CControlsWindow::animationSpeedChanged,
            this, &CMapMainWindow::onAnimationSpeedChanged);
    connect(m_controlsWindow, &CControlsWindow::gridVisibilityChanged,
            this, &CMapMainWindow::onGridVisibilityChanged);
    connect(m_controlsWindow, &CControlsWindow::compassVisibilityChanged,
            this, &CMapMainWindow::onCompassVisibilityChanged);
    connect(m_controlsWindow, &CControlsWindow::chartsRequested,
            this, &CMapMainWindow::onChartsRequested);
    
    // Forward track selection to analytics widget
    connect(this, &CMapMainWindow::onTrackSelected,
            m_controlsWindow->getAnalyticsWidget(), &CAnalyticsWidget::onTrackSelected);
}

void CMapMainWindow::connectManagerButtons()
{
    // Connect UI buttons to slots
    connect(ui->showPPIButton, &QPushButton::clicked, this, &CMapMainWindow::onShowPPIWindow);
    connect(ui->showControlsButton, &QPushButton::clicked, this, &CMapMainWindow::onShowControlsWindow);
    connect(ui->arrangeDualButton, &QPushButton::clicked, this, &CMapMainWindow::onArrangeDualMonitor);
    connect(ui->fullscreenButton, &QPushButton::clicked, this, &CMapMainWindow::onToggleFullscreen);
}

void CMapMainWindow::applyLightTheme()
{
    // Light theme for main window manager
    setStyleSheet(
        "CMapMainWindow {"
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
        "}"
        "QLabel {"
        "   color: #334155;"
        "   font-weight: 500;"
        "}"
    );
}

void CMapMainWindow::setupMonitors()
{
    m_screens = QGuiApplication::screens();
    m_isDualMonitor = m_screens.count() >= 2;
    
    qDebug() << "Detected" << m_screens.count() << "monitors";
    for (int i = 0; i < m_screens.count(); ++i) {
        QScreen *screen = m_screens[i];
        qDebug() << "Monitor" << i << ":" << screen->name() 
                 << "Size:" << screen->size() 
                 << "Geometry:" << screen->geometry();
    }
}

void CMapMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_F1:
        onShowPPIWindow();
        break;
    case Qt::Key_F2:
        onShowControlsWindow();
        break;
    case Qt::Key_F3:
        onArrangeDualMonitor();
        break;
    case Qt::Key_F4:
        onToggleFullscreen();
        break;
    case Qt::Key_Escape:
        if (m_isFullscreen) {
            onToggleFullscreen();
        }
        break;
    }
    QMainWindow::keyPressEvent(event);
}

void CMapMainWindow::closeEvent(QCloseEvent *event)
{
    // Close all windows when main window closes
    if (m_ppiWindow) {
        m_ppiWindow->close();
    }
    if (m_controlsWindow) {
        m_controlsWindow->close();
    }
    
    saveWindowSettings();
    event->accept();
}

// Window management slots
void CMapMainWindow::onShowPPIWindow()
{
    if (m_ppiWindow) {
        m_ppiWindow->show();
        m_ppiWindow->raise();
        m_ppiWindow->activateWindow();
    }
}

void CMapMainWindow::onShowControlsWindow()
{
    if (m_controlsWindow) {
        m_controlsWindow->show();
        m_controlsWindow->raise();
        m_controlsWindow->activateWindow();
    }
}

void CMapMainWindow::onArrangeDualMonitor()
{
    if (!m_isDualMonitor || m_screens.count() < 2) {
        QMessageBox::information(this, "Dual Monitor", 
            "Dual monitor setup requires at least 2 displays.\n"
            "Currently detected: " + QString::number(m_screens.count()) + " display(s)");
        return;
    }
    
    // Arrange PPI window on first monitor
    QScreen *primaryScreen = m_screens[0];
    QRect primaryGeometry = primaryScreen->availableGeometry();
    m_ppiWindow->setGeometry(primaryGeometry);
    m_ppiWindow->showMaximized();
    
    // Arrange Controls window on second monitor
    QScreen *secondaryScreen = m_screens[1];
    QRect secondaryGeometry = secondaryScreen->availableGeometry();
    m_controlsWindow->setGeometry(secondaryGeometry);
    m_controlsWindow->showMaximized();
    
    qDebug() << "Arranged windows for dual monitor setup";
}

void CMapMainWindow::onToggleFullscreen()
{
    m_isFullscreen = !m_isFullscreen;
    
    if (m_isFullscreen) {
        if (m_ppiWindow) m_ppiWindow->showFullScreen();
        if (m_controlsWindow) m_controlsWindow->showFullScreen();
    } else {
        if (m_ppiWindow) m_ppiWindow->showNormal();
        if (m_controlsWindow) m_controlsWindow->showNormal();
    }
    
    qDebug() << "Fullscreen mode:" << m_isFullscreen;
}

// Inter-window communication slots
void CMapMainWindow::onTrackSelected(int trackId)
{
    qDebug() << "Track selected:" << trackId;
    
    // Forward to analytics widget in controls window
    if (m_controlsWindow && m_controlsWindow->getAnalyticsWidget()) {
        m_controlsWindow->getAnalyticsWidget()->onTrackSelected(trackId);
    }
}

void CMapMainWindow::onTrackDoubleClicked(int trackId)
{
    qDebug() << "Track double-clicked:" << trackId;
    // Track focusing is handled by individual windows
}

void CMapMainWindow::onMapHomeRequested()
{
    if (m_ppiWindow && m_ppiWindow->getMapCanvas()) {
        m_ppiWindow->getMapCanvas()->mapHome();
    }
    qDebug() << "Map home requested";
}

void CMapMainWindow::onNewMapRequested(const QString& mapPath)
{
    qDebug() << "New map requested:" << mapPath;
    // Map loading is handled by PPI window
}

// Control panel forwarding slots
void CMapMainWindow::onOpenMapsRequested()
{
    QString filter = "Map Files (*.tif *.tiff *.png *.bmp *.jpg *.jpeg *.TIF *.TIFF *.PNG *.BMP *.JPG *.JPEG)";
    QString mapPath = QFileDialog::getOpenFileName(
        this,
        "Select Map File",
        QString(),
        filter
    );
    
    if (!mapPath.isEmpty() && m_ppiWindow && m_ppiWindow->getMapCanvas()) {
        m_ppiWindow->getMapCanvas()->importRasterMap(mapPath);
        qDebug() << "Map loaded:" << mapPath;
    }
}

void CMapMainWindow::onFlushRequested()
{
    qDebug() << "Flush requested";
    // TODO: Implement flush functionality
}

void CMapMainWindow::onExitRequested()
{
    QApplication::quit();
}

void CMapMainWindow::onZoomChanged(double zoom)
{
    qDebug() << "Zoom changed to:" << zoom;
    // TODO: Implement zoom change
}

void CMapMainWindow::onOpacityChanged(int opacity)
{
    qDebug() << "Opacity changed to:" << opacity;
    // TODO: Implement opacity change
}

void CMapMainWindow::onTrackSizeChanged(int size)
{
    qDebug() << "Track size changed to:" << size;
    // TODO: Implement track size change
}

void CMapMainWindow::onTrackFilterChanged(bool showFriend, bool showHostile, bool showUnknown)
{
    qDebug() << "Track filter changed - Friend:" << showFriend
             << "Hostile:" << showHostile << "Unknown:" << showUnknown;
    // TODO: Implement track filtering
}

void CMapMainWindow::onAnimationSpeedChanged(int speed)
{
    qDebug() << "Animation speed changed to:" << speed;
    // TODO: Implement animation speed change
}

void CMapMainWindow::onGridVisibilityChanged(bool visible)
{
    qDebug() << "Grid visibility:" << visible;
    // TODO: Implement grid visibility
}

void CMapMainWindow::onCompassVisibilityChanged(bool visible)
{
    qDebug() << "Compass visibility:" << visible;
    // TODO: Implement compass visibility
}

void CMapMainWindow::onChartsRequested()
{
    if (m_controlsWindow && m_controlsWindow->getChartsWidget()) {
        // Switch to charts tab in controls window
        qDebug() << "Charts requested - switching to charts tab";
    }
}

void CMapMainWindow::saveWindowSettings()
{
    m_settings->setValue("geometry", saveGeometry());
    m_settings->setValue("windowState", saveState());
    m_settings->setValue("isDualMonitor", m_isDualMonitor);
    m_settings->setValue("isFullscreen", m_isFullscreen);
    
    if (m_ppiWindow) {
        m_settings->setValue("ppiGeometry", m_ppiWindow->saveGeometry());
        m_settings->setValue("ppiState", m_ppiWindow->saveState());
    }
    
    if (m_controlsWindow) {
        m_settings->setValue("controlsGeometry", m_controlsWindow->saveGeometry());
        m_settings->setValue("controlsState", m_controlsWindow->saveState());
    }
}

void CMapMainWindow::loadWindowSettings()
{
    restoreGeometry(m_settings->value("geometry").toByteArray());
    restoreState(m_settings->value("windowState").toByteArray());
    
    m_isDualMonitor = m_settings->value("isDualMonitor", m_isDualMonitor).toBool();
    m_isFullscreen = m_settings->value("isFullscreen", false).toBool();
    
    if (m_ppiWindow) {
        m_ppiWindow->restoreGeometry(m_settings->value("ppiGeometry").toByteArray());
        m_ppiWindow->restoreState(m_settings->value("ppiState").toByteArray());
    }
    
    if (m_controlsWindow) {
        m_controlsWindow->restoreGeometry(m_settings->value("controlsGeometry").toByteArray());
        m_controlsWindow->restoreState(m_settings->value("controlsState").toByteArray());
    }
}

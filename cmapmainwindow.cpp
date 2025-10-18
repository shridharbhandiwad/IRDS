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
#include "cdatawarehouse.h"
#include "MapDisplay/cppiwindow.h"
#include "MapDisplay/ccontrolswindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QScreen>
#include <QApplication>
#include <qgspoint.h>

CMapMainWindow::CMapMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMapMainWindow),
    m_ppiWindow(nullptr),
    m_controlsWindow(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Radar Display - Dual Monitor Control System");

    // Setup dual-monitor windows
    setupDualMonitorWindows();

    // Apply light theme
    applyLightTheme();

    // Position windows for dual-monitor setup
    positionWindowsForDualMonitor();

    // Hide the main window (it's just a controller now)
    hide();
}

CMapMainWindow::~CMapMainWindow()
{
    delete ui;
}

void CMapMainWindow::setupDualMonitorWindows()
{
    // Create PPI window (Monitor 1)
    m_ppiWindow = new CPPIWindow(this);
    m_ppiWindow->show();

    // Create Controls window (Monitor 2)
    m_controlsWindow = new CControlsWindow(this);
    m_controlsWindow->show();

    // Connect control window signals to appropriate handlers
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
}

void CMapMainWindow::applyLightTheme()
{
    // Apply light theme to both windows
    QString lightTheme = 
        "QMainWindow {"
        "   background-color: #E3F2FD;"
        "}"
        "QWidget {"
        "   background-color: #FFFFFF;"
        "   color: #1565C0;"
        "}";
    
    if (m_ppiWindow) {
        m_ppiWindow->setStyleSheet(lightTheme);
    }
    
    if (m_controlsWindow) {
        m_controlsWindow->setStyleSheet(lightTheme);
    }
    
    setStyleSheet(lightTheme);
}

void CMapMainWindow::positionWindowsForDualMonitor()
{
    // Get available screens
    QList<QScreen*> screens = QApplication::screens();
    
    if (screens.count() >= 2) {
        // Dual monitor setup
        QScreen *primaryScreen = screens[0];
        QScreen *secondaryScreen = screens[1];
        
        // Position PPI window on primary monitor
        QRect primaryGeometry = primaryScreen->availableGeometry();
        m_ppiWindow->move(primaryGeometry.left(), primaryGeometry.top());
        m_ppiWindow->resize(primaryGeometry.width(), primaryGeometry.height());
        
        // Position Controls window on secondary monitor
        QRect secondaryGeometry = secondaryScreen->availableGeometry();
        m_controlsWindow->move(secondaryGeometry.left(), secondaryGeometry.top());
        m_controlsWindow->resize(secondaryGeometry.width(), secondaryGeometry.height());
        
        qDebug() << "Dual monitor setup: PPI on Monitor 1, Controls on Monitor 2";
    } else {
        // Single monitor setup - position side by side
        QScreen *screen = screens[0];
        QRect geometry = screen->availableGeometry();
        
        int halfWidth = geometry.width() / 2;
        
        // PPI window on left half
        m_ppiWindow->move(geometry.left(), geometry.top());
        m_ppiWindow->resize(halfWidth - 10, geometry.height());
        
        // Controls window on right half
        m_controlsWindow->move(geometry.left() + halfWidth + 10, geometry.top());
        m_controlsWindow->resize(halfWidth - 10, geometry.height());
        
        qDebug() << "Single monitor setup: Windows positioned side by side";
    }
}


void CMapMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_F1:
        // Toggle PPI window visibility
        if (m_ppiWindow) {
            m_ppiWindow->setVisible(!m_ppiWindow->isVisible());
        }
        break;
    case Qt::Key_F2:
        // Toggle Controls window visibility
        if (m_controlsWindow) {
            m_controlsWindow->setVisible(!m_controlsWindow->isVisible());
        }
        break;
    case Qt::Key_H:
        // Map home
        onMapHomeRequested();
        break;
    case Qt::Key_Escape:
        // Exit application
        onExitRequested();
        break;
    }
    QMainWindow::keyPressEvent(event);
}


// Control window signal handlers
void CMapMainWindow::onMapHomeRequested()
{
    if (m_ppiWindow && m_ppiWindow->getMapCanvas()) {
        m_ppiWindow->getMapCanvas()->mapHome();
        qDebug() << "Map reset to home view";
    }
}

void CMapMainWindow::onOpenMapsRequested()
{
    QString filter = "Raster Files (*.tif *.tiff *.png *.bmp *.jpg *.TIF *.PNG *.BMP *.JPG)";
    
    QString rasterPath = QFileDialog::getOpenFileName(
        m_controlsWindow,
        "Select Raster or World-Referenced Image",
        QString(),
        filter
    );
    
    if (!rasterPath.isEmpty() && m_ppiWindow && m_ppiWindow->getMapCanvas()) {
        m_ppiWindow->getMapCanvas()->importRasterMap(rasterPath);
    }
}

void CMapMainWindow::onFlushRequested()
{
    qDebug() << "Flush requested";
    // Implement flush logic here
}

void CMapMainWindow::onExitRequested()
{
    QApplication::quit();
}

void CMapMainWindow::onZoomChanged(double zoom)
{
    qDebug() << "Zoom changed to:" << zoom;
    // TODO: Implement zoom change on map canvas
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


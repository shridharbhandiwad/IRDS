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
#include "MapDisplay/ctracktablewidget.h"
#include "MapDisplay/cconfigpanelwidget.h"
#include "MapDisplay/cchartswidget.h"
#include "MapDisplay/cinterfacespanelwidget.h"
#include "MapDisplay/canalyticswidget.h"
#include "MapDisplay/csimulationwidget.h"
#include "MapDisplay/crecordingwidget.h"
#include "MapDisplay/chealthmonitorwidget.h"
#include "MapDisplay/cpredictivemaintenancewidget.h"
#include <QFileDialog>
#include <QDebug>
#include <qgspoint.h>

CMapMainWindow::CMapMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMapMainWindow)
{
    ui->setupUi(this);
    ui->widgetMapCanvas->Initialize();
    setWindowTitle("⚡ Radar Display - Advanced Control System");

    // Setup rich dockable widgets
    setupTrackTable();
    setupConfigPanel();
    setupInterfacesPanel();
    setupChartsWidget();
    setupAnalyticsWidget();
    setupSimulationWidget();
    setupRecordingWidget();
    setupHealthMonitorWidget();
    setupPredictiveMaintenanceWidget();

    // Hide the old widgets
    if (ui->tableWidget) {
        ui->tableWidget->setVisible(false);
    }

    if (ui->widget_TextualControl) {
        ui->widget_TextualControl->setVisible(false);
    }

    connect(ui->widgetMapCanvas, SIGNAL(signalMouseRead(QString)), this, SLOT(slotMouseRead(QString)));

    // Apply modern dark theme to main window
    applyModernTheme();

    // Set better dock widget layout
    setupDockWidgetLayout();

    // Start update timer for status bar
    connect(&_m_updateTimer, &QTimer::timeout, this, &CMapMainWindow::updateTrackTable);
    _m_updateTimer.start(1000);
}

CMapMainWindow::~CMapMainWindow()
{
    delete ui;
}

void CMapMainWindow::setupTrackTable()
{
    m_trackTable = new CTrackTableWidget(this);

    // Add as dockable widget to right side
    addDockWidget(Qt::RightDockWidgetArea, m_trackTable);

    // Set preferred size for better space utilization
    m_trackTable->setMinimumWidth(350);
    m_trackTable->setMaximumWidth(500);

    // Make it initially visible
    m_trackTable->setVisible(true);

    // Allow docking on left and right sides only
    m_trackTable->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // Enable floating
    m_trackTable->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );

    // Connect signals for track interaction
    connect(m_trackTable, &CTrackTableWidget::trackSelected,
            this, &CMapMainWindow::onTrackSelected);
    connect(m_trackTable, &CTrackTableWidget::trackDoubleClicked,
            this, &CMapMainWindow::onTrackDoubleClicked);
}

void CMapMainWindow::setupConfigPanel()
{
    m_configPanel = new CConfigPanelWidget(this);

    // Add as dockable widget to left side
    addDockWidget(Qt::LeftDockWidgetArea, m_configPanel);

    // Set preferred size for better space utilization
    m_configPanel->setMinimumWidth(300);
    m_configPanel->setMaximumWidth(400);

    // Make it initially visible
    m_configPanel->setVisible(true);

    // Allow docking on left and right only
    m_configPanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // Enable features
    m_configPanel->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );

    // Connect all signals
    connect(m_configPanel, &CConfigPanelWidget::mapHomeRequested,
            this, &CMapMainWindow::onMapHomeRequested);
    connect(m_configPanel, &CConfigPanelWidget::openMapsRequested,
            this, &CMapMainWindow::onOpenMapsRequested);
    connect(m_configPanel, &CConfigPanelWidget::flushRequested,
            this, &CMapMainWindow::onFlushRequested);
    connect(m_configPanel, &CConfigPanelWidget::exitRequested,
            this, &CMapMainWindow::onExitRequested);
    connect(m_configPanel, &CConfigPanelWidget::zoomLevelChanged,
            this, &CMapMainWindow::onZoomChanged);
    connect(m_configPanel, &CConfigPanelWidget::opacityChanged,
            this, &CMapMainWindow::onOpacityChanged);
    connect(m_configPanel, &CConfigPanelWidget::trackSizeChanged,
            this, &CMapMainWindow::onTrackSizeChanged);
    connect(m_configPanel, &CConfigPanelWidget::trackFilterChanged,
            this, &CMapMainWindow::onTrackFilterChanged);
    connect(m_configPanel, &CConfigPanelWidget::animationSpeedChanged,
            this, &CMapMainWindow::onAnimationSpeedChanged);
    connect(m_configPanel, &CConfigPanelWidget::gridVisibilityChanged,
            this, &CMapMainWindow::onGridVisibilityChanged);
    connect(m_configPanel, &CConfigPanelWidget::compassVisibilityChanged,
            this, &CMapMainWindow::onCompassVisibilityChanged);
    connect(m_configPanel, &CConfigPanelWidget::chartsRequested,
            this, &CMapMainWindow::onChartsRequested);
}

void CMapMainWindow::applyModernTheme()
{
    // Modern dark theme with gradient accents
    setStyleSheet(
        "QMainWindow {"
        "   background-color: #0f172a;"
        "}"
        "QWidget {"
        "   background-color: #0f172a;"
        "   color: #ffffff;"
        "}"
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #667eea, stop:1 #764ba2);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 10px 16px;"
        "   font-weight: bold;"
        "   font-size: 12px;"
        "   min-height: 32px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #5568d3, stop:1 #6b3fa0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4c51bf, stop:1 #5a32a3);"
        "}"
        "QStatusBar {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #1e293b, stop:1 #334155);"
        "   color: #ffffff;"
        "   border-top: 2px solid #667eea;"
        "   font-size: 11px;"
        "   padding: 6px;"
        "   font-weight: 500;"
        "}"
        "QMenuBar {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #1e293b, stop:1 #334155);"
        "   color: #ffffff;"
        "   border-bottom: 2px solid #667eea;"
        "   padding: 4px;"
        "}"
        "QMenuBar::item {"
        "   background-color: transparent;"
        "   padding: 8px 16px;"
        "   border-radius: 6px;"
        "}"
        "QMenuBar::item:selected {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "}"
        "QMenu {"
        "   background-color: #1e293b;"
        "   color: #ffffff;"
        "   border: 2px solid #4a5568;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "}"
        "QMenu::item {"
        "   padding: 8px 24px;"
        "   border-radius: 4px;"
        "}"
        "QMenu::item:selected {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);"
        "}"
    );
}

void CMapMainWindow::setupDockWidgetLayout()
{
    // Set dock widget size constraints to prevent overlapping
    setDockNestingEnabled(true);
    
    // Set minimum dock widget sizes
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    
    // Resize dock areas to reasonable proportions
    QList<int> leftSizes;
    QList<int> rightSizes;
    QList<int> bottomSizes;
    
    // Left area: Config/Interfaces (top), Simulation/Recording (bottom)
    leftSizes << 400 << 400;  // Equal split
    
    // Right area: Track Table (top), Analytics/Health/Maintenance (bottom)
    rightSizes << 350 << 350;  // Equal split
    
    // Bottom area: Charts
    bottomSizes << 200;
    
    // Apply size constraints
    resizeDocks({m_configPanel, m_simulationWidget}, leftSizes, Qt::Vertical);
    resizeDocks({m_trackTable, m_analyticsWidget}, rightSizes, Qt::Vertical);
    resizeDocks({m_chartsWidget}, bottomSizes, Qt::Horizontal);
    
    // Set initial visibility state
    m_configPanel->setVisible(true);
    m_trackTable->setVisible(true);
    m_simulationWidget->setVisible(true);
    m_analyticsWidget->setVisible(true);  // Visible by default
    m_chartsWidget->setVisible(false);     // Hidden by default
    m_interfacesPanel->setVisible(true);  // Visible by default
    m_recordingWidget->setVisible(false);  // Hidden by default
    m_healthMonitorWidget->setVisible(false);  // Hidden by default
    m_predictiveMaintenanceWidget->setVisible(false);  // Hidden by default
}

void CMapMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_F:
        ui->widget_TextualControl->setVisible(!ui->widget_TextualControl->isVisible());
        break;
    case Qt::Key_H:
        ui->widgetMapCanvas->mapHome();
        break;
    case Qt::Key_T:
        // Toggle track table visibility
        m_trackTable->setVisible(!m_trackTable->isVisible());
        break;
    case Qt::Key_C:
        // Toggle config panel visibility
        m_configPanel->setVisible(!m_configPanel->isVisible());
        break;
    case Qt::Key_I:
        // Toggle interfaces panel visibility
        m_interfacesPanel->setVisible(!m_interfacesPanel->isVisible());
        break;
    case Qt::Key_A:
        // Toggle analytics panel visibility
        m_analyticsWidget->setVisible(!m_analyticsWidget->isVisible());
        break;
    case Qt::Key_S:
        // Toggle simulation panel visibility
        m_simulationWidget->setVisible(!m_simulationWidget->isVisible());
        break;
    case Qt::Key_R:
        // Toggle recording panel visibility
        m_recordingWidget->setVisible(!m_recordingWidget->isVisible());
        break;
    case Qt::Key_M:
        // Toggle health monitor visibility
        m_healthMonitorWidget->setVisible(!m_healthMonitorWidget->isVisible());
        break;
    case Qt::Key_P:
        // Toggle predictive maintenance visibility
        m_predictiveMaintenanceWidget->setVisible(!m_predictiveMaintenanceWidget->isVisible());
        break;
    }
    QMainWindow::keyPressEvent(event);
}

void CMapMainWindow::slotMouseRead(QString mouseRead)
{
    ui->statusBar->showMessage(mouseRead);
}

void CMapMainWindow::on_pushButton_MapHome_clicked()
{
    ui->widgetMapCanvas->mapHome();
}

void CMapMainWindow::on_pushButton_OpenMaps_clicked()
{
    QString filter = "Raster Files (*.tif *.tiff *.png *.bmp *.jpg *.TIF *.tiff *.PNG *.BMP *.JPG)";

    QString rasterPath = QFileDialog::getOpenFileName(
                this,
                "Select Raster or World-Referenced Image",
                QString(),
                filter
                );

    if (rasterPath.isEmpty())
        return;

    ui->widgetMapCanvas->importRasterMap(rasterPath);
}

void CMapMainWindow::on_pushButton_FLUSH_clicked()
{
    // Flush implementation
    qDebug() << "Flush requested";
}

void CMapMainWindow::on_pushButton_EXIT_clicked()
{
    exit(0);
}

void CMapMainWindow::updateTrackTable()
{
    QList<stTrackDisplayInfo> listTracks = CDataWarehouse::getInstance()->getTrackList();

    // Update status bar with keyboard shortcuts
    QString statusMsg = QString("🎯 Tracks: %1 | T:Table C:Controls I:Interfaces A:Analytics S:Simulation R:Recording M:Health P:Maintenance H:Home")
        .arg(listTracks.count());

    ui->statusBar->showMessage(statusMsg);
}

void CMapMainWindow::onTrackSelected(int trackId)
{
    qDebug() << "Track selected:" << trackId;

    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == trackId) {
            ui->statusBar->showMessage(
                QString("✓ Track #%1 | 📏 Range: %2 km | 🧭 Heading: %3° | 📍 Pos: %4°, %5°")
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

void CMapMainWindow::onTrackDoubleClicked(int trackId)
{
    qDebug() << "Track double-clicked:" << trackId;

    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == trackId) {
            QgsPointXY centerPoint(track.lon, track.lat);
            ui->widgetMapCanvas->setCenter(centerPoint);
            ui->widgetMapCanvas->refresh();

            ui->statusBar->showMessage(
                QString("🎯 Centered on Track #%1 (Lat: %2°, Lon: %3°)")
                .arg(track.nTrkId)
                .arg(track.lat, 0, 'f', 5)
                .arg(track.lon, 0, 'f', 5),
                3000
            );
            break;
        }
    }
}

// Config panel slot implementations
void CMapMainWindow::onMapHomeRequested()
{
    ui->widgetMapCanvas->mapHome();
    ui->statusBar->showMessage("🏠 Map reset to home view", 2000);
}

void CMapMainWindow::onOpenMapsRequested()
{
    on_pushButton_OpenMaps_clicked();
}

void CMapMainWindow::onFlushRequested()
{
    on_pushButton_FLUSH_clicked();
    ui->statusBar->showMessage("🔄 Data flushed", 2000);
}

void CMapMainWindow::onExitRequested()
{
    on_pushButton_EXIT_clicked();
}

void CMapMainWindow::onZoomChanged(double zoom)
{
    qDebug() << "Zoom changed to:" << zoom;
    // Implement zoom change
    ui->statusBar->showMessage(QString("🔍 Zoom level: %1x").arg(zoom, 0, 'f', 1), 1000);
}

void CMapMainWindow::onOpacityChanged(int opacity)
{
    qDebug() << "Opacity changed to:" << opacity;
    // Implement opacity change
    ui->statusBar->showMessage(QString("👁 Map opacity: %1%").arg(opacity), 1000);
}

void CMapMainWindow::onTrackSizeChanged(int size)
{
    qDebug() << "Track size changed to:" << size;
    // Implement track size change
    ui->statusBar->showMessage(QString("📏 Track size: %1px").arg(size), 1000);
}

void CMapMainWindow::onTrackFilterChanged(bool showFriend, bool showHostile, bool showUnknown)
{
    qDebug() << "Track filter changed - Friend:" << showFriend
             << "Hostile:" << showHostile << "Unknown:" << showUnknown;
    // Implement track filtering
    QString filterMsg = "🔍 Showing: ";
    QStringList filters;
    if (showFriend) filters << "✓ Friendly";
    if (showHostile) filters << "✖ Hostile";
    if (showUnknown) filters << "? Unknown";
    ui->statusBar->showMessage(filterMsg + filters.join(", "), 2000);
}

void CMapMainWindow::onAnimationSpeedChanged(int speed)
{
    qDebug() << "Animation speed changed to:" << speed;
    // Implement animation speed change
    ui->statusBar->showMessage(QString("⚡ Animation speed: %1ms").arg(speed), 1000);
}

void CMapMainWindow::onGridVisibilityChanged(bool visible)
{
    qDebug() << "Grid visibility:" << visible;
    // Implement grid visibility
    ui->statusBar->showMessage(visible ? "📐 Grid enabled" : "📐 Grid disabled", 1000);
}

void CMapMainWindow::onCompassVisibilityChanged(bool visible)
{
    qDebug() << "Compass visibility:" << visible;
    // Implement compass visibility
    ui->statusBar->showMessage(visible ? "🧭 Compass enabled" : "🧭 Compass disabled", 1000);
}

void CMapMainWindow::setupInterfacesPanel()
{
    m_interfacesPanel = new CInterfacesPanelWidget(this);

    // Add as dockable widget to left side, below config panel
    addDockWidget(Qt::LeftDockWidgetArea, m_interfacesPanel);
    
    // Stack it below the config panel
    tabifyDockWidget(m_configPanel, m_interfacesPanel);

    // Set preferred size for better space utilization
    m_interfacesPanel->setMinimumWidth(300);
    m_interfacesPanel->setMaximumWidth(400);

    // Make it initially visible
    m_interfacesPanel->setVisible(true);
    
    // Make config panel the default visible tab
    m_configPanel->raise();

    // Allow docking on left and right
    m_interfacesPanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // Enable features
    m_interfacesPanel->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );

    // Connect interface signals to debug slots
    connect(m_interfacesPanel, &CInterfacesPanelWidget::servoAzimuthChanged, this, [](double az) {
        qDebug() << "Servo azimuth changed to:" << az;
    });
    connect(m_interfacesPanel, &CInterfacesPanelWidget::servoElevationChanged, this, [](double el) {
        qDebug() << "Servo elevation changed to:" << el;
    });
    connect(m_interfacesPanel, &CInterfacesPanelWidget::radarScanStartRequested, this, []() {
        qDebug() << "Radar scan start requested";
    });
    connect(m_interfacesPanel, &CInterfacesPanelWidget::gunFireRequested, this, []() {
        qDebug() << "Gun fire requested!";
    });
    connect(m_interfacesPanel, &CInterfacesPanelWidget::missileLaunchRequested, this, []() {
        qDebug() << "Missile launch requested!";
    });
    connect(m_interfacesPanel, &CInterfacesPanelWidget::loggingStarted, this, [this]() {
        qDebug() << "Logging started";
        m_interfacesPanel->appendLogMessage("Logging session started");
    });
}

void CMapMainWindow::setupChartsWidget()
{
    m_chartsWidget = new CChartsWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea, m_chartsWidget);
    
    // Set smaller size for better space utilization
    m_chartsWidget->setMinimumHeight(250);
    m_chartsWidget->setMaximumHeight(350);
    
    m_chartsWidget->setVisible(false); // Hidden by default

    m_chartsWidget->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    m_chartsWidget->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );
}

void CMapMainWindow::onChartsRequested()
{
    m_chartsWidget->setVisible(!m_chartsWidget->isVisible());
}

void CMapMainWindow::setupAnalyticsWidget()
{
    m_analyticsWidget = new CAnalyticsWidget(this);
    
    // Add as dockable widget to right side, below track table
    addDockWidget(Qt::RightDockWidgetArea, m_analyticsWidget);
    
    // Stack it below the track table (tabbed)
    tabifyDockWidget(m_trackTable, m_analyticsWidget);
    
    // Set preferred size for better space utilization
    m_analyticsWidget->setMinimumWidth(350);
    m_analyticsWidget->setMaximumWidth(500);
    
    // Make track table the default visible tab
    m_trackTable->raise();
    
    // Allow docking on left and right
    m_analyticsWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    // Enable features
    m_analyticsWidget->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );
    
    // Connect track selection signals
    connect(m_trackTable, &CTrackTableWidget::trackSelected,
            m_analyticsWidget, &CAnalyticsWidget::onTrackSelected);
}

void CMapMainWindow::setupSimulationWidget()
{
    m_simulationWidget = new CSimulationWidget(this);
    
    // Add as dockable widget to left side
    addDockWidget(Qt::LeftDockWidgetArea, m_simulationWidget);
    
    // Set preferred size
    m_simulationWidget->setMinimumWidth(400);
    m_simulationWidget->setMaximumWidth(550);
    
    // Make it initially visible
    m_simulationWidget->setVisible(true);
    
    // Allow docking on left and right
    m_simulationWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    // Enable features
    m_simulationWidget->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );
    
    // Connect simulation signal to data warehouse for direct track updates
    connect(m_simulationWidget, &CSimulationWidget::simulatedTrackData,
            CDataWarehouse::getInstance(), &CDataWarehouse::slotUpdateTrackData);
}

void CMapMainWindow::setupRecordingWidget()
{
    m_recordingWidget = new CRecordingWidget(this);
    
    // Add as dockable widget to left side, tabbed with simulation
    addDockWidget(Qt::LeftDockWidgetArea, m_recordingWidget);
    tabifyDockWidget(m_simulationWidget, m_recordingWidget);
    
    // Set preferred size
    m_recordingWidget->setMinimumWidth(400);
    m_recordingWidget->setMaximumWidth(550);
    
    // Make simulation the default visible tab
    m_simulationWidget->raise();
    
    // Allow docking on left and right
    m_recordingWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    // Enable features
    m_recordingWidget->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );
    
    // Connect replay signal to data warehouse
    connect(m_recordingWidget, &CRecordingWidget::replayTrackData,
            CDataWarehouse::getInstance(), &CDataWarehouse::slotUpdateTrackData);
}

void CMapMainWindow::setupHealthMonitorWidget()
{
    m_healthMonitorWidget = new CHealthMonitorWidget(this);
    
    // Add as dockable widget to right side
    addDockWidget(Qt::RightDockWidgetArea, m_healthMonitorWidget);
    
    // Set preferred size
    m_healthMonitorWidget->setMinimumWidth(350);
    m_healthMonitorWidget->setMaximumWidth(500);
    
    // Make it initially visible
    m_healthMonitorWidget->setVisible(true);
    
    // Allow docking on left and right
    m_healthMonitorWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    // Enable features
    m_healthMonitorWidget->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );
}

void CMapMainWindow::setupPredictiveMaintenanceWidget()
{
    m_predictiveMaintenanceWidget = new CPredictiveMaintenanceWidget(this);
    
    // Add as dockable widget to right side, tabbed with health monitor
    addDockWidget(Qt::RightDockWidgetArea, m_predictiveMaintenanceWidget);
    tabifyDockWidget(m_healthMonitorWidget, m_predictiveMaintenanceWidget);
    
    // Set preferred size
    m_predictiveMaintenanceWidget->setMinimumWidth(350);
    m_predictiveMaintenanceWidget->setMaximumWidth(500);
    
    // Make health monitor the default visible tab
    m_healthMonitorWidget->raise();
    
    // Allow docking on left and right
    m_predictiveMaintenanceWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    // Enable features
    m_predictiveMaintenanceWidget->setFeatures(
        QDockWidget::DockWidgetClosable |
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetFloatable
    );
}

#include "ccontrolswindow.h"
#include "cconfigpanelwidget.h"
#include "cinterfacespanelwidget.h"
#include "canalyticswidget.h"
#include "csimulationwidget.h"
#include "crecordingwidget.h"
#include "chealthmonitorwidget.h"
#include "cpredictivemaintenancewidget.h"
#include "cchartswidget.h"
#include "../cdatawarehouse.h"
#include <QVBoxLayout>
#include <QStatusBar>
#include <QLabel>
#include <QDebug>

CControlsWindow::CControlsWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tabWidget(nullptr)
    , m_configPanel(nullptr)
    , m_interfacesPanel(nullptr)
    , m_analyticsWidget(nullptr)
    , m_simulationWidget(nullptr)
    , m_recordingWidget(nullptr)
    , m_healthMonitorWidget(nullptr)
    , m_predictiveMaintenanceWidget(nullptr)
    , m_chartsWidget(nullptr)
{
    setWindowTitle("Control Center - All Tabs");
    
    setupUI();
    setupConfigPanel();
    setupInterfacesPanel();
    setupAnalyticsWidget();
    setupSimulationWidget();
    setupRecordingWidget();
    setupHealthMonitorWidget();
    setupPredictiveMaintenanceWidget();
    setupChartsWidget();
    applyLightTheme();
    
    // Set window size for typical monitor
    resize(1200, 900);
}

CControlsWindow::~CControlsWindow()
{
}

void CControlsWindow::setupUI()
{
    // Create central widget with tab widget
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(8);
    
    // Create tab widget
    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setTabPosition(QTabWidget::North);
    m_tabWidget->setMovable(true);
    m_tabWidget->setDocumentMode(false);
    
    mainLayout->addWidget(m_tabWidget);
    setCentralWidget(centralWidget);
    
    // Create status bar
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    statusBar->showMessage("Control Center Ready");
    
    // Connect tab changed signal
    connect(m_tabWidget, &QTabWidget::currentChanged,
            this, &CControlsWindow::onCurrentTabChanged);
}

void CControlsWindow::setupConfigPanel()
{
    // Create a container widget for the config panel
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_configPanel = new CConfigPanelWidget(this);
    
    // Remove dock widget features since it's now in a tab
    QWidget *configContent = m_configPanel->widget();
    layout->addWidget(configContent);
    
    m_tabWidget->addTab(container, "⚙️ Configuration");
    
    // Forward all configuration signals
    connect(m_configPanel, &CConfigPanelWidget::mapHomeRequested,
            this, &CControlsWindow::mapHomeRequested);
    connect(m_configPanel, &CConfigPanelWidget::openMapsRequested,
            this, &CControlsWindow::openMapsRequested);
    connect(m_configPanel, &CConfigPanelWidget::flushRequested,
            this, &CControlsWindow::flushRequested);
    connect(m_configPanel, &CConfigPanelWidget::exitRequested,
            this, &CControlsWindow::exitRequested);
    connect(m_configPanel, &CConfigPanelWidget::zoomLevelChanged,
            this, &CControlsWindow::zoomChanged);
    connect(m_configPanel, &CConfigPanelWidget::opacityChanged,
            this, &CControlsWindow::opacityChanged);
    connect(m_configPanel, &CConfigPanelWidget::trackSizeChanged,
            this, &CControlsWindow::trackSizeChanged);
    connect(m_configPanel, &CConfigPanelWidget::trackFilterChanged,
            this, &CControlsWindow::trackFilterChanged);
    connect(m_configPanel, &CConfigPanelWidget::animationSpeedChanged,
            this, &CControlsWindow::animationSpeedChanged);
    connect(m_configPanel, &CConfigPanelWidget::gridVisibilityChanged,
            this, &CControlsWindow::gridVisibilityChanged);
    connect(m_configPanel, &CConfigPanelWidget::compassVisibilityChanged,
            this, &CControlsWindow::compassVisibilityChanged);
}

void CControlsWindow::setupInterfacesPanel()
{
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_interfacesPanel = new CInterfacesPanelWidget(this);
    QWidget *interfacesContent = m_interfacesPanel->widget();
    layout->addWidget(interfacesContent);
    
    m_tabWidget->addTab(container, "🔌 Interfaces");
    
    // Connect interface signals
    connect(m_interfacesPanel, &CInterfacesPanelWidget::servoAzimuthChanged, 
            this, [](double az) {
        qDebug() << "Servo azimuth changed to:" << az;
    });
    connect(m_interfacesPanel, &CInterfacesPanelWidget::servoElevationChanged, 
            this, [](double el) {
        qDebug() << "Servo elevation changed to:" << el;
    });
}

void CControlsWindow::setupAnalyticsWidget()
{
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_analyticsWidget = new CAnalyticsWidget(this);
    QWidget *analyticsContent = m_analyticsWidget->widget();
    layout->addWidget(analyticsContent);
    
    m_tabWidget->addTab(container, "📊 Analytics");
}

void CControlsWindow::setupSimulationWidget()
{
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_simulationWidget = new CSimulationWidget(this);
    QWidget *simulationContent = m_simulationWidget->widget();
    layout->addWidget(simulationContent);
    
    m_tabWidget->addTab(container, "🎮 Simulation");
    
    // Connect simulation signal to data warehouse
    connect(m_simulationWidget, &CSimulationWidget::simulatedTrackData,
            CDataWarehouse::getInstance(), &CDataWarehouse::slotUpdateTrackData);
}

void CControlsWindow::setupRecordingWidget()
{
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_recordingWidget = new CRecordingWidget(this);
    QWidget *recordingContent = m_recordingWidget->widget();
    layout->addWidget(recordingContent);
    
    m_tabWidget->addTab(container, "⏺️ Recording");
    
    // Connect replay signal to data warehouse
    connect(m_recordingWidget, &CRecordingWidget::replayTrackData,
            CDataWarehouse::getInstance(), &CDataWarehouse::slotUpdateTrackData);
}

void CControlsWindow::setupHealthMonitorWidget()
{
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_healthMonitorWidget = new CHealthMonitorWidget(this);
    QWidget *healthContent = m_healthMonitorWidget->widget();
    layout->addWidget(healthContent);
    
    m_tabWidget->addTab(container, "💚 Health Monitor");
}

void CControlsWindow::setupPredictiveMaintenanceWidget()
{
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_predictiveMaintenanceWidget = new CPredictiveMaintenanceWidget(this);
    QWidget *maintenanceContent = m_predictiveMaintenanceWidget->widget();
    layout->addWidget(maintenanceContent);
    
    m_tabWidget->addTab(container, "🔧 Maintenance");
}

void CControlsWindow::setupChartsWidget()
{
    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_chartsWidget = new CChartsWidget(this);
    QWidget *chartsContent = m_chartsWidget->widget();
    layout->addWidget(chartsContent);
    
    m_tabWidget->addTab(container, "📈 Charts");
}

void CControlsWindow::applyLightTheme()
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
        "QTabWidget::pane {"
        "   background-color: #FFFFFF;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 6px;"
        "   top: -2px;"
        "}"
        "QTabBar::tab {"
        "   background-color: #E3F2FD;" // Light blue tabs
        "   color: #1565C0;"
        "   border: 2px solid #90CAF9;"
        "   border-bottom: none;"
        "   border-top-left-radius: 6px;"
        "   border-top-right-radius: 6px;"
        "   padding: 12px 24px;"
        "   margin-right: 4px;"
        "   font-weight: 600;"
        "   font-size: 13px;"
        "}"
        "QTabBar::tab:selected {"
        "   background-color: #FFFFFF;" // White for selected tab
        "   color: #0D47A1;"            // Darker blue text
        "   border-bottom: 2px solid #FFFFFF;" // Hide bottom border for selected
        "}"
        "QTabBar::tab:hover:!selected {"
        "   background-color: #BBDEFB;" // Slightly darker blue on hover
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
        "QGroupBox {"
        "   background-color: #FFFFFF;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 6px;"
        "   margin-top: 12px;"
        "   padding-top: 12px;"
        "   font-weight: bold;"
        "   color: #1565C0;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top left;"
        "   padding: 4px 12px;"
        "   background-color: #E3F2FD;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 4px;"
        "   color: #0D47A1;"
        "   font-weight: bold;"
        "}"
        "QLabel {"
        "   color: #1565C0;"
        "   background-color: transparent;"
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
        "QSpinBox, QDoubleSpinBox {"
        "   background-color: #FFFFFF;"
        "   color: #1565C0;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 4px;"
        "   padding: 6px;"
        "}"
        "QSpinBox:focus, QDoubleSpinBox:focus {"
        "   border: 2px solid #42A5F5;"
        "}"
        "QSlider::groove:horizontal {"
        "   background: #E3F2FD;"
        "   height: 8px;"
        "   border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "   background: #1565C0;"
        "   border: 2px solid #90CAF9;"
        "   width: 18px;"
        "   margin: -5px 0;"
        "   border-radius: 9px;"
        "}"
        "QSlider::handle:horizontal:hover {"
        "   background: #0D47A1;"
        "   border: 2px solid #64B5F6;"
        "}"
        "QCheckBox {"
        "   color: #1565C0;"
        "   spacing: 8px;"
        "}"
        "QCheckBox::indicator {"
        "   width: 18px;"
        "   height: 18px;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 4px;"
        "   background-color: #FFFFFF;"
        "}"
        "QCheckBox::indicator:checked {"
        "   background-color: #1565C0;"
        "   border: 2px solid #1565C0;"
        "}"
        "QCheckBox::indicator:hover {"
        "   border: 2px solid #64B5F6;"
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
        "QComboBox QAbstractItemView {"
        "   background-color: #FFFFFF;"
        "   color: #1565C0;"
        "   selection-background-color: #E3F2FD;"
        "   selection-color: #0D47A1;"
        "   border: 2px solid #90CAF9;"
        "}"
        "QStatusBar {"
        "   background-color: #E3F2FD;" // Light blue status bar
        "   color: #1565C0;"
        "   border-top: 2px solid #90CAF9;"
        "   font-size: 11px;"
        "   padding: 6px;"
        "   font-weight: 500;"
        "}"
        "QTableWidget {"
        "   background-color: #FFFFFF;"
        "   alternate-background-color: #F5FBFE;"
        "   color: #1565C0;"
        "   gridline-color: #E3F2FD;"
        "   border: 2px solid #90CAF9;"
        "   border-radius: 4px;"
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
        "QScrollBar:vertical {"
        "   background: #E3F2FD;"
        "   width: 14px;"
        "   border-radius: 7px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #90CAF9;"
        "   border-radius: 7px;"
        "   min-height: 30px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "   background: #64B5F6;"
        "}"
        "QScrollBar:horizontal {"
        "   background: #E3F2FD;"
        "   height: 14px;"
        "   border-radius: 7px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "   background: #90CAF9;"
        "   border-radius: 7px;"
        "   min-width: 30px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "   background: #64B5F6;"
        "}";
    
    setStyleSheet(lightTheme);
}

void CControlsWindow::onCurrentTabChanged(int index)
{
    QString tabName = m_tabWidget->tabText(index);
    statusBar()->showMessage("Switched to: " + tabName, 2000);
}

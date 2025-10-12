#include "cpredictivemaintenancewidget.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QSplitter>
#include <QDebug>
#include <QtMath>

CPredictiveMaintenanceWidget::CPredictiveMaintenanceWidget(QWidget *parent)
    : QDockWidget("Predictive Maintenance", parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_predictionTimer(new QTimer(this))
    , m_autoUpdate(true)
{
    setupUI();
    applyModernTheme();
    initializeMaintenanceItems();
    
    // Connect timer
    connect(m_predictionTimer, &QTimer::timeout, this, &CPredictiveMaintenanceWidget::onPredictionTimer);
    
    // Start predictions
    m_predictionTimer->start(UPDATE_INTERVAL);
    
    updateMaintenanceTable();
    updateMaintenanceCalendar();
}

CPredictiveMaintenanceWidget::~CPredictiveMaintenanceWidget()
{
    m_predictionTimer->stop();
}

void CPredictiveMaintenanceWidget::setupUI()
{
    m_centralWidget = new QWidget();
    setWidget(m_centralWidget);
    
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    
    // Create main splitter
    m_mainSplitter = new QSplitter(Qt::Horizontal);
    m_mainLayout->addWidget(m_mainSplitter);
    
    // Left Panel
    m_leftPanel = new QWidget();
    m_leftLayout = new QVBoxLayout(m_leftPanel);
    m_leftLayout->setSpacing(8);
    m_leftLayout->setContentsMargins(5, 5, 5, 5);
    
    // Control Group
    m_controlGroup = new QGroupBox("Control");
    QHBoxLayout *controlLayout = new QHBoxLayout(m_controlGroup);
    
    m_refreshButton = new QPushButton("🔄 Refresh");
    m_scheduleButton = new QPushButton("📅 Schedule");
    m_completeButton = new QPushButton("✅ Complete");
    m_exportButton = new QPushButton("📊 Export");
    m_autoUpdateCheck = new QCheckBox("Auto Update");
    m_autoUpdateCheck->setChecked(true);
    
    controlLayout->addWidget(m_refreshButton);
    controlLayout->addWidget(m_scheduleButton);
    controlLayout->addWidget(m_completeButton);
    controlLayout->addWidget(m_exportButton);
    controlLayout->addWidget(m_autoUpdateCheck);
    controlLayout->addStretch();
    
    // Filter Group
    m_filterGroup = new QGroupBox("Filters");
    QGridLayout *filterLayout = new QGridLayout(m_filterGroup);
    
    filterLayout->addWidget(new QLabel("Status:"), 0, 0);
    m_statusFilter = new QComboBox();
    m_statusFilter->addItems({"All", "Optimal", "Good", "Attention", "Urgent", "Critical"});
    filterLayout->addWidget(m_statusFilter, 0, 1);
    
    filterLayout->addWidget(new QLabel("Priority:"), 0, 2);
    m_priorityFilter = new QComboBox();
    m_priorityFilter->addItems({"All", "Low", "Medium", "High", "Critical"});
    filterLayout->addWidget(m_priorityFilter, 0, 3);
    
    filterLayout->addWidget(new QLabel("Category:"), 1, 0);
    m_categoryFilter = new QComboBox();
    m_categoryFilter->addItems({"All", "Hardware", "Software", "Sensors", "Mechanical"});
    filterLayout->addWidget(m_categoryFilter, 1, 1, 1, 3);
    
    // Overview Group
    m_overviewGroup = new QGroupBox("System Overview");
    QGridLayout *overviewLayout = new QGridLayout(m_overviewGroup);
    
    m_totalItemsLabel = new QLabel("Total Items: 0");
    m_urgentItemsLabel = new QLabel("Urgent Items: 0");
    m_upcomingLabel = new QLabel("Upcoming (7 days): 0");
    overviewLayout->addWidget(m_totalItemsLabel, 0, 0);
    overviewLayout->addWidget(m_urgentItemsLabel, 0, 1);
    overviewLayout->addWidget(m_upcomingLabel, 1, 0, 1, 2);
    
    overviewLayout->addWidget(new QLabel("System Reliability:"), 2, 0);
    m_systemReliabilityBar = new QProgressBar();
    m_systemReliabilityBar->setRange(0, 100);
    m_systemReliabilityBar->setValue(87);
    overviewLayout->addWidget(m_systemReliabilityBar, 2, 1);
    
    // Maintenance Table
    m_tableGroup = new QGroupBox("Maintenance Schedule");
    QVBoxLayout *tableLayout = new QVBoxLayout(m_tableGroup);
    
    m_maintenanceTable = new QTableWidget();
    m_maintenanceTable->setColumnCount(7);
    m_maintenanceTable->setHorizontalHeaderLabels({
        "Component", "Status", "Priority", "Next Maintenance", "Operating Hours", "Wear Level", "Reliability"
    });
    m_maintenanceTable->horizontalHeader()->setStretchLastSection(true);
    m_maintenanceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_maintenanceTable->setAlternatingRowColors(true);
    m_maintenanceTable->setSortingEnabled(true);
    tableLayout->addWidget(m_maintenanceTable);
    
    // Add groups to left layout
    m_leftLayout->addWidget(m_controlGroup);
    m_leftLayout->addWidget(m_filterGroup);
    m_leftLayout->addWidget(m_overviewGroup);
    m_leftLayout->addWidget(m_tableGroup);
    
    // Right Panel
    m_rightPanel = new QWidget();
    m_rightLayout = new QVBoxLayout(m_rightPanel);
    m_rightLayout->setSpacing(8);
    m_rightLayout->setContentsMargins(5, 5, 5, 5);
    
    // Details Group
    m_detailsGroup = new QGroupBox("Component Details");
    QGridLayout *detailsLayout = new QGridLayout(m_detailsGroup);
    
    m_selectedComponentLabel = new QLabel("Select a component for details");
    m_selectedComponentLabel->setStyleSheet("font-weight: bold; font-size: 12px;");
    detailsLayout->addWidget(m_selectedComponentLabel, 0, 0, 1, 2);
    
    m_statusLabel = new QLabel("Status: N/A");
    m_priorityLabel = new QLabel("Priority: N/A");
    detailsLayout->addWidget(m_statusLabel, 1, 0);
    detailsLayout->addWidget(m_priorityLabel, 1, 1);
    
    m_nextMaintenanceLabel = new QLabel("Next Maintenance: N/A");
    m_operatingHoursLabel = new QLabel("Operating Hours: N/A");
    detailsLayout->addWidget(m_nextMaintenanceLabel, 2, 0);
    detailsLayout->addWidget(m_operatingHoursLabel, 2, 1);
    
    detailsLayout->addWidget(new QLabel("Wear Level:"), 3, 0);
    m_wearLevelBar = new QProgressBar();
    m_wearLevelBar->setRange(0, 100);
    detailsLayout->addWidget(m_wearLevelBar, 3, 1);
    
    detailsLayout->addWidget(new QLabel("Reliability:"), 4, 0);
    m_reliabilityBar = new QProgressBar();
    m_reliabilityBar->setRange(0, 100);
    detailsLayout->addWidget(m_reliabilityBar, 4, 1);
    
    detailsLayout->addWidget(new QLabel("Description:"), 5, 0, 1, 2);
    m_descriptionText = new QTextEdit();
    m_descriptionText->setMaximumHeight(60);
    m_descriptionText->setReadOnly(true);
    detailsLayout->addWidget(m_descriptionText, 6, 0, 1, 2);
    
    detailsLayout->addWidget(new QLabel("Recommendations:"), 7, 0, 1, 2);
    m_recommendationsText = new QTextEdit();
    m_recommendationsText->setMaximumHeight(80);
    m_recommendationsText->setReadOnly(true);
    detailsLayout->addWidget(m_recommendationsText, 8, 0, 1, 2);
    
    // Calendar Group
    m_calendarGroup = new QGroupBox("Maintenance Calendar");
    QVBoxLayout *calendarLayout = new QVBoxLayout(m_calendarGroup);
    
    m_calendar = new QCalendarWidget();
    m_calendar->setMaximumHeight(200);
    calendarLayout->addWidget(m_calendar);
    
    // Log Group
    m_logGroup = new QGroupBox("Maintenance Log");
    QVBoxLayout *logLayout = new QVBoxLayout(m_logGroup);
    
    m_logText = new QTextEdit();
    m_logText->setMaximumHeight(120);
    m_logText->setReadOnly(true);
    logLayout->addWidget(m_logText);
    
    // Add groups to right layout
    m_rightLayout->addWidget(m_detailsGroup);
    m_rightLayout->addWidget(m_calendarGroup);
    m_rightLayout->addWidget(m_logGroup);
    
    // Add panels to splitter
    m_mainSplitter->addWidget(m_leftPanel);
    m_mainSplitter->addWidget(m_rightPanel);
    m_mainSplitter->setSizes({600, 400});
    
    // Connect signals
    connect(m_refreshButton, &QPushButton::clicked, this, &CPredictiveMaintenanceWidget::onRefreshData);
    connect(m_scheduleButton, &QPushButton::clicked, this, &CPredictiveMaintenanceWidget::onScheduleMaintenance);
    connect(m_completeButton, &QPushButton::clicked, this, &CPredictiveMaintenanceWidget::onCompleteMaintenance);
    connect(m_exportButton, &QPushButton::clicked, this, &CPredictiveMaintenanceWidget::onExportSchedule);
    connect(m_autoUpdateCheck, &QCheckBox::toggled, this, &CPredictiveMaintenanceWidget::onAutoUpdateToggled);
    
    connect(m_statusFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CPredictiveMaintenanceWidget::onFilterChanged);
    connect(m_priorityFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CPredictiveMaintenanceWidget::onFilterChanged);
    connect(m_categoryFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CPredictiveMaintenanceWidget::onFilterChanged);
    
    connect(m_maintenanceTable, &QTableWidget::itemSelectionChanged, this, &CPredictiveMaintenanceWidget::onMaintenanceItemSelected);
    connect(m_calendar, &QCalendarWidget::selectionChanged, this, &CPredictiveMaintenanceWidget::onCalendarDateSelected);
    
    // Initial button states
    m_scheduleButton->setEnabled(false);
    m_completeButton->setEnabled(false);
}

void CPredictiveMaintenanceWidget::applyModernTheme()
{
    setStyleSheet(R"(
        QDockWidget {
            background-color: #1e1e2e;
            color: #cdd6f4;
            border: 1px solid #45475a;
        }
        
        QDockWidget::title {
            background-color: #313244;
            color: #f38ba8;
            padding: 8px;
            font-weight: bold;
            font-size: 12px;
        }
        
        QGroupBox {
            font-weight: bold;
            border: 2px solid #45475a;
            border-radius: 8px;
            margin-top: 8px;
            padding-top: 8px;
            background-color: #181825;
        }
        
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 8px;
            padding: 0 6px 0 6px;
            color: #89b4fa;
            font-size: 10px;
        }
        
        QPushButton {
            background-color: #45475a;
            border: 1px solid #6c7086;
            border-radius: 6px;
            color: #cdd6f4;
            font-weight: bold;
            padding: 6px 12px;
            min-width: 70px;
        }
        
        QPushButton:hover {
            background-color: #585b70;
            border-color: #89b4fa;
        }
        
        QPushButton:pressed {
            background-color: #313244;
        }
        
        QPushButton:disabled {
            background-color: #313244;
            color: #6c7086;
            border-color: #45475a;
        }
        
        QComboBox {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 4px;
            padding: 4px 8px;
            color: #cdd6f4;
            min-width: 80px;
        }
        
        QComboBox:focus {
            border-color: #89b4fa;
        }
        
        QCheckBox {
            color: #cdd6f4;
            spacing: 6px;
        }
        
        QCheckBox::indicator {
            width: 14px;
            height: 14px;
            border: 1px solid #45475a;
            border-radius: 3px;
            background-color: #313244;
        }
        
        QCheckBox::indicator:checked {
            background-color: #a6e3a1;
            border-color: #40a02b;
        }
        
        QProgressBar {
            border: 1px solid #45475a;
            border-radius: 4px;
            text-align: center;
            background-color: #313244;
            color: #cdd6f4;
            font-weight: bold;
            min-height: 18px;
        }
        
        QProgressBar::chunk {
            border-radius: 3px;
        }
        
        QTableWidget {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 4px;
            color: #cdd6f4;
            alternate-background-color: #383a59;
            gridline-color: #45475a;
        }
        
        QTableWidget::item {
            padding: 6px;
            border-bottom: 1px solid #45475a;
        }
        
        QTableWidget::item:selected {
            background-color: #89b4fa;
            color: #1e1e2e;
        }
        
        QTableWidget::item:hover {
            background-color: #585b70;
        }
        
        QHeaderView::section {
            background-color: #45475a;
            color: #cdd6f4;
            padding: 6px;
            border: none;
            border-right: 1px solid #6c7086;
            font-weight: bold;
            font-size: 9px;
        }
        
        QTextEdit {
            background-color: #181825;
            border: 1px solid #45475a;
            border-radius: 4px;
            color: #cdd6f4;
            font-family: 'Consolas', 'Monaco', monospace;
            font-size: 9px;
        }
        
        QCalendarWidget {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 4px;
        }
        
        QCalendarWidget QToolButton {
            background-color: #45475a;
            color: #cdd6f4;
            border: none;
            padding: 4px;
        }
        
        QCalendarWidget QToolButton:hover {
            background-color: #585b70;
        }
        
        QCalendarWidget QAbstractItemView {
            background-color: #313244;
            color: #cdd6f4;
            selection-background-color: #89b4fa;
            selection-color: #1e1e2e;
        }
        
        QLabel {
            color: #cdd6f4;
            font-size: 10px;
        }
        
        QSplitter::handle {
            background-color: #45475a;
            width: 3px;
        }
        
        QSplitter::handle:hover {
            background-color: #89b4fa;
        }
    )");
}

void CPredictiveMaintenanceWidget::initializeMaintenanceItems()
{
    m_categories = {"Hardware", "Software", "Sensors", "Mechanical"};
    
    // Initialize maintenance items with realistic data
    QDateTime now = QDateTime::currentDateTime();
    
    // Hardware components
    m_maintenanceItems["Radar Transmitter"] = {
        "Radar Transmitter", "Hardware", MAINTENANCE_GOOD, PRIORITY_HIGH,
        now.addDays(15), now.addDays(-45), 2880, 2000, 45.0, 92.0,
        "High-power radar transmission system requiring regular calibration",
        "Check power output levels, inspect cooling system, verify frequency stability",
        {now.addDays(-180), now.addDays(-90), now.addDays(-45)}
    };
    
    m_maintenanceItems["Antenna Array"] = {
        "Antenna Array", "Hardware", MAINTENANCE_ATTENTION, PRIORITY_MEDIUM,
        now.addDays(7), now.addDays(-30), 4320, 1500, 62.0, 88.0,
        "Phased array antenna system for radar beam forming",
        "Inspect antenna elements, check phase alignment, clean surfaces",
        {now.addDays(-120), now.addDays(-60), now.addDays(-30)}
    };
    
    m_maintenanceItems["Power Supply Unit"] = {
        "Power Supply Unit", "Hardware", MAINTENANCE_OPTIMAL, PRIORITY_LOW,
        now.addDays(45), now.addDays(-15), 1440, 3000, 25.0, 96.0,
        "Primary power distribution and conditioning system",
        "Monitor voltage regulation, check thermal performance, test backup systems",
        {now.addDays(-90), now.addDays(-45), now.addDays(-15)}
    };
    
    m_maintenanceItems["Cooling System"] = {
        "Cooling System", "Mechanical", MAINTENANCE_URGENT, PRIORITY_CRITICAL,
        now.addDays(2), now.addDays(-60), 5760, 1000, 78.0, 75.0,
        "Liquid cooling system for high-power components",
        "URGENT: Replace coolant, inspect pumps, check for leaks, clean heat exchangers",
        {now.addDays(-150), now.addDays(-90), now.addDays(-60)}
    };
    
    // Software components
    m_maintenanceItems["Signal Processing"] = {
        "Signal Processing", "Software", MAINTENANCE_GOOD, PRIORITY_MEDIUM,
        now.addDays(30), now.addDays(-60), 0, 90, 35.0, 94.0,
        "Real-time radar signal processing algorithms",
        "Update algorithms, optimize performance, validate accuracy",
        {now.addDays(-180), now.addDays(-120), now.addDays(-60)}
    };
    
    m_maintenanceItems["Display Software"] = {
        "Display Software", "Software", MAINTENANCE_OPTIMAL, PRIORITY_LOW,
        now.addDays(60), now.addDays(-30), 0, 120, 18.0, 98.0,
        "User interface and display rendering system",
        "Update UI components, check performance metrics, backup configurations",
        {now.addDays(-150), now.addDays(-90), now.addDays(-30)}
    };
    
    m_maintenanceItems["Database System"] = {
        "Database System", "Software", MAINTENANCE_ATTENTION, PRIORITY_MEDIUM,
        now.addDays(10), now.addDays(-20), 0, 60, 55.0, 89.0,
        "Track data storage and retrieval system",
        "Optimize database, backup data, check integrity, update indexes",
        {now.addDays(-120), now.addDays(-60), now.addDays(-20)}
    };
    
    // Sensor components
    m_maintenanceItems["GPS Receiver"] = {
        "GPS Receiver", "Sensors", MAINTENANCE_GOOD, PRIORITY_LOW,
        now.addDays(90), now.addDays(-180), 8760, 4000, 22.0, 97.0,
        "Global positioning system receiver for location reference",
        "Update almanac data, check signal quality, verify accuracy",
        {now.addDays(-360), now.addDays(-180)}
    };
    
    m_maintenanceItems["Environmental Sensors"] = {
        "Environmental Sensors", "Sensors", MAINTENANCE_CRITICAL, PRIORITY_CRITICAL,
        now.addDays(1), now.addDays(-90), 2160, 500, 89.0, 65.0,
        "Temperature, humidity, and pressure monitoring sensors",
        "CRITICAL: Calibrate sensors immediately, replace faulty units, update firmware",
        {now.addDays(-270), now.addDays(-180), now.addDays(-90)}
    };
    
    // Mechanical components
    m_maintenanceItems["Servo Motors"] = {
        "Servo Motors", "Mechanical", MAINTENANCE_ATTENTION, PRIORITY_HIGH,
        now.addDays(5), now.addDays(-120), 3600, 2000, 68.0, 82.0,
        "Antenna positioning servo motor systems",
        "Lubricate bearings, check encoder accuracy, test positioning limits",
        {now.addDays(-240), now.addDays(-120)}
    };
    
    addMaintenanceLog("System", "Predictive maintenance system initialized");
}

void CPredictiveMaintenanceWidget::onRefreshData()
{
    updatePredictions();
    updateMaintenanceTable();
    updateMaintenanceCalendar();
    addMaintenanceLog("System", "Manual data refresh completed");
}

void CPredictiveMaintenanceWidget::onScheduleMaintenance()
{
    if (m_selectedComponent.isEmpty()) return;
    
    if (m_maintenanceItems.contains(m_selectedComponent)) {
        MaintenanceItem &item = m_maintenanceItems[m_selectedComponent];
        
        // Simple scheduling - move next maintenance forward by 7 days
        item.nextMaintenance = item.nextMaintenance.addDays(7);
        
        addMaintenanceLog(m_selectedComponent, "Maintenance rescheduled");
        updateMaintenanceTable();
        updateMaintenanceCalendar();
        onMaintenanceItemSelected(); // Refresh details
    }
}

void CPredictiveMaintenanceWidget::onCompleteMaintenance()
{
    if (m_selectedComponent.isEmpty()) return;
    
    if (m_maintenanceItems.contains(m_selectedComponent)) {
        MaintenanceItem &item = m_maintenanceItems[m_selectedComponent];
        
        // Mark maintenance as completed
        item.lastMaintenance = QDateTime::currentDateTime();
        item.nextMaintenance = QDateTime::currentDateTime().addDays(item.maintenanceInterval);
        item.maintenanceHistory.append(item.lastMaintenance);
        
        // Improve component condition
        item.wearLevel = qMax(0.0, item.wearLevel - 30.0);
        item.reliability = qMin(100.0, item.reliability + 10.0);
        item.operatingHours = 0; // Reset operating hours
        
        // Update status based on new condition
        if (item.wearLevel < 20) {
            item.status = MAINTENANCE_OPTIMAL;
            item.priority = PRIORITY_LOW;
        } else if (item.wearLevel < 40) {
            item.status = MAINTENANCE_GOOD;
            item.priority = PRIORITY_LOW;
        } else {
            item.status = MAINTENANCE_ATTENTION;
            item.priority = PRIORITY_MEDIUM;
        }
        
        addMaintenanceLog(m_selectedComponent, "Maintenance completed successfully");
        updateMaintenanceTable();
        updateMaintenanceCalendar();
        onMaintenanceItemSelected(); // Refresh details
    }
}

void CPredictiveMaintenanceWidget::onExportSchedule()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Maintenance Schedule", 
                                                   QString("maintenance_schedule_%1.csv").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")),
                                                   "CSV Files (*.csv)");
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            
            // CSV Header
            out << "Component,Category,Status,Priority,Next Maintenance,Last Maintenance,Operating Hours,Wear Level,Reliability,Description\n";
            
            // Data rows
            for (auto it = m_maintenanceItems.constBegin(); it != m_maintenanceItems.constEnd(); ++it) {
                const MaintenanceItem &item = it.value();
                out << QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,\"%10\"\n")
                       .arg(item.component)
                       .arg(item.category)
                       .arg(getStatusText(item.status))
                       .arg(getPriorityText(item.priority))
                       .arg(item.nextMaintenance.toString("yyyy-MM-dd"))
                       .arg(item.lastMaintenance.toString("yyyy-MM-dd"))
                       .arg(item.operatingHours)
                       .arg(item.wearLevel, 0, 'f', 1)
                       .arg(item.reliability, 0, 'f', 1)
                       .arg(item.description);
            }
            
            file.close();
            addMaintenanceLog("System", QString("Schedule exported to %1").arg(fileName));
        }
    }
}

void CPredictiveMaintenanceWidget::onPredictionTimer()
{
    if (m_autoUpdate) {
        updatePredictions();
        updateMaintenanceTable();
    }
}

void CPredictiveMaintenanceWidget::onFilterChanged()
{
    updateMaintenanceTable();
}

void CPredictiveMaintenanceWidget::onMaintenanceItemSelected()
{
    int currentRow = m_maintenanceTable->currentRow();
    if (currentRow < 0) {
        m_selectedComponent.clear();
        m_selectedComponentLabel->setText("Select a component for details");
        m_statusLabel->setText("Status: N/A");
        m_priorityLabel->setText("Priority: N/A");
        m_nextMaintenanceLabel->setText("Next Maintenance: N/A");
        m_operatingHoursLabel->setText("Operating Hours: N/A");
        m_wearLevelBar->setValue(0);
        m_reliabilityBar->setValue(0);
        m_descriptionText->clear();
        m_recommendationsText->clear();
        
        m_scheduleButton->setEnabled(false);
        m_completeButton->setEnabled(false);
        return;
    }
    
    QTableWidgetItem *item = m_maintenanceTable->item(currentRow, 0);
    if (!item) return;
    
    m_selectedComponent = item->text();
    
    if (m_maintenanceItems.contains(m_selectedComponent)) {
        const MaintenanceItem &comp = m_maintenanceItems[m_selectedComponent];
        
        m_selectedComponentLabel->setText(comp.component);
        m_statusLabel->setText(QString("Status: %1").arg(getStatusText(comp.status)));
        m_priorityLabel->setText(QString("Priority: %1").arg(getPriorityText(comp.priority)));
        m_nextMaintenanceLabel->setText(QString("Next: %1").arg(comp.nextMaintenance.toString("yyyy-MM-dd")));
        m_operatingHoursLabel->setText(QString("Hours: %1").arg(comp.operatingHours));
        
        m_wearLevelBar->setValue(static_cast<int>(comp.wearLevel));
        m_reliabilityBar->setValue(static_cast<int>(comp.reliability));
        
        // Set progress bar colors based on values
        QString wearColor = comp.wearLevel > 70 ? "background-color: #f38ba8;" : 
                           comp.wearLevel > 40 ? "background-color: #f9e2af;" : 
                           "background-color: #a6e3a1;";
        m_wearLevelBar->setStyleSheet(QString("QProgressBar::chunk { %1 border-radius: 3px; }").arg(wearColor));
        
        QString reliabilityColor = comp.reliability > 90 ? "background-color: #a6e3a1;" :
                                  comp.reliability > 70 ? "background-color: #f9e2af;" :
                                  "background-color: #f38ba8;";
        m_reliabilityBar->setStyleSheet(QString("QProgressBar::chunk { %1 border-radius: 3px; }").arg(reliabilityColor));
        
        m_descriptionText->setText(comp.description);
        m_recommendationsText->setText(comp.recommendations);
        
        m_scheduleButton->setEnabled(true);
        m_completeButton->setEnabled(true);
    }
}

void CPredictiveMaintenanceWidget::onAutoUpdateToggled(bool enabled)
{
    m_autoUpdate = enabled;
    if (enabled) {
        m_predictionTimer->start(UPDATE_INTERVAL);
        addMaintenanceLog("System", "Auto-update enabled");
    } else {
        m_predictionTimer->stop();
        addMaintenanceLog("System", "Auto-update disabled");
    }
}

void CPredictiveMaintenanceWidget::onCalendarDateSelected(const QDate &date)
{
    // Show maintenance items scheduled for the selected date
    QDateTime selectedDateTime = QDateTime(date);
    QStringList scheduledItems;
    
    for (auto it = m_maintenanceItems.constBegin(); it != m_maintenanceItems.constEnd(); ++it) {
        if (it.value().nextMaintenance.date() == date) {
            scheduledItems.append(it.value().component);
        }
    }
    
    if (!scheduledItems.isEmpty()) {
        addMaintenanceLog("Calendar", QString("Selected date has %1 scheduled maintenance(s): %2")
                          .arg(scheduledItems.size())
                          .arg(scheduledItems.join(", ")));
    }
}

void CPredictiveMaintenanceWidget::updateMaintenanceTable()
{
    // Apply filters
    QString statusFilter = m_statusFilter->currentText();
    QString priorityFilter = m_priorityFilter->currentText();
    QString categoryFilter = m_categoryFilter->currentText();
    
    QList<MaintenanceItem> filteredItems;
    for (auto it = m_maintenanceItems.constBegin(); it != m_maintenanceItems.constEnd(); ++it) {
        const MaintenanceItem &item = it.value();
        
        bool statusMatch = (statusFilter == "All" || getStatusText(item.status) == statusFilter);
        bool priorityMatch = (priorityFilter == "All" || getPriorityText(item.priority) == priorityFilter);
        bool categoryMatch = (categoryFilter == "All" || item.category == categoryFilter);
        
        if (statusMatch && priorityMatch && categoryMatch) {
            filteredItems.append(item);
        }
    }
    
    // Update table
    m_maintenanceTable->setRowCount(filteredItems.size());
    
    for (int i = 0; i < filteredItems.size(); ++i) {
        const MaintenanceItem &item = filteredItems[i];
        
        m_maintenanceTable->setItem(i, 0, new QTableWidgetItem(item.component));
        
        QTableWidgetItem *statusItem = new QTableWidgetItem(getStatusText(item.status));
        statusItem->setForeground(QBrush(getStatusColor(item.status)));
        m_maintenanceTable->setItem(i, 1, statusItem);
        
        QTableWidgetItem *priorityItem = new QTableWidgetItem(getPriorityText(item.priority));
        priorityItem->setForeground(QBrush(getPriorityColor(item.priority)));
        m_maintenanceTable->setItem(i, 2, priorityItem);
        
        m_maintenanceTable->setItem(i, 3, new QTableWidgetItem(item.nextMaintenance.toString("yyyy-MM-dd")));
        m_maintenanceTable->setItem(i, 4, new QTableWidgetItem(QString::number(item.operatingHours)));
        m_maintenanceTable->setItem(i, 5, new QTableWidgetItem(QString("%1%").arg(item.wearLevel, 0, 'f', 1)));
        m_maintenanceTable->setItem(i, 6, new QTableWidgetItem(QString("%1%").arg(item.reliability, 0, 'f', 1)));
    }
    
    // Update overview
    int totalItems = m_maintenanceItems.size();
    int urgentItems = 0;
    int upcomingItems = 0;
    double totalReliability = 0.0;
    
    QDateTime now = QDateTime::currentDateTime();
    QDateTime weekFromNow = now.addDays(7);
    
    for (auto it = m_maintenanceItems.constBegin(); it != m_maintenanceItems.constEnd(); ++it) {
        const MaintenanceItem &item = it.value();
        
        if (item.status == MAINTENANCE_URGENT || item.status == MAINTENANCE_CRITICAL) {
            urgentItems++;
        }
        
        if (item.nextMaintenance <= weekFromNow) {
            upcomingItems++;
        }
        
        totalReliability += item.reliability;
    }
    
    m_totalItemsLabel->setText(QString("Total Items: %1").arg(totalItems));
    m_urgentItemsLabel->setText(QString("Urgent Items: %1").arg(urgentItems));
    m_upcomingLabel->setText(QString("Upcoming (7 days): %1").arg(upcomingItems));
    
    int avgReliability = totalItems > 0 ? static_cast<int>(totalReliability / totalItems) : 0;
    m_systemReliabilityBar->setValue(avgReliability);
    
    QString reliabilityColor = avgReliability > 90 ? "background-color: #a6e3a1;" :
                              avgReliability > 70 ? "background-color: #f9e2af;" :
                              "background-color: #f38ba8;";
    m_systemReliabilityBar->setStyleSheet(QString("QProgressBar::chunk { %1 border-radius: 3px; }").arg(reliabilityColor));
    
    // Resize columns
    for (int i = 0; i < m_maintenanceTable->columnCount(); ++i) {
        m_maintenanceTable->resizeColumnToContents(i);
    }
}

void CPredictiveMaintenanceWidget::updatePredictions()
{
    calculatePredictions();
}

void CPredictiveMaintenanceWidget::updateMaintenanceCalendar()
{
    // Highlight dates with scheduled maintenance
    QTextCharFormat format;
    format.setBackground(QBrush(QColor("#89b4fa")));
    format.setForeground(QBrush(QColor("#1e1e2e")));
    
    for (auto it = m_maintenanceItems.constBegin(); it != m_maintenanceItems.constEnd(); ++it) {
        const MaintenanceItem &item = it.value();
        m_calendar->setDateTextFormat(item.nextMaintenance.date(), format);
    }
}

void CPredictiveMaintenanceWidget::calculatePredictions()
{
    // Simulate predictive analytics
    for (auto it = m_maintenanceItems.begin(); it != m_maintenanceItems.end(); ++it) {
        MaintenanceItem &item = it.value();
        
        // Simulate operating hours increase
        item.operatingHours += QRandomGenerator::global()->bounded(1, 5);
        
        // Calculate wear based on operating hours
        double hourlyWear = 100.0 / item.maintenanceInterval;
        item.wearLevel = qMin(100.0, (item.operatingHours * hourlyWear));
        
        // Calculate reliability based on wear and time since last maintenance
        QDateTime now = QDateTime::currentDateTime();
        int daysSinceLastMaintenance = item.lastMaintenance.daysTo(now);
        double timeDecay = qMin(20.0, daysSinceLastMaintenance * 0.1);
        item.reliability = qMax(50.0, 100.0 - item.wearLevel * 0.5 - timeDecay);
        
        // Update status and priority based on predictions
        MaintenanceStatus oldStatus = item.status;
        
        int daysUntilMaintenance = now.daysTo(item.nextMaintenance);
        
        if (daysUntilMaintenance <= 0 || item.wearLevel > 90 || item.reliability < 60) {
            item.status = MAINTENANCE_CRITICAL;
            item.priority = PRIORITY_CRITICAL;
        } else if (daysUntilMaintenance <= 3 || item.wearLevel > 75 || item.reliability < 70) {
            item.status = MAINTENANCE_URGENT;
            item.priority = PRIORITY_HIGH;
        } else if (daysUntilMaintenance <= 7 || item.wearLevel > 50 || item.reliability < 85) {
            item.status = MAINTENANCE_ATTENTION;
            item.priority = PRIORITY_MEDIUM;
        } else if (item.wearLevel > 30 || item.reliability < 95) {
            item.status = MAINTENANCE_GOOD;
            item.priority = PRIORITY_LOW;
        } else {
            item.status = MAINTENANCE_OPTIMAL;
            item.priority = PRIORITY_LOW;
        }
        
        // Log status changes
        if (oldStatus != item.status) {
            addMaintenanceLog(item.component, QString("Status changed from %1 to %2")
                              .arg(getStatusText(oldStatus))
                              .arg(getStatusText(item.status)));
        }
    }
}

QString CPredictiveMaintenanceWidget::getStatusText(MaintenanceStatus status)
{
    switch (status) {
        case MAINTENANCE_OPTIMAL: return "Optimal";
        case MAINTENANCE_GOOD: return "Good";
        case MAINTENANCE_ATTENTION: return "Attention";
        case MAINTENANCE_URGENT: return "Urgent";
        case MAINTENANCE_CRITICAL: return "Critical";
        default: return "Unknown";
    }
}

QString CPredictiveMaintenanceWidget::getPriorityText(MaintenancePriority priority)
{
    switch (priority) {
        case PRIORITY_LOW: return "Low";
        case PRIORITY_MEDIUM: return "Medium";
        case PRIORITY_HIGH: return "High";
        case PRIORITY_CRITICAL: return "Critical";
        default: return "Unknown";
    }
}

QColor CPredictiveMaintenanceWidget::getStatusColor(MaintenanceStatus status)
{
    switch (status) {
        case MAINTENANCE_OPTIMAL: return QColor("#a6e3a1");   // Green
        case MAINTENANCE_GOOD: return QColor("#89b4fa");      // Blue
        case MAINTENANCE_ATTENTION: return QColor("#f9e2af"); // Yellow
        case MAINTENANCE_URGENT: return QColor("#fab387");    // Orange
        case MAINTENANCE_CRITICAL: return QColor("#f38ba8");  // Red
        default: return QColor("#cdd6f4");                    // White
    }
}

QColor CPredictiveMaintenanceWidget::getPriorityColor(MaintenancePriority priority)
{
    switch (priority) {
        case PRIORITY_LOW: return QColor("#89b4fa");      // Blue
        case PRIORITY_MEDIUM: return QColor("#f9e2af");   // Yellow
        case PRIORITY_HIGH: return QColor("#fab387");     // Orange
        case PRIORITY_CRITICAL: return QColor("#f38ba8"); // Red
        default: return QColor("#cdd6f4");                // White
    }
}

void CPredictiveMaintenanceWidget::addMaintenanceLog(const QString& component, const QString& action)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString logEntry = QString("[%1] %2: %3").arg(timestamp, component, action);
    
    m_recentLogs.prepend(logEntry);
    if (m_recentLogs.size() > MAX_LOG_ENTRIES) {
        m_recentLogs.removeLast();
    }
    
    m_logText->clear();
    for (const QString &log : m_recentLogs) {
        m_logText->append(log);
    }
}
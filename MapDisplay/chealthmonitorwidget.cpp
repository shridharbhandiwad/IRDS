#include "chealthmonitorwidget.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>
#include <QCheckBox>
#include <QDebug>
#include <QtMath>

CHealthMonitorWidget::CHealthMonitorWidget(QWidget *parent)
    : QDockWidget("Health Monitor", parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_healthTimer(new QTimer(this))
    , m_autoRefresh(true)
    , m_alertCount(0)
{
    setupUI();
    applyModernTheme();
    initializeComponents();
    
    // Connect timer
    connect(m_healthTimer, &QTimer::timeout, this, &CHealthMonitorWidget::onHealthTimer);
    
    // Start monitoring
    m_healthTimer->start(UPDATE_INTERVAL);
    
    updateHealthStatus();
}

CHealthMonitorWidget::~CHealthMonitorWidget()
{
    m_healthTimer->stop();
}

void CHealthMonitorWidget::setupUI()
{
    m_centralWidget = new QWidget();
    setWidget(m_centralWidget);
    
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(10);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // Control Group
    m_controlGroup = new QGroupBox("Control");
    QHBoxLayout *controlLayout = new QHBoxLayout(m_controlGroup);
    
    m_refreshButton = new QPushButton("🔄 Refresh");
    m_resetAlertsButton = new QPushButton("🔔 Reset Alerts");
    m_exportButton = new QPushButton("📊 Export Report");
    m_autoRefreshCheck = new QCheckBox("Auto Refresh");
    m_autoRefreshCheck->setChecked(true);
    
    controlLayout->addWidget(m_refreshButton);
    controlLayout->addWidget(m_resetAlertsButton);
    controlLayout->addWidget(m_exportButton);
    controlLayout->addWidget(m_autoRefreshCheck);
    controlLayout->addStretch();
    
    // Overview Group
    m_overviewGroup = new QGroupBox("System Overview");
    QGridLayout *overviewLayout = new QGridLayout(m_overviewGroup);
    
    m_systemStatusLabel = new QLabel("System Status: Initializing...");
    m_systemStatusLabel->setStyleSheet("font-weight: bold; font-size: 12px;");
    overviewLayout->addWidget(m_systemStatusLabel, 0, 0, 1, 2);
    
    overviewLayout->addWidget(new QLabel("Overall Health:"), 1, 0);
    m_overallHealthBar = new QProgressBar();
    m_overallHealthBar->setRange(0, 100);
    m_overallHealthBar->setValue(85);
    overviewLayout->addWidget(m_overallHealthBar, 1, 1);
    
    m_lastUpdateLabel = new QLabel("Last Update: Never");
    m_activeAlertsLabel = new QLabel("Active Alerts: 0");
    overviewLayout->addWidget(m_lastUpdateLabel, 2, 0);
    overviewLayout->addWidget(m_activeAlertsLabel, 2, 1);
    
    // Components Tree
    m_componentsGroup = new QGroupBox("System Components");
    QVBoxLayout *componentsLayout = new QVBoxLayout(m_componentsGroup);
    
    m_componentsTree = new QTreeWidget();
    m_componentsTree->setHeaderLabels({"Component", "Status", "Value", "Last Update"});
    m_componentsTree->setMaximumHeight(200);
    m_componentsTree->setRootIsDecorated(true);
    m_componentsTree->setAlternatingRowColors(true);
    componentsLayout->addWidget(m_componentsTree);
    
    // Details Group
    m_detailsGroup = new QGroupBox("Component Details");
    QGridLayout *detailsLayout = new QGridLayout(m_detailsGroup);
    
    m_selectedComponentLabel = new QLabel("Select a component for details");
    m_selectedComponentLabel->setStyleSheet("font-weight: bold;");
    detailsLayout->addWidget(m_selectedComponentLabel, 0, 0, 1, 2);
    
    detailsLayout->addWidget(new QLabel("Health:"), 1, 0);
    m_componentHealthBar = new QProgressBar();
    m_componentHealthBar->setRange(0, 100);
    detailsLayout->addWidget(m_componentHealthBar, 1, 1);
    
    m_componentValueLabel = new QLabel("Value: N/A");
    m_componentStatusLabel = new QLabel("Status: N/A");
    detailsLayout->addWidget(m_componentValueLabel, 2, 0);
    detailsLayout->addWidget(m_componentStatusLabel, 2, 1);
    
    m_componentDescriptionText = new QTextEdit();
    m_componentDescriptionText->setMaximumHeight(60);
    m_componentDescriptionText->setReadOnly(true);
    detailsLayout->addWidget(m_componentDescriptionText, 3, 0, 1, 2);
    
    // Alerts Group
    m_alertsGroup = new QGroupBox("Recent Alerts");
    QVBoxLayout *alertsLayout = new QVBoxLayout(m_alertsGroup);
    
    m_alertsText = new QTextEdit();
    m_alertsText->setMaximumHeight(100);
    m_alertsText->setReadOnly(true);
    alertsLayout->addWidget(m_alertsText);
    
    // Add all groups to main layout
    m_mainLayout->addWidget(m_controlGroup);
    m_mainLayout->addWidget(m_overviewGroup);
    m_mainLayout->addWidget(m_componentsGroup);
    m_mainLayout->addWidget(m_detailsGroup);
    m_mainLayout->addWidget(m_alertsGroup);
    m_mainLayout->addStretch();
    
    // Connect signals
    connect(m_refreshButton, &QPushButton::clicked, this, &CHealthMonitorWidget::onRefreshHealth);
    connect(m_resetAlertsButton, &QPushButton::clicked, this, &CHealthMonitorWidget::onResetAlerts);
    connect(m_exportButton, &QPushButton::clicked, this, &CHealthMonitorWidget::onExportReport);
    connect(m_autoRefreshCheck, &QCheckBox::toggled, this, &CHealthMonitorWidget::onAutoRefreshToggled);
    connect(m_componentsTree, &QTreeWidget::itemSelectionChanged, this, &CHealthMonitorWidget::onComponentSelectionChanged);
}

void CHealthMonitorWidget::applyModernTheme()
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
            margin-top: 10px;
            padding-top: 10px;
            background-color: #181825;
        }
        
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 8px 0 8px;
            color: #89b4fa;
            font-size: 11px;
        }
        
        QPushButton {
            background-color: #45475a;
            border: 1px solid #6c7086;
            border-radius: 6px;
            color: #cdd6f4;
            font-weight: bold;
            padding: 8px 16px;
            min-width: 80px;
        }
        
        QPushButton:hover {
            background-color: #585b70;
            border-color: #89b4fa;
        }
        
        QPushButton:pressed {
            background-color: #313244;
        }
        
        QCheckBox {
            color: #cdd6f4;
            spacing: 8px;
        }
        
        QCheckBox::indicator {
            width: 16px;
            height: 16px;
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
        }
        
        QProgressBar::chunk {
            border-radius: 3px;
        }
        
        QTreeWidget {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 4px;
            color: #cdd6f4;
            alternate-background-color: #383a59;
        }
        
        QTreeWidget::item {
            padding: 4px;
            border-bottom: 1px solid #45475a;
        }
        
        QTreeWidget::item:selected {
            background-color: #89b4fa;
            color: #1e1e2e;
        }
        
        QTreeWidget::item:hover {
            background-color: #585b70;
        }
        
        QHeaderView::section {
            background-color: #45475a;
            color: #cdd6f4;
            padding: 6px;
            border: none;
            border-right: 1px solid #6c7086;
            font-weight: bold;
        }
        
        QTextEdit {
            background-color: #181825;
            border: 1px solid #45475a;
            border-radius: 4px;
            color: #cdd6f4;
            font-family: 'Consolas', 'Monaco', monospace;
            font-size: 9px;
        }
        
        QLabel {
            color: #cdd6f4;
            font-size: 10px;
        }
    )");
}

void CHealthMonitorWidget::initializeComponents()
{
    m_categories = {"Hardware", "Software", "Network", "Storage", "Sensors"};
    
    // Initialize hardware components
    m_components["CPU"] = {"CPU", "Hardware", HEALTH_GOOD, 45.0, 0.0, 100.0, "%", "Central Processing Unit utilization", QDateTime::currentDateTime(), {}};
    m_components["Memory"] = {"Memory", "Hardware", HEALTH_GOOD, 68.0, 0.0, 100.0, "%", "System memory usage", QDateTime::currentDateTime(), {}};
    m_components["GPU"] = {"GPU", "Hardware", HEALTH_EXCELLENT, 32.0, 0.0, 100.0, "%", "Graphics Processing Unit utilization", QDateTime::currentDateTime(), {}};
    m_components["Temperature"] = {"Temperature", "Hardware", HEALTH_GOOD, 65.0, 0.0, 100.0, "°C", "System temperature", QDateTime::currentDateTime(), {}};
    m_components["Power Supply"] = {"Power Supply", "Hardware", HEALTH_EXCELLENT, 87.0, 0.0, 100.0, "%", "Power supply efficiency", QDateTime::currentDateTime(), {}};
    
    // Initialize software components
    m_components["Operating System"] = {"Operating System", "Software", HEALTH_EXCELLENT, 98.0, 0.0, 100.0, "%", "OS health and stability", QDateTime::currentDateTime(), {}};
    m_components["Radar Processing"] = {"Radar Processing", "Software", HEALTH_GOOD, 82.0, 0.0, 100.0, "%", "Radar signal processing module", QDateTime::currentDateTime(), {}};
    m_components["Display Engine"] = {"Display Engine", "Software", HEALTH_GOOD, 76.0, 0.0, 100.0, "%", "Graphics display rendering engine", QDateTime::currentDateTime(), {}};
    m_components["Database"] = {"Database", "Software", HEALTH_EXCELLENT, 94.0, 0.0, 100.0, "%", "Track database system", QDateTime::currentDateTime(), {}};
    
    // Initialize network components
    m_components["Ethernet"] = {"Ethernet", "Network", HEALTH_EXCELLENT, 95.0, 0.0, 100.0, "%", "Primary network interface", QDateTime::currentDateTime(), {}};
    m_components["UDP Receiver"] = {"UDP Receiver", "Network", HEALTH_GOOD, 88.0, 0.0, 100.0, "%", "UDP data reception module", QDateTime::currentDateTime(), {}};
    m_components["Network Latency"] = {"Network Latency", "Network", HEALTH_GOOD, 12.0, 0.0, 100.0, "ms", "Network response time", QDateTime::currentDateTime(), {}};
    
    // Initialize storage components
    m_components["System Disk"] = {"System Disk", "Storage", HEALTH_WARNING, 78.0, 0.0, 100.0, "%", "Primary system storage", QDateTime::currentDateTime(), {}};
    m_components["Data Disk"] = {"Data Disk", "Storage", HEALTH_GOOD, 45.0, 0.0, 100.0, "%", "Data storage partition", QDateTime::currentDateTime(), {}};
    m_components["Log Storage"] = {"Log Storage", "Storage", HEALTH_EXCELLENT, 23.0, 0.0, 100.0, "%", "System log storage", QDateTime::currentDateTime(), {}};
    
    // Initialize sensor components
    m_components["Radar Antenna"] = {"Radar Antenna", "Sensors", HEALTH_EXCELLENT, 96.0, 0.0, 100.0, "%", "Primary radar antenna system", QDateTime::currentDateTime(), {}};
    m_components["GPS Receiver"] = {"GPS Receiver", "Sensors", HEALTH_GOOD, 89.0, 0.0, 100.0, "%", "Global positioning system", QDateTime::currentDateTime(), {}};
    m_components["Compass"] = {"Compass", "Sensors", HEALTH_EXCELLENT, 98.0, 0.0, 100.0, "%", "Digital compass sensor", QDateTime::currentDateTime(), {}};
    
    updateComponentDisplay();
}

void CHealthMonitorWidget::onRefreshHealth()
{
    updateHealthStatus();
    addHealthAlert("System", "Manual health refresh requested", HEALTH_GOOD);
}

void CHealthMonitorWidget::onResetAlerts()
{
    m_recentAlerts.clear();
    m_alertCount = 0;
    m_alertsText->clear();
    m_alertsText->append(QString("[%1] All alerts cleared").arg(QTime::currentTime().toString()));
    m_activeAlertsLabel->setText("Active Alerts: 0");
}

void CHealthMonitorWidget::onExportReport()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Health Report", 
                                                   QString("health_report_%1.txt").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")),
                                                   "Text Files (*.txt)");
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            
            out << "RADAR DISPLAY SYSTEM HEALTH REPORT\n";
            out << "Generated: " << QDateTime::currentDateTime().toString() << "\n";
            out << "========================================\n\n";
            
            // Overall status
            out << "SYSTEM OVERVIEW:\n";
            out << "Overall Health: " << m_overallHealthBar->value() << "%\n";
            out << "Active Alerts: " << m_alertCount << "\n\n";
            
            // Components by category
            for (const QString &category : m_categories) {
                out << category.toUpper() << " COMPONENTS:\n";
                for (auto it = m_components.constBegin(); it != m_components.constEnd(); ++it) {
                    if (it.value().category == category) {
                        out << "  " << it.value().name << ": " << getStatusText(it.value().status) 
                            << " (" << it.value().value << it.value().unit << ")\n";
                    }
                }
                out << "\n";
            }
            
            // Recent alerts
            out << "RECENT ALERTS:\n";
            for (const QString &alert : m_recentAlerts) {
                out << "  " << alert << "\n";
            }
            
            file.close();
            addHealthAlert("System", QString("Health report exported to %1").arg(fileName), HEALTH_GOOD);
        }
    }
}

void CHealthMonitorWidget::onHealthTimer()
{
    if (m_autoRefresh) {
        simulateHealthData();
        updateHealthStatus();
    }
}

void CHealthMonitorWidget::onComponentSelectionChanged()
{
    QTreeWidgetItem *item = m_componentsTree->currentItem();
    if (!item || !item->parent()) {
        m_selectedComponentLabel->setText("Select a component for details");
        m_componentHealthBar->setValue(0);
        m_componentValueLabel->setText("Value: N/A");
        m_componentStatusLabel->setText("Status: N/A");
        m_componentDescriptionText->clear();
        return;
    }
    
    QString componentName = item->text(0);
    if (m_components.contains(componentName)) {
        const SystemComponent &comp = m_components[componentName];
        
        m_selectedComponentLabel->setText(comp.name);
        
        // Calculate health percentage based on status
        int healthPercent = 0;
        switch (comp.status) {
            case HEALTH_EXCELLENT: healthPercent = 95; break;
            case HEALTH_GOOD: healthPercent = 80; break;
            case HEALTH_WARNING: healthPercent = 60; break;
            case HEALTH_CRITICAL: healthPercent = 30; break;
            case HEALTH_OFFLINE: healthPercent = 0; break;
        }
        m_componentHealthBar->setValue(healthPercent);
        
        // Set progress bar color based on status
        QString barColor;
        switch (comp.status) {
            case HEALTH_EXCELLENT: 
            case HEALTH_GOOD: 
                barColor = "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #a6e3a1, stop:1 #40a02b);";
                break;
            case HEALTH_WARNING: 
                barColor = "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f9e2af, stop:1 #d29922);";
                break;
            case HEALTH_CRITICAL: 
                barColor = "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f38ba8, stop:1 #d20f39);";
                break;
            case HEALTH_OFFLINE: 
                barColor = "background-color: #6c7086;";
                break;
        }
        m_componentHealthBar->setStyleSheet(QString("QProgressBar::chunk { %1 border-radius: 3px; }").arg(barColor));
        
        m_componentValueLabel->setText(QString("Value: %1 %2").arg(comp.value).arg(comp.unit));
        m_componentStatusLabel->setText(QString("Status: %1").arg(getStatusText(comp.status)));
        m_componentDescriptionText->setText(comp.description);
    }
}

void CHealthMonitorWidget::onAutoRefreshToggled(bool enabled)
{
    m_autoRefresh = enabled;
    if (enabled) {
        m_healthTimer->start(UPDATE_INTERVAL);
        addHealthAlert("System", "Auto-refresh enabled", HEALTH_GOOD);
    } else {
        m_healthTimer->stop();
        addHealthAlert("System", "Auto-refresh disabled", HEALTH_GOOD);
    }
}

void CHealthMonitorWidget::updateHealthStatus()
{
    // Calculate overall health
    int totalComponents = m_components.size();
    int healthSum = 0;
    int criticalCount = 0;
    int warningCount = 0;
    
    for (auto it = m_components.constBegin(); it != m_components.constEnd(); ++it) {
        const SystemComponent &comp = it.value();
        switch (comp.status) {
            case HEALTH_EXCELLENT: healthSum += 100; break;
            case HEALTH_GOOD: healthSum += 80; break;
            case HEALTH_WARNING: healthSum += 60; warningCount++; break;
            case HEALTH_CRITICAL: healthSum += 30; criticalCount++; break;
            case HEALTH_OFFLINE: healthSum += 0; criticalCount++; break;
        }
    }
    
    int overallHealth = healthSum / totalComponents;
    m_overallHealthBar->setValue(overallHealth);
    
    // Set overall health bar color
    QString barColor;
    if (overallHealth >= 80) {
        barColor = "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #a6e3a1, stop:1 #40a02b);";
        m_systemStatusLabel->setText("System Status: Operational");
        m_systemStatusLabel->setStyleSheet("color: #a6e3a1; font-weight: bold; font-size: 12px;");
    } else if (overallHealth >= 60) {
        barColor = "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f9e2af, stop:1 #d29922);";
        m_systemStatusLabel->setText("System Status: Warning");
        m_systemStatusLabel->setStyleSheet("color: #f9e2af; font-weight: bold; font-size: 12px;");
    } else {
        barColor = "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f38ba8, stop:1 #d20f39);";
        m_systemStatusLabel->setText("System Status: Critical");
        m_systemStatusLabel->setStyleSheet("color: #f38ba8; font-weight: bold; font-size: 12px;");
    }
    m_overallHealthBar->setStyleSheet(QString("QProgressBar::chunk { %1 border-radius: 3px; }").arg(barColor));
    
    m_lastUpdateLabel->setText(QString("Last Update: %1").arg(QTime::currentTime().toString()));
    m_activeAlertsLabel->setText(QString("Active Alerts: %1").arg(m_alertCount));
    
    updateComponentDisplay();
}

void CHealthMonitorWidget::updateComponentDisplay()
{
    m_componentsTree->clear();
    m_categoryItems.clear();
    
    // Create category items
    for (const QString &category : m_categories) {
        QTreeWidgetItem *categoryItem = new QTreeWidgetItem(m_componentsTree);
        categoryItem->setText(0, category);
        categoryItem->setExpanded(true);
        categoryItem->setFont(0, QFont("Arial", 10, QFont::Bold));
        m_categoryItems[category] = categoryItem;
    }
    
    // Add components to categories
    for (auto it = m_components.constBegin(); it != m_components.constEnd(); ++it) {
        const SystemComponent &comp = it.value();
        QTreeWidgetItem *categoryItem = m_categoryItems[comp.category];
        
        QTreeWidgetItem *compItem = new QTreeWidgetItem(categoryItem);
        compItem->setText(0, comp.name);
        compItem->setText(1, getStatusText(comp.status));
        compItem->setText(2, QString("%1 %2").arg(comp.value).arg(comp.unit));
        compItem->setText(3, comp.lastUpdate.time().toString());
        
        // Set status color
        QColor statusColor = getStatusColor(comp.status);
        compItem->setForeground(1, QBrush(statusColor));
        compItem->setIcon(0, createStatusIcon(comp.status));
    }
    
    // Resize columns to content
    for (int i = 0; i < m_componentsTree->columnCount(); ++i) {
        m_componentsTree->resizeColumnToContents(i);
    }
}

void CHealthMonitorWidget::simulateHealthData()
{
    // Simulate realistic health data changes
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        SystemComponent &comp = it.value();
        
        // Add some random variation to values
        double variation = (QRandomGenerator::global()->generateDouble() - 0.5) * 10.0;
        comp.value = qMax(comp.minValue, qMin(comp.maxValue, comp.value + variation));
        
        // Update status based on value and component type
        HealthStatus oldStatus = comp.status;
        
        if (comp.name == "System Disk" && comp.value > 85) {
            comp.status = HEALTH_CRITICAL;
        } else if (comp.name == "Temperature" && comp.value > 80) {
            comp.status = HEALTH_WARNING;
        } else if (comp.name == "Network Latency" && comp.value > 50) {
            comp.status = HEALTH_WARNING;
        } else if (comp.value > 90) {
            comp.status = HEALTH_WARNING;
        } else if (comp.value > 95) {
            comp.status = HEALTH_CRITICAL;
        } else if (comp.value < 20) {
            comp.status = HEALTH_EXCELLENT;
        } else if (comp.value < 60) {
            comp.status = HEALTH_GOOD;
        } else {
            comp.status = HEALTH_GOOD;
        }
        
        // Randomly introduce some issues
        if (QRandomGenerator::global()->bounded(1000) < 5) { // 0.5% chance
            comp.status = static_cast<HealthStatus>(QRandomGenerator::global()->bounded(5));
        }
        
        comp.lastUpdate = QDateTime::currentDateTime();
        
        // Add to history
        comp.history.append(comp.value);
        if (comp.history.size() > MAX_HISTORY_SIZE) {
            comp.history.removeFirst();
        }
        
        // Generate alerts for status changes
        if (oldStatus != comp.status) {
            QString message;
            switch (comp.status) {
                case HEALTH_CRITICAL:
                    message = QString("%1 status changed to CRITICAL").arg(comp.name);
                    break;
                case HEALTH_WARNING:
                    message = QString("%1 status changed to WARNING").arg(comp.name);
                    break;
                case HEALTH_OFFLINE:
                    message = QString("%1 has gone OFFLINE").arg(comp.name);
                    break;
                case HEALTH_GOOD:
                    if (oldStatus == HEALTH_CRITICAL || oldStatus == HEALTH_WARNING) {
                        message = QString("%1 status improved to GOOD").arg(comp.name);
                    }
                    break;
                case HEALTH_EXCELLENT:
                    if (oldStatus != HEALTH_GOOD) {
                        message = QString("%1 status improved to EXCELLENT").arg(comp.name);
                    }
                    break;
            }
            
            if (!message.isEmpty()) {
                addHealthAlert(comp.name, message, comp.status);
            }
        }
    }
}

QString CHealthMonitorWidget::getStatusText(HealthStatus status)
{
    switch (status) {
        case HEALTH_EXCELLENT: return "Excellent";
        case HEALTH_GOOD: return "Good";
        case HEALTH_WARNING: return "Warning";
        case HEALTH_CRITICAL: return "Critical";
        case HEALTH_OFFLINE: return "Offline";
        default: return "Unknown";
    }
}

QColor CHealthMonitorWidget::getStatusColor(HealthStatus status)
{
    switch (status) {
        case HEALTH_EXCELLENT: return QColor("#a6e3a1"); // Green
        case HEALTH_GOOD: return QColor("#89b4fa");       // Blue
        case HEALTH_WARNING: return QColor("#f9e2af");    // Yellow
        case HEALTH_CRITICAL: return QColor("#f38ba8");   // Red
        case HEALTH_OFFLINE: return QColor("#6c7086");    // Gray
        default: return QColor("#cdd6f4");                // White
    }
}

QIcon CHealthMonitorWidget::createStatusIcon(HealthStatus status)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::transparent);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    QColor color = getStatusColor(status);
    painter.setBrush(QBrush(color));
    painter.setPen(QPen(color.darker(), 1));
    
    painter.drawEllipse(2, 2, 12, 12);
    
    return QIcon(pixmap);
}

void CHealthMonitorWidget::addHealthAlert(const QString& component, const QString& message, HealthStatus severity)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString severityText = getStatusText(severity).toUpper();
    QString alertText = QString("[%1] %2: %3 - %4").arg(timestamp, severityText, component, message);
    
    m_recentAlerts.prepend(alertText);
    if (m_recentAlerts.size() > MAX_ALERTS) {
        m_recentAlerts.removeLast();
    }
    
    m_alertsText->clear();
    for (const QString &alert : m_recentAlerts) {
        m_alertsText->append(alert);
    }
    
    // Update alert count (only count warnings and critical)
    if (severity == HEALTH_WARNING || severity == HEALTH_CRITICAL) {
        m_alertCount++;
    }
}
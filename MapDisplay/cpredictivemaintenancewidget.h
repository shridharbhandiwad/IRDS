#ifndef CPREDICTIVEMAINTENANCEWIDGET_H
#define CPREDICTIVEMAINTENANCEWIDGET_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QGroupBox>
#include <QTimer>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QFrame>
#include <QRandomGenerator>
#include <QDateTime>
#include <QCalendarWidget>
#include <QSplitter>

class CPredictiveMaintenanceWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CPredictiveMaintenanceWidget(QWidget *parent = nullptr);
    ~CPredictiveMaintenanceWidget();

    enum MaintenanceStatus {
        MAINTENANCE_OPTIMAL = 0,
        MAINTENANCE_GOOD = 1,
        MAINTENANCE_ATTENTION = 2,
        MAINTENANCE_URGENT = 3,
        MAINTENANCE_CRITICAL = 4
    };

    enum MaintenancePriority {
        PRIORITY_LOW = 0,
        PRIORITY_MEDIUM = 1,
        PRIORITY_HIGH = 2,
        PRIORITY_CRITICAL = 3
    };

    struct MaintenanceItem {
        QString component;
        QString category;
        MaintenanceStatus status;
        MaintenancePriority priority;
        QDateTime nextMaintenance;
        QDateTime lastMaintenance;
        int operatingHours;
        int maintenanceInterval;
        double wearLevel;
        double reliability;
        QString description;
        QString recommendations;
        QList<QDateTime> maintenanceHistory;
    };

private slots:
    void onRefreshData();
    void onScheduleMaintenance();
    void onCompleteMaintenance();
    void onExportSchedule();
    void onPredictionTimer();
    void onFilterChanged();
    void onMaintenanceItemSelected();
    void onAutoUpdateToggled(bool enabled);
    void onCalendarDateSelected(const QDate &date);

private:
    void setupUI();
    void applyModernTheme();
    void initializeMaintenanceItems();
    void updateMaintenanceTable();
    void updatePredictions();
    void updateMaintenanceCalendar();
    void calculatePredictions();
    QString getStatusText(MaintenanceStatus status);
    QString getPriorityText(MaintenancePriority priority);
    QColor getStatusColor(MaintenanceStatus status);
    QColor getPriorityColor(MaintenancePriority priority);
    void addMaintenanceLog(const QString& component, const QString& action);

    // UI Components
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    QSplitter *m_mainSplitter;
    
    // Left Panel
    QWidget *m_leftPanel;
    QVBoxLayout *m_leftLayout;
    
    // Control Group
    QGroupBox *m_controlGroup;
    QPushButton *m_refreshButton;
    QPushButton *m_scheduleButton;
    QPushButton *m_completeButton;
    QPushButton *m_exportButton;
    QCheckBox *m_autoUpdateCheck;
    
    // Filter Group
    QGroupBox *m_filterGroup;
    QComboBox *m_statusFilter;
    QComboBox *m_priorityFilter;
    QComboBox *m_categoryFilter;
    
    // Overview Group
    QGroupBox *m_overviewGroup;
    QLabel *m_totalItemsLabel;
    QLabel *m_urgentItemsLabel;
    QLabel *m_upcomingLabel;
    QProgressBar *m_systemReliabilityBar;
    
    // Maintenance Table
    QGroupBox *m_tableGroup;
    QTableWidget *m_maintenanceTable;
    
    // Right Panel
    QWidget *m_rightPanel;
    QVBoxLayout *m_rightLayout;
    
    // Details Group
    QGroupBox *m_detailsGroup;
    QLabel *m_selectedComponentLabel;
    QLabel *m_statusLabel;
    QLabel *m_priorityLabel;
    QLabel *m_nextMaintenanceLabel;
    QLabel *m_operatingHoursLabel;
    QProgressBar *m_wearLevelBar;
    QProgressBar *m_reliabilityBar;
    QTextEdit *m_descriptionText;
    QTextEdit *m_recommendationsText;
    
    // Calendar Group
    QGroupBox *m_calendarGroup;
    QCalendarWidget *m_calendar;
    
    // Log Group
    QGroupBox *m_logGroup;
    QTextEdit *m_logText;
    
    // Maintenance state
    QTimer *m_predictionTimer;
    QMap<QString, MaintenanceItem> m_maintenanceItems;
    QStringList m_recentLogs;
    
    bool m_autoUpdate;
    QString m_selectedComponent;
    
    // Categories and filters
    QStringList m_categories;
    
    // Constants
    static constexpr int UPDATE_INTERVAL = 10000; // 10 seconds
    static constexpr int MAX_LOG_ENTRIES = 100;
    static constexpr int HOURS_PER_DAY = 24;
};

#endif // CPREDICTIVEMAINTENANCEWIDGET_H
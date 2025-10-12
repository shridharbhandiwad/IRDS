#ifndef CHEALTHMONITORWIDGET_H
#define CHEALTHMONITORWIDGET_H

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
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFrame>
#include <QScrollArea>
#include <QRandomGenerator>
#include <QDateTime>
#include <QIcon>
#include <QPixmap>
#include <QPainter>

class CHealthMonitorWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CHealthMonitorWidget(QWidget *parent = nullptr);
    ~CHealthMonitorWidget();

    enum HealthStatus {
        HEALTH_EXCELLENT = 0,
        HEALTH_GOOD = 1,
        HEALTH_WARNING = 2,
        HEALTH_CRITICAL = 3,
        HEALTH_OFFLINE = 4
    };

    struct SystemComponent {
        QString name;
        QString category;
        HealthStatus status;
        double value;
        double minValue;
        double maxValue;
        QString unit;
        QString description;
        QDateTime lastUpdate;
        QList<double> history;
    };

private slots:
    void onRefreshHealth();
    void onResetAlerts();
    void onExportReport();
    void onHealthTimer();
    void onComponentSelectionChanged();
    void onAutoRefreshToggled(bool enabled);

private:
    void setupUI();
    void applyModernTheme();
    void initializeComponents();
    void updateHealthStatus();
    void updateComponentDisplay();
    void simulateHealthData();
    QString getStatusText(HealthStatus status);
    QColor getStatusColor(HealthStatus status);
    QIcon createStatusIcon(HealthStatus status);
    void addHealthAlert(const QString& component, const QString& message, HealthStatus severity);

    // UI Components
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    
    // Control Group
    QGroupBox *m_controlGroup;
    QPushButton *m_refreshButton;
    QPushButton *m_resetAlertsButton;
    QPushButton *m_exportButton;
    QCheckBox *m_autoRefreshCheck;
    
    // Overview Group
    QGroupBox *m_overviewGroup;
    QLabel *m_systemStatusLabel;
    QProgressBar *m_overallHealthBar;
    QLabel *m_lastUpdateLabel;
    QLabel *m_activeAlertsLabel;
    
    // Components Tree
    QGroupBox *m_componentsGroup;
    QTreeWidget *m_componentsTree;
    
    // Details Group
    QGroupBox *m_detailsGroup;
    QLabel *m_selectedComponentLabel;
    QProgressBar *m_componentHealthBar;
    QLabel *m_componentValueLabel;
    QLabel *m_componentStatusLabel;
    QTextEdit *m_componentDescriptionText;
    
    // Alerts Group
    QGroupBox *m_alertsGroup;
    QTextEdit *m_alertsText;
    
    // Health monitoring state
    QTimer *m_healthTimer;
    QMap<QString, SystemComponent> m_components;
    QStringList m_recentAlerts;
    
    bool m_autoRefresh;
    int m_alertCount;
    
    // Categories for organization
    QStringList m_categories;
    QMap<QString, QTreeWidgetItem*> m_categoryItems;
    
    // Constants
    static constexpr int UPDATE_INTERVAL = 5000; // 5 seconds
    static constexpr int MAX_HISTORY_SIZE = 100;
    static constexpr int MAX_ALERTS = 50;
};

#endif // CHEALTHMONITORWIDGET_H
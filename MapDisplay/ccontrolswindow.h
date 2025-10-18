#ifndef CCONTROLSWINDOW_H
#define CCONTROLSWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

// Forward declarations
class CConfigPanelWidget;
class CInterfacesPanelWidget;
class CAnalyticsWidget;
class CSimulationWidget;
class CRecordingWidget;
class CHealthMonitorWidget;
class CPredictiveMaintenanceWidget;
class CChartsWidget;

/**
 * @brief Window for all controls and tabs (Monitor 2)
 * 
 * This window contains all control panels in a rich tabbed interface:
 * - Configuration panel
 * - Interfaces panel
 * - Analytics widget
 * - Simulation widget
 * - Recording widget
 * - Health monitor
 * - Predictive maintenance
 * - Charts widget
 */
class CControlsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CControlsWindow(QWidget *parent = nullptr);
    ~CControlsWindow();

    /**
     * @brief Get configuration panel instance
     * @return Pointer to config panel
     */
    CConfigPanelWidget* getConfigPanel() { return m_configPanel; }

signals:
    // Configuration signals (to be forwarded to PPI window or main controller)
    void mapHomeRequested();
    void openMapsRequested();
    void flushRequested();
    void exitRequested();
    void zoomChanged(double zoom);
    void opacityChanged(int opacity);
    void trackSizeChanged(int size);
    void trackFilterChanged(bool showFriend, bool showHostile, bool showUnknown);
    void animationSpeedChanged(int speed);
    void gridVisibilityChanged(bool visible);
    void compassVisibilityChanged(bool visible);

private slots:
    void onCurrentTabChanged(int index);

private:
    void setupUI();
    void setupConfigPanel();
    void setupInterfacesPanel();
    void setupAnalyticsWidget();
    void setupSimulationWidget();
    void setupRecordingWidget();
    void setupHealthMonitorWidget();
    void setupPredictiveMaintenanceWidget();
    void setupChartsWidget();
    void applyLightTheme();

private:
    QTabWidget *m_tabWidget;
    
    CConfigPanelWidget *m_configPanel;
    CInterfacesPanelWidget *m_interfacesPanel;
    CAnalyticsWidget *m_analyticsWidget;
    CSimulationWidget *m_simulationWidget;
    CRecordingWidget *m_recordingWidget;
    CHealthMonitorWidget *m_healthMonitorWidget;
    CPredictiveMaintenanceWidget *m_predictiveMaintenanceWidget;
    CChartsWidget *m_chartsWidget;
};

#endif // CCONTROLSWINDOW_H

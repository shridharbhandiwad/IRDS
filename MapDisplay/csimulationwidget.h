#ifndef CSIMULATIONWIDGET_H
#define CSIMULATIONWIDGET_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QSlider>
#include <QCheckBox>
#include <QGroupBox>
#include <QTimer>
#include <QProgressBar>
#include <QTextEdit>
#include <QUdpSocket>
#include <QRandomGenerator>
#include <QFrame>
#include "../globalstructs.h"

class CSimulationWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CSimulationWidget(QWidget *parent = nullptr);
    ~CSimulationWidget();

private slots:
    void onStartSimulation();
    void onStopSimulation();
    void onPauseSimulation();
    void onResetSimulation();
    void onGenerateTrack();
    void onClearAllTracks();
    void onSimulationTick();
    void onTrackCountChanged(int count);
    void onRangeChanged(double range);
    void onUpdateRateChanged(int rate);
    void onScenarioChanged(int index);

private:
    void setupUI();
    void applyModernTheme();
    void generateRandomTrack();
    void updateTrackPosition(int trackId);
    void sendTrackData(const stTrackRecvInfo& track);
    void updateSimulationStatus();
    void loadScenario(int scenarioIndex);

    // UI Components
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    
    // Control Group
    QGroupBox *m_controlGroup;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QPushButton *m_pauseButton;
    QPushButton *m_resetButton;
    
    // Track Generation Group
    QGroupBox *m_trackGenGroup;
    QSpinBox *m_trackCountSpin;
    QDoubleSpinBox *m_rangeSpin;
    QPushButton *m_generateButton;
    QPushButton *m_clearButton;
    
    // Simulation Parameters Group
    QGroupBox *m_paramGroup;
    QSlider *m_updateRateSlider;
    QLabel *m_updateRateLabel;
    QComboBox *m_scenarioCombo;
    QCheckBox *m_randomMotionCheck;
    QCheckBox *m_collisionAvoidanceCheck;
    
    // Status Group
    QGroupBox *m_statusGroup;
    QLabel *m_activeTracksLabel;
    QLabel *m_simulationTimeLabel;
    QProgressBar *m_cpuUsageBar;
    QTextEdit *m_logText;
    
    // Simulation State
    QTimer *m_simulationTimer;
    QUdpSocket *m_udpSocket;
    QMap<int, stTrackRecvInfo> m_activeTracks;
    QMap<int, QPointF> m_trackVelocities;
    
    bool m_isRunning;
    bool m_isPaused;
    int m_simulationTime;
    int m_nextTrackId;
    double m_maxRange;
    int m_updateRate;
    
    // Scenario configurations
    struct SimulationScenario {
        QString name;
        int defaultTrackCount;
        double defaultRange;
        bool hasRandomMotion;
        QString description;
    };
    
    QList<SimulationScenario> m_scenarios;
    
    // Constants
    static constexpr int UDP_PORT = 12345;
    static constexpr double MAX_SIMULATION_RANGE = 10000.0; // 10km
    static constexpr int MIN_UPDATE_RATE = 100; // 100ms
    static constexpr int MAX_UPDATE_RATE = 5000; // 5s
};

#endif // CSIMULATIONWIDGET_H
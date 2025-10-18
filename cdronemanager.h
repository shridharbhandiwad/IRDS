#ifndef CDRONEMANAGER_H
#define CDRONEMANAGER_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include <QMutex>
#include "cdrone.h"

/**
 * @brief Manager class for handling multiple drones
 */
class CDroneManager : public QObject
{
    Q_OBJECT

public:
    static CDroneManager* getInstance();
    
    // Drone management
    CDrone* createDrone(int droneId);
    CDrone* getDrone(int droneId);
    void removeDrone(int droneId);
    QList<CDrone*> getAllDrones() const;
    QList<int> getDroneIds() const;
    
    // Batch operations
    void startAllDroneSimulations();
    void stopAllDroneSimulations();
    void updateAllDronePositions();
    
    // Convert to track display format
    QList<stTrackDisplayInfo> getDroneTrackList() const;
    
    // Scenario management
    void createTestScenario();
    void clearAllDrones();
    
    // Statistics
    int getActiveDroneCount() const;
    int getTotalDroneCount() const;

public slots:
    void onDroneDynamicsUpdated();
    void onDroneFlightModeChanged(eDroneFlightMode newMode);
    void onDroneSystemStatusChanged(eDroneSystemStatus newStatus);
    void onDroneWaypointReached(int waypointIndex);
    void onDroneBatteryLow(double level);

signals:
    void droneAdded(int droneId);
    void droneRemoved(int droneId);
    void droneUpdated(int droneId);
    void droneListChanged();

private:
    explicit CDroneManager(QObject *parent = nullptr);
    ~CDroneManager();
    
    static CDroneManager* m_instance;
    static QMutex m_mutex;
    
    QMap<int, CDrone*> m_drones;
    QMutex m_dronesMutex;
    
    // Helper methods
    void connectDroneSignals(CDrone* drone);
    void disconnectDroneSignals(CDrone* drone);
};

#endif // CDRONEMANAGER_H
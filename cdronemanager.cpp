#include "cdronemanager.h"
#include <QDebug>
#include <QMutexLocker>

CDroneManager* CDroneManager::m_instance = nullptr;
QMutex CDroneManager::m_mutex;

CDroneManager::CDroneManager(QObject *parent)
    : QObject(parent)
{
    qDebug() << "DroneManager initialized";
}

CDroneManager::~CDroneManager()
{
    clearAllDrones();
    qDebug() << "DroneManager destroyed";
}

CDroneManager* CDroneManager::getInstance()
{
    QMutexLocker locker(&m_mutex);
    if (m_instance == nullptr) {
        m_instance = new CDroneManager();
    }
    return m_instance;
}

CDrone* CDroneManager::createDrone(int droneId)
{
    QMutexLocker locker(&m_dronesMutex);
    
    if (m_drones.contains(droneId)) {
        qWarning() << "Drone with ID" << droneId << "already exists";
        return m_drones[droneId];
    }
    
    CDrone* drone = new CDrone(droneId, this);
    m_drones[droneId] = drone;
    
    connectDroneSignals(drone);
    
    qDebug() << "Created drone with ID" << droneId;
    emit droneAdded(droneId);
    emit droneListChanged();
    
    return drone;
}

CDrone* CDroneManager::getDrone(int droneId)
{
    QMutexLocker locker(&m_dronesMutex);
    return m_drones.value(droneId, nullptr);
}

void CDroneManager::removeDrone(int droneId)
{
    QMutexLocker locker(&m_dronesMutex);
    
    if (!m_drones.contains(droneId)) {
        qWarning() << "Drone with ID" << droneId << "does not exist";
        return;
    }
    
    CDrone* drone = m_drones[droneId];
    disconnectDroneSignals(drone);
    
    m_drones.remove(droneId);
    drone->deleteLater();
    
    qDebug() << "Removed drone with ID" << droneId;
    emit droneRemoved(droneId);
    emit droneListChanged();
}

QList<CDrone*> CDroneManager::getAllDrones() const
{
    QMutexLocker locker(&m_dronesMutex);
    return m_drones.values();
}

QList<int> CDroneManager::getDroneIds() const
{
    QMutexLocker locker(&m_dronesMutex);
    return m_drones.keys();
}

void CDroneManager::startAllDroneSimulations()
{
    QMutexLocker locker(&m_dronesMutex);
    
    for (CDrone* drone : m_drones) {
        if (drone->getSystemStatus() == DRONE_STATUS_ACTIVE) {
            drone->startDynamicsSimulation();
        }
    }
    
    qDebug() << "Started simulation for all active drones";
}

void CDroneManager::stopAllDroneSimulations()
{
    QMutexLocker locker(&m_dronesMutex);
    
    for (CDrone* drone : m_drones) {
        drone->stopDynamicsSimulation();
    }
    
    qDebug() << "Stopped simulation for all drones";
}

void CDroneManager::updateAllDronePositions()
{
    QMutexLocker locker(&m_dronesMutex);
    
    for (CDrone* drone : m_drones) {
        // This would typically receive updates from external sources
        // For now, the drones update themselves via simulation
    }
}

QList<stTrackDisplayInfo> CDroneManager::getDroneTrackList() const
{
    QMutexLocker locker(&m_dronesMutex);
    
    QList<stTrackDisplayInfo> trackList;
    
    for (CDrone* drone : m_drones) {
        trackList.append(drone->toTrackDisplayInfo());
    }
    
    return trackList;
}

void CDroneManager::createTestScenario()
{
    qDebug() << "Creating test drone scenario";
    
    // Create multiple test drones with different configurations
    
    // Drone 1: Friendly patrol drone
    CDrone* drone1 = createDrone(101);
    drone1->setIdentity(TRACK_IDENTITY_FRIEND);
    drone1->setFlightMode(DRONE_MODE_WAYPOINT);
    drone1->setSystemStatus(DRONE_STATUS_ACTIVE);
    drone1->updatePosition(40.7128, -74.0060, 100.0, 45.0); // New York area
    drone1->setBatteryLevel(85.0);
    drone1->setSignalStrength(95.0);
    
    // Add waypoints for patrol
    stDroneWaypoint wp1 = {1, 40.7200, -74.0000, 120.0, 15.0, 0, false};
    stDroneWaypoint wp2 = {2, 40.7300, -74.0100, 100.0, 15.0, 0, false};
    stDroneWaypoint wp3 = {3, 40.7200, -74.0200, 110.0, 15.0, 0, false};
    drone1->addWaypoint(wp1);
    drone1->addWaypoint(wp2);
    drone1->addWaypoint(wp3);
    
    // Drone 2: Unknown surveillance drone
    CDrone* drone2 = createDrone(102);
    drone2->setIdentity(TRACK_IDENTITY_UNKNOWN);
    drone2->setFlightMode(DRONE_MODE_LOITER);
    drone2->setSystemStatus(DRONE_STATUS_ACTIVE);
    drone2->updatePosition(40.7500, -73.9800, 200.0, 180.0);
    drone2->setBatteryLevel(60.0);
    drone2->setSignalStrength(75.0);
    
    // Drone 3: Hostile interceptor
    CDrone* drone3 = createDrone(103);
    drone3->setIdentity(TRACK_IDENTITY_HOSTILE);
    drone3->setFlightMode(DRONE_MODE_AUTOPILOT);
    drone3->setSystemStatus(DRONE_STATUS_ACTIVE);
    drone3->updatePosition(40.7000, -73.9900, 150.0, 270.0);
    drone3->setBatteryLevel(90.0);
    drone3->setSignalStrength(85.0);
    
    // Add intercept waypoints
    stDroneWaypoint wp4 = {1, 40.7100, -74.0050, 150.0, 20.0, 0, false};
    stDroneWaypoint wp5 = {2, 40.7150, -74.0080, 150.0, 20.0, 0, false};
    drone3->addWaypoint(wp4);
    drone3->addWaypoint(wp5);
    
    // Drone 4: Search and rescue drone with degraded health
    CDrone* drone4 = createDrone(104);
    drone4->setIdentity(TRACK_IDENTITY_FRIEND);
    drone4->setFlightMode(DRONE_MODE_WAYPOINT);
    drone4->setSystemStatus(DRONE_STATUS_CRITICAL);
    drone4->updatePosition(40.7400, -74.0150, 80.0, 90.0);
    drone4->setBatteryLevel(25.0); // Low battery
    drone4->setSignalStrength(50.0); // Weak signal
    
    // Simulate degraded health
    stDroneSubsystemHealth health4;
    health4.gps_healthy = true;
    health4.imu_healthy = false; // IMU problem
    health4.battery_healthy = false; // Battery issue
    health4.motor_healthy = true;
    health4.communication_healthy = false; // Comm problem
    health4.camera_healthy = true;
    health4.navigation_healthy = true;
    health4.gps_health_percent = 95;
    health4.imu_health_percent = 30;
    health4.battery_health_percent = 25;
    health4.motor_health_percent = 90;
    health4.communication_health_percent = 50;
    health4.camera_health_percent = 85;
    health4.navigation_health_percent = 80;
    drone4->updateSubsystemHealth(health4);
    
    // RTH waypoint
    stDroneWaypoint rth = {1, 40.7350, -74.0120, 50.0, 10.0, 0, false};
    drone4->addWaypoint(rth);
    
    // Start simulations for all active drones
    startAllDroneSimulations();
    
    qDebug() << "Test scenario created with 4 drones";
}

void CDroneManager::clearAllDrones()
{
    QMutexLocker locker(&m_dronesMutex);
    
    for (CDrone* drone : m_drones) {
        disconnectDroneSignals(drone);
        drone->deleteLater();
    }
    
    m_drones.clear();
    
    qDebug() << "All drones cleared";
    emit droneListChanged();
}

int CDroneManager::getActiveDroneCount() const
{
    QMutexLocker locker(&m_dronesMutex);
    
    int activeCount = 0;
    for (CDrone* drone : m_drones) {
        if (drone->getSystemStatus() == DRONE_STATUS_ACTIVE) {
            activeCount++;
        }
    }
    
    return activeCount;
}

int CDroneManager::getTotalDroneCount() const
{
    QMutexLocker locker(&m_dronesMutex);
    return m_drones.size();
}

void CDroneManager::connectDroneSignals(CDrone* drone)
{
    connect(drone, &CDrone::dynamicsUpdated, 
            this, &CDroneManager::onDroneDynamicsUpdated);
    connect(drone, &CDrone::flightModeChanged, 
            this, &CDroneManager::onDroneFlightModeChanged);
    connect(drone, &CDrone::systemStatusChanged, 
            this, &CDroneManager::onDroneSystemStatusChanged);
    connect(drone, &CDrone::waypointReached, 
            this, &CDroneManager::onDroneWaypointReached);
    connect(drone, &CDrone::batteryLow, 
            this, &CDroneManager::onDroneBatteryLow);
}

void CDroneManager::disconnectDroneSignals(CDrone* drone)
{
    disconnect(drone, nullptr, this, nullptr);
}

// Slot implementations
void CDroneManager::onDroneDynamicsUpdated()
{
    CDrone* drone = qobject_cast<CDrone*>(sender());
    if (drone) {
        emit droneUpdated(drone->getDroneId());
    }
}

void CDroneManager::onDroneFlightModeChanged(eDroneFlightMode newMode)
{
    CDrone* drone = qobject_cast<CDrone*>(sender());
    if (drone) {
        qDebug() << "Drone" << drone->getDroneId() << "flight mode changed to" << newMode;
        emit droneUpdated(drone->getDroneId());
    }
}

void CDroneManager::onDroneSystemStatusChanged(eDroneSystemStatus newStatus)
{
    CDrone* drone = qobject_cast<CDrone*>(sender());
    if (drone) {
        qDebug() << "Drone" << drone->getDroneId() << "system status changed to" << newStatus;
        emit droneUpdated(drone->getDroneId());
    }
}

void CDroneManager::onDroneWaypointReached(int waypointIndex)
{
    CDrone* drone = qobject_cast<CDrone*>(sender());
    if (drone) {
        qDebug() << "Drone" << drone->getDroneId() << "reached waypoint" << waypointIndex;
        emit droneUpdated(drone->getDroneId());
    }
}

void CDroneManager::onDroneBatteryLow(double level)
{
    CDrone* drone = qobject_cast<CDrone*>(sender());
    if (drone) {
        qWarning() << "Drone" << drone->getDroneId() << "battery low:" << level << "%";
        emit droneUpdated(drone->getDroneId());
    }
}
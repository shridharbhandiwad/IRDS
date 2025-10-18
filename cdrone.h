#ifndef CDRONE_H
#define CDRONE_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QPointF>
#include <QList>
#include <cmath>
#include "globalstructs.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Drone flight modes
 */
enum eDroneFlightMode {
    DRONE_MODE_MANUAL = 0,
    DRONE_MODE_AUTOPILOT = 1,
    DRONE_MODE_WAYPOINT = 2,
    DRONE_MODE_LOITER = 3,
    DRONE_MODE_RTH = 4,  // Return to Home
    DRONE_MODE_EMERGENCY = 5
};

/**
 * @brief Drone system status
 */
enum eDroneSystemStatus {
    DRONE_STATUS_INITIALIZING = 0,
    DRONE_STATUS_STANDBY = 1,
    DRONE_STATUS_ACTIVE = 2,
    DRONE_STATUS_CRITICAL = 3,
    DRONE_STATUS_EMERGENCY = 4,
    DRONE_STATUS_POWEROFF = 5
};

/**
 * @brief Drone subsystem health status
 */
struct stDroneSubsystemHealth {
    bool gps_healthy = true;
    bool imu_healthy = true;
    bool battery_healthy = true;
    bool motor_healthy = true;
    bool communication_healthy = true;
    bool camera_healthy = true;
    bool navigation_healthy = true;
    
    // Health percentages (0-100)
    int gps_health_percent = 100;
    int imu_health_percent = 100;
    int battery_health_percent = 100;
    int motor_health_percent = 100;
    int communication_health_percent = 100;
    int camera_health_percent = 100;
    int navigation_health_percent = 100;
};

/**
 * @brief Drone dynamics information
 */
struct stDroneDynamics {
    // Position and orientation
    double latitude = 0.0;
    double longitude = 0.0;
    double altitude = 0.0;
    double heading = 0.0;      // Yaw angle (degrees)
    double pitch = 0.0;        // Pitch angle (degrees)
    double roll = 0.0;         // Roll angle (degrees)
    
    // Velocity components
    double velocity_north = 0.0;  // m/s
    double velocity_east = 0.0;   // m/s
    double velocity_down = 0.0;   // m/s (positive down)
    double ground_speed = 0.0;    // m/s
    double vertical_speed = 0.0;  // m/s (positive up)
    
    // Acceleration components
    double accel_x = 0.0;      // m/s²
    double accel_y = 0.0;      // m/s²
    double accel_z = 0.0;      // m/s²
    
    // Angular rates
    double angular_velocity_x = 0.0;  // rad/s (roll rate)
    double angular_velocity_y = 0.0;  // rad/s (pitch rate)
    double angular_velocity_z = 0.0;  // rad/s (yaw rate)
    
    // Navigation
    double desired_heading = 0.0;
    double heading_error = 0.0;
    double cross_track_error = 0.0;  // Distance from desired path
    
    // Timestamps
    qint64 timestamp = 0;
};

/**
 * @brief Drone mission waypoint
 */
struct stDroneWaypoint {
    int waypoint_id = 0;
    double lat = 0.0;
    double lon = 0.0;
    double alt = 0.0;
    double speed = 0.0;
    int action = 0;  // Action to perform at waypoint
    bool reached = false;
};

/**
 * @brief Comprehensive drone object with dynamics and internal systems
 */
class CDrone : public QObject
{
    Q_OBJECT

public:
    explicit CDrone(int droneId, QObject *parent = nullptr);
    ~CDrone();

    // Basic properties
    int getDroneId() const { return m_droneId; }
    void setDroneId(int id) { m_droneId = id; }
    
    eTrackIdentity getIdentity() const { return m_identity; }
    void setIdentity(eTrackIdentity identity) { m_identity = identity; }
    
    // Flight mode and status
    eDroneFlightMode getFlightMode() const { return m_flightMode; }
    void setFlightMode(eDroneFlightMode mode);
    
    eDroneSystemStatus getSystemStatus() const { return m_systemStatus; }
    void setSystemStatus(eDroneSystemStatus status) { m_systemStatus = status; }
    
    // Dynamics access
    const stDroneDynamics& getDynamics() const { return m_dynamics; }
    void updateDynamics(const stDroneDynamics& dynamics);
    void updatePosition(double lat, double lon, double alt, double heading);
    void updateVelocity(double vn, double ve, double vd);
    
    // System health
    const stDroneSubsystemHealth& getSubsystemHealth() const { return m_health; }
    void updateSubsystemHealth(const stDroneSubsystemHealth& health) { m_health = health; }
    
    // Battery and power
    double getBatteryLevel() const { return m_batteryLevel; }
    void setBatteryLevel(double level) { m_batteryLevel = qBound(0.0, level, 100.0); }
    
    double getBatteryVoltage() const { return m_batteryVoltage; }
    void setBatteryVoltage(double voltage) { m_batteryVoltage = voltage; }
    
    // Communication
    double getSignalStrength() const { return m_signalStrength; }
    void setSignalStrength(double strength) { m_signalStrength = qBound(0.0, strength, 100.0); }
    
    // Mission management
    void addWaypoint(const stDroneWaypoint& waypoint);
    void clearWaypoints() { m_waypoints.clear(); }
    const QList<stDroneWaypoint>& getWaypoints() const { return m_waypoints; }
    int getCurrentWaypointIndex() const { return m_currentWaypointIndex; }
    
    // Prediction and simulation
    void predictFuturePosition(double deltaTime, double& futLat, double& futLon, double& futAlt) const;
    void simulateDynamics(double deltaTime);
    
    // Conversion to display info
    stTrackDisplayInfo toTrackDisplayInfo() const;
    
    // Utility functions
    double getDistanceToWaypoint(int waypointIndex) const;
    double getBearingToWaypoint(int waypointIndex) const;
    double getTimeToWaypoint(int waypointIndex) const;
    
    // String representations for display
    QString getFlightModeString() const;
    QString getSystemStatusString() const;
    QString getHealthSummary() const;

public slots:
    void updateDynamicsTimer();
    void startDynamicsSimulation();
    void stopDynamicsSimulation();

signals:
    void dynamicsUpdated();
    void flightModeChanged(eDroneFlightMode newMode);
    void systemStatusChanged(eDroneSystemStatus newStatus);
    void waypointReached(int waypointIndex);
    void batteryLow(double level);
    void systemHealthChanged();

private:
    // Core properties
    int m_droneId;
    eTrackIdentity m_identity;
    eDroneFlightMode m_flightMode;
    eDroneSystemStatus m_systemStatus;
    
    // Dynamics and state
    stDroneDynamics m_dynamics;
    stDroneSubsystemHealth m_health;
    
    // Power and communication
    double m_batteryLevel;      // Percentage (0-100)
    double m_batteryVoltage;    // Volts
    double m_signalStrength;    // Percentage (0-100)
    
    // Mission data
    QList<stDroneWaypoint> m_waypoints;
    int m_currentWaypointIndex;
    
    // Simulation and updates
    QTimer* m_dynamicsTimer;
    qint64 m_lastUpdateTime;
    
    // Internal calculations
    void calculateGroundSpeed();
    void calculateHeadingError();
    void updateNavigationToWaypoint();
    void checkWaypointReached();
    void simulateRealisticDynamics(double deltaTime);
    
    // Constants for simulation
    static constexpr double MAX_ACCELERATION = 5.0;     // m/s²
    static constexpr double MAX_ANGULAR_RATE = 1.0;     // rad/s
    static constexpr double MAX_GROUND_SPEED = 25.0;    // m/s
    static constexpr double WAYPOINT_TOLERANCE = 10.0;  // meters
};

#endif // CDRONE_H
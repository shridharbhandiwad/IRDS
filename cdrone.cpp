#include "cdrone.h"
#include <QDebug>
#include <QtMath>

CDrone::CDrone(int droneId, QObject *parent)
    : QObject(parent)
    , m_droneId(droneId)
    , m_identity(TRACK_IDENTITY_UNKNOWN)
    , m_flightMode(DRONE_MODE_STANDBY)
    , m_systemStatus(DRONE_STATUS_INITIALIZING)
    , m_batteryLevel(100.0)
    , m_batteryVoltage(12.6)
    , m_signalStrength(100.0)
    , m_currentWaypointIndex(-1)
    , m_dynamicsTimer(nullptr)
    , m_lastUpdateTime(0)
{
    // Initialize dynamics
    m_dynamics.timestamp = QDateTime::currentMSecsSinceEpoch();
    
    // Initialize health to good state
    m_health = stDroneSubsystemHealth();
    
    // Setup dynamics update timer
    m_dynamicsTimer = new QTimer(this);
    connect(m_dynamicsTimer, &QTimer::timeout, this, &CDrone::updateDynamicsTimer);
    
    qDebug() << "Drone" << m_droneId << "initialized";
}

CDrone::~CDrone()
{
    if (m_dynamicsTimer) {
        m_dynamicsTimer->stop();
    }
    qDebug() << "Drone" << m_droneId << "destroyed";
}

void CDrone::setFlightMode(eDroneFlightMode mode)
{
    if (m_flightMode != mode) {
        eDroneFlightMode oldMode = m_flightMode;
        m_flightMode = mode;
        
        qDebug() << "Drone" << m_droneId << "flight mode changed from" 
                 << oldMode << "to" << mode;
        
        emit flightModeChanged(mode);
    }
}

void CDrone::updateDynamics(const stDroneDynamics& dynamics)
{
    m_dynamics = dynamics;
    m_dynamics.timestamp = QDateTime::currentMSecsSinceEpoch();
    
    // Calculate derived values
    calculateGroundSpeed();
    calculateHeadingError();
    
    // Update navigation if in waypoint mode
    if (m_flightMode == DRONE_MODE_WAYPOINT) {
        updateNavigationToWaypoint();
        checkWaypointReached();
    }
    
    emit dynamicsUpdated();
}

void CDrone::updatePosition(double lat, double lon, double alt, double heading)
{
    m_dynamics.latitude = lat;
    m_dynamics.longitude = lon;
    m_dynamics.altitude = alt;
    m_dynamics.heading = heading;
    m_dynamics.timestamp = QDateTime::currentMSecsSinceEpoch();
    
    calculateGroundSpeed();
    emit dynamicsUpdated();
}

void CDrone::updateVelocity(double vn, double ve, double vd)
{
    m_dynamics.velocity_north = vn;
    m_dynamics.velocity_east = ve;
    m_dynamics.velocity_down = vd;
    
    calculateGroundSpeed();
    m_dynamics.vertical_speed = -vd;  // Convert to positive up
    
    emit dynamicsUpdated();
}

void CDrone::addWaypoint(const stDroneWaypoint& waypoint)
{
    m_waypoints.append(waypoint);
    
    // If this is the first waypoint and we're not already navigating
    if (m_waypoints.size() == 1 && m_currentWaypointIndex == -1) {
        m_currentWaypointIndex = 0;
    }
    
    qDebug() << "Drone" << m_droneId << "waypoint added. Total waypoints:" << m_waypoints.size();
}

void CDrone::predictFuturePosition(double deltaTime, double& futLat, double& futLon, double& futAlt) const
{
    // Simple linear prediction based on current velocity
    double deltaLat = (m_dynamics.velocity_north * deltaTime) / 111132.0; // meters to degrees
    double deltaLon = (m_dynamics.velocity_east * deltaTime) / (111320.0 * std::cos(qDegreesToRadians(m_dynamics.latitude)));
    double deltaAlt = -m_dynamics.velocity_down * deltaTime; // positive up
    
    futLat = m_dynamics.latitude + deltaLat;
    futLon = m_dynamics.longitude + deltaLon;
    futAlt = m_dynamics.altitude + deltaAlt;
}

void CDrone::simulateDynamics(double deltaTime)
{
    if (m_flightMode == DRONE_MODE_STANDBY || m_systemStatus != DRONE_STATUS_ACTIVE) {
        return;
    }
    
    simulateRealisticDynamics(deltaTime);
    
    // Update position based on velocity
    double deltaLat = (m_dynamics.velocity_north * deltaTime) / 111132.0;
    double deltaLon = (m_dynamics.velocity_east * deltaTime) / (111320.0 * std::cos(qDegreesToRadians(m_dynamics.latitude)));
    double deltaAlt = -m_dynamics.velocity_down * deltaTime;
    
    m_dynamics.latitude += deltaLat;
    m_dynamics.longitude += deltaLon;
    m_dynamics.altitude += deltaAlt;
    
    calculateGroundSpeed();
    
    // Update navigation if in waypoint mode
    if (m_flightMode == DRONE_MODE_WAYPOINT) {
        updateNavigationToWaypoint();
        checkWaypointReached();
    }
    
    m_dynamics.timestamp = QDateTime::currentMSecsSinceEpoch();
    emit dynamicsUpdated();
}

stTrackDisplayInfo CDrone::toTrackDisplayInfo() const
{
    stTrackDisplayInfo trackInfo;
    
    trackInfo.nTrkId = m_droneId;
    trackInfo.lat = m_dynamics.latitude;
    trackInfo.lon = m_dynamics.longitude;
    trackInfo.alt = m_dynamics.altitude;
    trackInfo.heading = m_dynamics.heading;
    trackInfo.velocity = m_dynamics.ground_speed;
    trackInfo.nTrackIden = m_identity;
    trackInfo.nTrackTime = m_dynamics.timestamp;
    
    // Calculate range and azimuth (assuming center at 0,0 for now)
    trackInfo.range = std::sqrt(trackInfo.lat * trackInfo.lat + trackInfo.lon * trackInfo.lon) * 111132.0;
    trackInfo.azimuth = qRadiansToDegrees(std::atan2(trackInfo.lon, trackInfo.lat));
    trackInfo.elevation = qRadiansToDegrees(std::atan2(trackInfo.alt, trackInfo.range));
    
    // Populate drone-specific fields
    trackInfo.isDrone = true;
    trackInfo.pitch = m_dynamics.pitch;
    trackInfo.roll = m_dynamics.roll;
    trackInfo.verticalSpeed = m_dynamics.vertical_speed;
    trackInfo.batteryLevel = m_batteryLevel;
    trackInfo.signalStrength = m_signalStrength;
    trackInfo.flightMode = getFlightModeString();
    trackInfo.systemStatus = getSystemStatusString();
    trackInfo.healthSummary = getHealthSummary();
    trackInfo.waypointIndex = m_currentWaypointIndex;
    trackInfo.totalWaypoints = m_waypoints.size();
    
    // Create detailed tooltip with drone-specific information
    QStringList tooltipLines;
    tooltipLines << QString("🚁 DRONE ID: %1").arg(m_droneId);
    tooltipLines << QString("📡 Mode: %1").arg(getFlightModeString());
    tooltipLines << QString("⚡ Status: %1").arg(getSystemStatusString());
    tooltipLines << "";
    tooltipLines << QString("📍 Position:");
    tooltipLines << QString("  Lat: %1°").arg(m_dynamics.latitude, 0, 'f', 6);
    tooltipLines << QString("  Lon: %1°").arg(m_dynamics.longitude, 0, 'f', 6);
    tooltipLines << QString("  Alt: %1 m").arg(m_dynamics.altitude, 0, 'f', 1);
    tooltipLines << "";
    tooltipLines << QString("🧭 Dynamics:");
    tooltipLines << QString("  Heading: %1°").arg(m_dynamics.heading, 0, 'f', 1);
    tooltipLines << QString("  Ground Speed: %1 m/s").arg(m_dynamics.ground_speed, 0, 'f', 1);
    tooltipLines << QString("  Vertical Speed: %1 m/s").arg(m_dynamics.vertical_speed, 0, 'f', 1);
    tooltipLines << QString("  Pitch: %1°").arg(m_dynamics.pitch, 0, 'f', 1);
    tooltipLines << QString("  Roll: %1°").arg(m_dynamics.roll, 0, 'f', 1);
    tooltipLines << "";
    tooltipLines << QString("🔋 Power & Comms:");
    tooltipLines << QString("  Battery: %1%").arg(m_batteryLevel, 0, 'f', 1);
    tooltipLines << QString("  Voltage: %1V").arg(m_batteryVoltage, 0, 'f', 1);
    tooltipLines << QString("  Signal: %1%").arg(m_signalStrength, 0, 'f', 1);
    tooltipLines << "";
    tooltipLines << QString("🏥 Health: %1").arg(getHealthSummary());
    
    if (m_flightMode == DRONE_MODE_WAYPOINT && m_currentWaypointIndex >= 0 && m_currentWaypointIndex < m_waypoints.size()) {
        tooltipLines << "";
        tooltipLines << QString("🎯 Navigation:");
        tooltipLines << QString("  Waypoint: %1/%2").arg(m_currentWaypointIndex + 1).arg(m_waypoints.size());
        tooltipLines << QString("  Distance: %1 m").arg(getDistanceToWaypoint(m_currentWaypointIndex), 0, 'f', 1);
        tooltipLines << QString("  Bearing: %1°").arg(getBearingToWaypoint(m_currentWaypointIndex), 0, 'f', 1);
        tooltipLines << QString("  ETA: %1 s").arg(getTimeToWaypoint(m_currentWaypointIndex), 0, 'f', 1);
    }
    
    trackInfo.tooltip = tooltipLines.join("\n");
    
    return trackInfo;
}

double CDrone::getDistanceToWaypoint(int waypointIndex) const
{
    if (waypointIndex < 0 || waypointIndex >= m_waypoints.size()) {
        return 0.0;
    }
    
    const stDroneWaypoint& wp = m_waypoints[waypointIndex];
    
    // Haversine formula for distance calculation
    double lat1 = qDegreesToRadians(m_dynamics.latitude);
    double lon1 = qDegreesToRadians(m_dynamics.longitude);
    double lat2 = qDegreesToRadians(wp.lat);
    double lon2 = qDegreesToRadians(wp.lon);
    
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    
    double a = std::sin(dlat/2) * std::sin(dlat/2) + 
               std::cos(lat1) * std::cos(lat2) * 
               std::sin(dlon/2) * std::sin(dlon/2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));
    
    double distance2d = 6371000.0 * c; // Earth radius in meters
    double altDiff = wp.alt - m_dynamics.altitude;
    
    return std::sqrt(distance2d * distance2d + altDiff * altDiff);
}

double CDrone::getBearingToWaypoint(int waypointIndex) const
{
    if (waypointIndex < 0 || waypointIndex >= m_waypoints.size()) {
        return 0.0;
    }
    
    const stDroneWaypoint& wp = m_waypoints[waypointIndex];
    
    double lat1 = qDegreesToRadians(m_dynamics.latitude);
    double lon1 = qDegreesToRadians(m_dynamics.longitude);
    double lat2 = qDegreesToRadians(wp.lat);
    double lon2 = qDegreesToRadians(wp.lon);
    
    double dlon = lon2 - lon1;
    
    double y = std::sin(dlon) * std::cos(lat2);
    double x = std::cos(lat1) * std::sin(lat2) - std::sin(lat1) * std::cos(lat2) * std::cos(dlon);
    
    double bearing = qRadiansToDegrees(std::atan2(y, x));
    return fmod(bearing + 360.0, 360.0); // Normalize to 0-360
}

double CDrone::getTimeToWaypoint(int waypointIndex) const
{
    if (m_dynamics.ground_speed <= 0.1) {
        return -1.0; // Invalid/infinite time
    }
    
    double distance = getDistanceToWaypoint(waypointIndex);
    return distance / m_dynamics.ground_speed;
}

QString CDrone::getFlightModeString() const
{
    switch (m_flightMode) {
        case DRONE_MODE_MANUAL: return "MANUAL";
        case DRONE_MODE_AUTOPILOT: return "AUTOPILOT";
        case DRONE_MODE_WAYPOINT: return "WAYPOINT";
        case DRONE_MODE_LOITER: return "LOITER";
        case DRONE_MODE_RTH: return "RTH";
        case DRONE_MODE_EMERGENCY: return "EMERGENCY";
        default: return "UNKNOWN";
    }
}

QString CDrone::getSystemStatusString() const
{
    switch (m_systemStatus) {
        case DRONE_STATUS_INITIALIZING: return "INITIALIZING";
        case DRONE_STATUS_STANDBY: return "STANDBY";
        case DRONE_STATUS_ACTIVE: return "ACTIVE";
        case DRONE_STATUS_CRITICAL: return "CRITICAL";
        case DRONE_STATUS_EMERGENCY: return "EMERGENCY";
        case DRONE_STATUS_POWEROFF: return "POWEROFF";
        default: return "UNKNOWN";
    }
}

QString CDrone::getHealthSummary() const
{
    int healthyCount = 0;
    int totalSystems = 7;
    
    if (m_health.gps_healthy) healthyCount++;
    if (m_health.imu_healthy) healthyCount++;
    if (m_health.battery_healthy) healthyCount++;
    if (m_health.motor_healthy) healthyCount++;
    if (m_health.communication_healthy) healthyCount++;
    if (m_health.camera_healthy) healthyCount++;
    if (m_health.navigation_healthy) healthyCount++;
    
    if (healthyCount == totalSystems) {
        return "ALL SYSTEMS OK";
    } else if (healthyCount >= totalSystems * 0.8) {
        return "MOSTLY HEALTHY";
    } else if (healthyCount >= totalSystems * 0.5) {
        return "DEGRADED";
    } else {
        return "CRITICAL";
    }
}

void CDrone::updateDynamicsTimer()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    if (m_lastUpdateTime > 0) {
        double deltaTime = (currentTime - m_lastUpdateTime) / 1000.0; // Convert to seconds
        simulateDynamics(deltaTime);
    }
    m_lastUpdateTime = currentTime;
}

void CDrone::startDynamicsSimulation()
{
    m_lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
    m_dynamicsTimer->start(100); // Update every 100ms
    qDebug() << "Drone" << m_droneId << "dynamics simulation started";
}

void CDrone::stopDynamicsSimulation()
{
    m_dynamicsTimer->stop();
    qDebug() << "Drone" << m_droneId << "dynamics simulation stopped";
}

void CDrone::calculateGroundSpeed()
{
    m_dynamics.ground_speed = std::sqrt(
        m_dynamics.velocity_north * m_dynamics.velocity_north +
        m_dynamics.velocity_east * m_dynamics.velocity_east
    );
}

void CDrone::calculateHeadingError()
{
    double error = m_dynamics.desired_heading - m_dynamics.heading;
    
    // Normalize to -180 to +180
    while (error > 180.0) error -= 360.0;
    while (error < -180.0) error += 360.0;
    
    m_dynamics.heading_error = error;
}

void CDrone::updateNavigationToWaypoint()
{
    if (m_currentWaypointIndex < 0 || m_currentWaypointIndex >= m_waypoints.size()) {
        return;
    }
    
    // Calculate desired heading to current waypoint
    m_dynamics.desired_heading = getBearingToWaypoint(m_currentWaypointIndex);
    calculateHeadingError();
    
    // Calculate cross-track error (simplified)
    // This would normally be more complex for a full navigation system
    double distance = getDistanceToWaypoint(m_currentWaypointIndex);
    double bearingError = std::abs(m_dynamics.heading_error);
    m_dynamics.cross_track_error = distance * std::sin(qDegreesToRadians(bearingError));
}

void CDrone::checkWaypointReached()
{
    if (m_currentWaypointIndex < 0 || m_currentWaypointIndex >= m_waypoints.size()) {
        return;
    }
    
    double distance = getDistanceToWaypoint(m_currentWaypointIndex);
    
    if (distance <= WAYPOINT_TOLERANCE) {
        m_waypoints[m_currentWaypointIndex].reached = true;
        emit waypointReached(m_currentWaypointIndex);
        
        qDebug() << "Drone" << m_droneId << "reached waypoint" << m_currentWaypointIndex;
        
        // Move to next waypoint
        m_currentWaypointIndex++;
        if (m_currentWaypointIndex >= m_waypoints.size()) {
            // Mission complete
            m_currentWaypointIndex = -1;
            setFlightMode(DRONE_MODE_LOITER);
            qDebug() << "Drone" << m_droneId << "mission complete";
        }
    }
}

void CDrone::simulateRealisticDynamics(double deltaTime)
{
    // Simple physics simulation for demonstration
    // In a real system, this would be much more sophisticated
    
    if (m_flightMode == DRONE_MODE_WAYPOINT && m_currentWaypointIndex >= 0) {
        // Navigate towards waypoint
        double desiredHeading = getBearingToWaypoint(m_currentWaypointIndex);
        double headingError = desiredHeading - m_dynamics.heading;
        
        // Normalize heading error
        while (headingError > 180.0) headingError -= 360.0;
        while (headingError < -180.0) headingError += 360.0;
        
        // Apply heading correction (simple P controller)
        double maxTurnRate = 30.0; // degrees per second
        double turnRate = qBound(-maxTurnRate, headingError * 2.0, maxTurnRate);
        m_dynamics.heading += turnRate * deltaTime;
        
        // Normalize heading
        while (m_dynamics.heading >= 360.0) m_dynamics.heading -= 360.0;
        while (m_dynamics.heading < 0.0) m_dynamics.heading += 360.0;
        
        // Update velocity based on heading
        double desiredSpeed = 15.0; // m/s
        double headingRad = qDegreesToRadians(m_dynamics.heading);
        
        m_dynamics.velocity_north = desiredSpeed * std::cos(headingRad);
        m_dynamics.velocity_east = desiredSpeed * std::sin(headingRad);
        
        // Simple altitude control
        if (m_currentWaypointIndex < m_waypoints.size()) {
            double altError = m_waypoints[m_currentWaypointIndex].alt - m_dynamics.altitude;
            double maxClimbRate = 5.0; // m/s
            double climbRate = qBound(-maxClimbRate, altError * 0.5, maxClimbRate);
            m_dynamics.velocity_down = -climbRate; // Negative for up
        }
    }
    
    // Add some realistic noise and variations
    static int noiseCounter = 0;
    noiseCounter++;
    
    if (noiseCounter % 10 == 0) { // Every second at 100ms updates
        // Add small random variations to simulate real-world conditions
        m_dynamics.heading += (qrand() % 21 - 10) * 0.1; // ±1 degree noise
        m_dynamics.velocity_north += (qrand() % 21 - 10) * 0.01; // Small velocity noise
        m_dynamics.velocity_east += (qrand() % 21 - 10) * 0.01;
        
        // Simulate battery drain
        if (m_systemStatus == DRONE_STATUS_ACTIVE) {
            m_batteryLevel -= 0.01; // Drain 0.01% per second
            if (m_batteryLevel < 20.0 && m_batteryLevel > 19.0) {
                emit batteryLow(m_batteryLevel);
            }
        }
        
        // Update battery voltage based on level
        m_batteryVoltage = 10.5 + (m_batteryLevel / 100.0) * 2.1; // 10.5V to 12.6V
    }
}
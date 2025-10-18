#ifndef GLOBALSTRUCTS_H
#define GLOBALSTRUCTS_H
#include <QString>
#include <QList>
#include <QPointF>

enum eTrackIdentity {
    TRACK_IDENTITY_DEFAULT = 0,
    TRACK_IDENTITY_UNKNOWN = 1,
    TRACK_IDENTITY_FRIEND = 2,
    TRACK_IDENTITY_HOSTILE = 3,
};

// Structure to store a single history point
struct stTrackHistoryPoint {
    double lat;
    double lon;
    double alt;
    long long timestamp;
};

#pragma pack(1)
// Replace with your actual structure definition
struct stTrackRecvInfo {
    unsigned short usMsgId;    //!< Msg ID
    int nTrkId;                //!< Track ID
    float x;                   //!< X-coordinate
    float y;                   //!< Y-coordinate
    float z;                   //!< Z-coordinate
    float heading;             //!< Heading
    float velocity;            //!< Velocity
    int nTrackIden;
};

struct stTrackDisplayInfo {
    int nTrkId;                 //!< Track ID
    float x;                    //!< X-coordinate
    float y;                    //!< Y-coordinate
    float z;                    //!< Z-coordinate
    double lat;                 //!< Latitude
    double lon;                 //!< Longitude
    double alt;                 //!< Altitude
    double range;               //!< Range
    double azimuth;             //!< Azimuth
    double elevation;           //!< Elevation
    double heading;             //!< Heading
    double velocity;            //!< Velocity
    double snr;                 //!< SNR
    int nTrackIden;
    long long nTrackTime;
    QString tooltip;            //!< Tooltip information
    QList<stTrackHistoryPoint> historyPoints;  //!< Track history points
    bool showHistory;           //!< Flag to show/hide history trail
    
    // Drone-specific fields
    bool isDrone = false;               //!< Flag indicating if this is a drone track
    double pitch = 0.0;                 //!< Pitch angle (degrees)
    double roll = 0.0;                  //!< Roll angle (degrees)
    double verticalSpeed = 0.0;         //!< Vertical speed (m/s, positive up)
    double batteryLevel = 0.0;          //!< Battery level (0-100%)
    double signalStrength = 0.0;        //!< Signal strength (0-100%)
    QString flightMode;                 //!< Flight mode string
    QString systemStatus;               //!< System status string
    QString healthSummary;              //!< Health summary string
    int waypointIndex = -1;             //!< Current waypoint index (-1 if none)
    int totalWaypoints = 0;             //!< Total number of waypoints
};

#pragma pack()

#endif // GLOBALSTRUCTS_H

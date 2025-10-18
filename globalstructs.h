#ifndef GLOBALSTRUCTS_H
#define GLOBALSTRUCTS_H
#include <QString>

enum eTrackIdentity {
    TRACK_IDENTITY_DEFAULT = 0,
    TRACK_IDENTITY_UNKNOWN = 1,
    TRACK_IDENTITY_FRIEND = 2,
    TRACK_IDENTITY_HOSTILE = 3,
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
    QString tooltip;  // ADD THIS LINE
};

struct stTrackHistoryPoint {
    double lat;                 //!< Latitude at this point
    double lon;                 //!< Longitude at this point
    double alt;                 //!< Altitude at this point
    double heading;             //!< Heading at this point
    long long timestamp;        //!< Timestamp of this point
};

struct stTrackHistoryConfig {
    int maxHistoryPoints;       //!< Maximum number of history points to keep (default 50)
    bool showHistory;           //!< Whether to show history trails
    int historyLineWidth;       //!< Width of history trail lines
    double historyAlpha;        //!< Alpha transparency for history trails (0.0-1.0)
};

#pragma pack()

#endif // GLOBALSTRUCTS_H

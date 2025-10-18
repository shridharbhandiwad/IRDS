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
    QString tooltip;
    int nMaxHistoryPoints;      //!< Maximum number of history points (default: 20, max: 50)
    bool bHighlighted;          //!< Whether track is highlighted
    bool bFollowEnabled;        //!< Whether to follow track movement
    QString customImagePath;    //!< Custom image path for the track
    
    stTrackDisplayInfo() : nMaxHistoryPoints(20), bHighlighted(false), bFollowEnabled(false) {}
};

#pragma pack()

#endif // GLOBALSTRUCTS_H

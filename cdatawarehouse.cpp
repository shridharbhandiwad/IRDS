#include "cdatawarehouse.h"
#include <QMutexLocker>
#include "cudpreceiver.h"
#include <QDateTime>

// Initialize static member variables
CDataWarehouse* CDataWarehouse::_m_pInstance = nullptr;
QMutex CDataWarehouse::_m_mutex;

CDataWarehouse* CDataWarehouse::getInstance()
{
    // Thread-safe singleton instantiation using mutex lock
    if (_m_pInstance == nullptr) {
        QMutexLocker locker(&_m_mutex);
        if (_m_pInstance == nullptr) {
            _m_pInstance = new CDataWarehouse();
        }
    }
    return _m_pInstance;
}

CDataWarehouse::CDataWarehouse(QObject *parent) : QObject(parent)
{
    _m_RadarPos = QPointF(77.2946, 13.2716);
    
    // Initialize history configuration with defaults
    _m_historyConfig.maxHistoryPoints = 50;
    _m_historyConfig.showHistory = true;
    _m_historyConfig.historyLineWidth = 2;
    _m_historyConfig.historyAlpha = 0.7;

    stTrackRecvInfo info1;
    info1.nTrkId = 1;
    info1.x = 7000;
    info1.y = 0;
    info1.z = 0;
    info1.velocity = 20;
    info1.heading = 100;
    info1.nTrackIden = TRACK_IDENTITY_FRIEND;

    stTrackRecvInfo info2;
    info2.nTrkId = 2;
    info2.x = -4000;
    info2.y = 0;
    info2.z = 0;
    info2.velocity = 20;
    info2.heading = 200;
    info2.nTrackIden = TRACK_IDENTITY_HOSTILE;

    stTrackRecvInfo info3;
    info3.nTrkId = 3;
    info3.x = -2000;
    info3.y = 0;
    info3.z = 0;
    info3.velocity = 35;
    info3.heading = 200;
    info3.nTrackIden = TRACK_IDENTITY_UNKNOWN;


    slotUpdateTrackData(info1);
    slotUpdateTrackData(info2);
    slotUpdateTrackData(info3);

    connect(&_m_timeTrackTimeout,SIGNAL(timeout()),this,SLOT(slotClearTracksOnTimeOut()));
    _m_timeTrackTimeout.start(100000);

    _m_UdpRecvr.startListening(2025);
    connect(&_m_UdpRecvr,SIGNAL(signalUpdateTrackData(stTrackRecvInfo)),this,SLOT(slotUpdateTrackData(stTrackRecvInfo)));
}

QList<stTrackDisplayInfo> CDataWarehouse::getTrackList() {
    return _m_listTrackInfo.values();
}

void CDataWarehouse::slotClearTracksOnTimeOut() {

    QList<int> trackIds = _m_listTrackInfo.keys();
    for ( int trackId : trackIds  ) {
        stTrackDisplayInfo trackInfo = _m_listTrackInfo.value(trackId);
        if ( (trackInfo.nTrackTime + 10) < QDateTime::currentDateTime().toSecsSinceEpoch() ) {
            _m_listTrackInfo.remove(trackInfo.nTrkId);
        }
    }
}

void CDataWarehouse::slotUpdateTrackData(stTrackRecvInfo trackRecvInfo) {

    stTrackDisplayInfo info;
    info.nTrkId = trackRecvInfo.nTrkId;
    info.heading = trackRecvInfo.heading;
    info.nTrackIden = trackRecvInfo.nTrackIden;
    info.nTrackTime = QDateTime::currentDateTime().toSecsSinceEpoch();

    _m_CoordConv.env2geodetic(trackRecvInfo.x,trackRecvInfo.y,trackRecvInfo.z,
                              _m_RadarPos.y(),_m_RadarPos.x(),0,&info.lat,&info.lon,&info.alt,0);

    _m_CoordConv.env2polar(&info.range,&info.azimuth,&info.elevation,
                           trackRecvInfo.x,trackRecvInfo.y,trackRecvInfo.z);

    _m_listTrackInfo.insert(info.nTrkId,info);
    
    // Update track history if this track has history enabled
    if (_m_tracksWithHistoryEnabled.contains(info.nTrkId)) {
        stTrackHistoryPoint historyPoint;
        historyPoint.lat = info.lat;
        historyPoint.lon = info.lon;
        historyPoint.alt = info.alt;
        historyPoint.heading = info.heading;
        historyPoint.timestamp = info.nTrackTime;
        
        // Add to history
        _m_trackHistory[info.nTrkId].append(historyPoint);
        
        // Limit history points to configured maximum
        if (_m_trackHistory[info.nTrkId].size() > _m_historyConfig.maxHistoryPoints) {
            _m_trackHistory[info.nTrkId].removeFirst();
        }
    }
}

const QPointF CDataWarehouse::getRadarPos() {
    return _m_RadarPos;
}

QList<stTrackHistoryPoint> CDataWarehouse::getTrackHistory(int trackId) {
    return _m_trackHistory.value(trackId, QList<stTrackHistoryPoint>());
}

bool CDataWarehouse::toggleTrackHistory(int trackId) {
    if (_m_tracksWithHistoryEnabled.contains(trackId)) {
        // Disable history for this track
        _m_tracksWithHistoryEnabled.remove(trackId);
        _m_trackHistory.remove(trackId);
        return false;
    } else {
        // Enable history for this track
        _m_tracksWithHistoryEnabled.insert(trackId);
        
        // Add current position as first history point if track exists
        if (_m_listTrackInfo.contains(trackId)) {
            stTrackDisplayInfo currentTrack = _m_listTrackInfo.value(trackId);
            stTrackHistoryPoint historyPoint;
            historyPoint.lat = currentTrack.lat;
            historyPoint.lon = currentTrack.lon;
            historyPoint.alt = currentTrack.alt;
            historyPoint.heading = currentTrack.heading;
            historyPoint.timestamp = currentTrack.nTrackTime;
            
            _m_trackHistory[trackId].append(historyPoint);
        }
        return true;
    }
}

bool CDataWarehouse::isTrackHistoryEnabled(int trackId) {
    return _m_tracksWithHistoryEnabled.contains(trackId);
}

stTrackHistoryConfig CDataWarehouse::getHistoryConfig() {
    return _m_historyConfig;
}

void CDataWarehouse::setMaxHistoryPoints(int maxPoints) {
    if (maxPoints > 0 && maxPoints <= 1000) { // Reasonable limits
        _m_historyConfig.maxHistoryPoints = maxPoints;
        
        // Trim existing histories to new limit
        for (auto it = _m_trackHistory.begin(); it != _m_trackHistory.end(); ++it) {
            QList<stTrackHistoryPoint> &history = it.value();
            while (history.size() > maxPoints) {
                history.removeFirst();
            }
        }
    }
}

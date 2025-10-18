#ifndef CDATAWAREHOUSE_H
#define CDATAWAREHOUSE_H

#include <QObject>
#include "globalstructs.h"
#include <QMutex>
#include "cudpreceiver.h"
#include "CoordinateConverter.h"
#include <QPointF>
#include <QTimer>
#include <QSet>

class CDataWarehouse : public QObject
{
    Q_OBJECT

public :
    /**
     * @brief Gets the singleton instance of CDataWarehouse
     * @return Pointer to the singleton instance
     */
    static CDataWarehouse* getInstance();

    QList<stTrackDisplayInfo> getTrackList();
    
    /**
     * @brief Gets the history points for a specific track
     * @param trackId The track ID to get history for
     * @return List of history points for the track
     */
    QList<stTrackHistoryPoint> getTrackHistory(int trackId);
    
    /**
     * @brief Toggles history display for a specific track
     * @param trackId The track ID to toggle history for
     * @return true if history is now enabled, false if disabled
     */
    bool toggleTrackHistory(int trackId);
    
    /**
     * @brief Checks if history is enabled for a specific track
     * @param trackId The track ID to check
     * @return true if history is enabled, false otherwise
     */
    bool isTrackHistoryEnabled(int trackId);
    
    /**
     * @brief Gets the current history configuration
     * @return Current history configuration
     */
    stTrackHistoryConfig getHistoryConfig();
    
    /**
     * @brief Sets the maximum number of history points to keep
     * @param maxPoints Maximum number of history points (default 50)
     */
    void setMaxHistoryPoints(int maxPoints);

    const QPointF getRadarPos();
private slots:
    void slotUpdateTrackData(stTrackRecvInfo trackRecvInfo);
    void slotClearTracksOnTimeOut();
private:
    /**
     * @brief Private constructor for singleton pattern
     * @param pParent Optional QObject parent pointer
     */
    explicit CDataWarehouse(QObject *pParent = nullptr);

    QTimer _m_timeTrackTimeout;

    static CDataWarehouse*_m_pInstance;  //!< Singleton instance pointer
    static QMutex _m_mutex;                //!< Mutex for thread-safe singleton initialization


    QHash<int,stTrackDisplayInfo> _m_listTrackInfo;
    
    // History management
    QHash<int, QList<stTrackHistoryPoint>> _m_trackHistory;  //!< Track history points
    QSet<int> _m_tracksWithHistoryEnabled;                   //!< Tracks with history display enabled
    stTrackHistoryConfig _m_historyConfig;                   //!< History configuration

    CUdpReceiver _m_UdpRecvr;

    CoordinateConverter _m_CoordConv;

    QPointF _m_RadarPos;

};

#endif // CDATAWAREHOUSE_H

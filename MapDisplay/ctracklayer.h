//#ifndef CTRACKLAYER_H
//#define CTRACKLAYER_H

//#include <qgsmapcanvasitem.h>
//#include <qgsmapcanvas.h>
//#include <QTimer>

//class CTrackLayer : public QObject, public QgsMapCanvasItem
//{
//    Q_OBJECT
//public:
//    CTrackLayer(QgsMapCanvas *canvas);

//    void paint(QPainter *painter) override;
//    QRectF boundingRect() const override;

//private slots:
//    void _UpdateAnimation(); //!< Timer-based animation tick

//private:
//    QgsMapCanvas *m_canvas;
//    QTimer m_timer;
//};

//#endif // CTRACKLAYER_H


#ifndef CTRACKLAYER_H
#define CTRACKLAYER_H

#include <qgsmapcanvasitem.h>
#include <qgsmapcanvas.h>
#include <QTimer>

// Forward declaration
struct stTrackDisplayInfo;

class CTrackLayer : public QObject, public QgsMapCanvasItem
{
    Q_OBJECT
public:
    CTrackLayer(QgsMapCanvas *canvas);
    ~CTrackLayer();

    void paint(QPainter *painter) override;
    QRectF boundingRect() const override;

protected:
    /**
     * @brief Event filter to capture mouse events from canvas
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void _UpdateAnimation(); //!< Timer-based animation tick

signals:
    void trackRightClicked(int trackId, const QPoint& globalPos);

private:
    QgsMapCanvas *m_canvas;
    QTimer m_timer;

    // Tooltip support members
    int m_hoveredTrackId;      //!< Currently hovered track ID (-1 if none)
    QPointF m_mousePos;        //!< Current mouse position for tooltip placement

    /**
     * @brief Detects if a track is at the given position
     * @param pos Mouse position in screen coordinates
     * @return Track ID if found, -1 otherwise
     */
    int getTrackAtPosition(const QPointF &pos);

    /**
     * @brief Draws tooltip with track information
     * @param pPainter QPainter instance
     * @param trackInfo Track information to display
     * @param screenPos Screen position for tooltip
     */
    void drawTooltip(QPainter *pPainter, const stTrackDisplayInfo &trackInfo, const QPointF &screenPos);
};

#endif // CTRACKLAYER_H

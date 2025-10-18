//#include "ctracklayer.h"
//#include <qgsmaptopixel.h>
//#include <QtMath>
//#include <QPainter>
//#include  "../cdatawarehouse.h"
//#include "globalmacros.h"

//int nAnimFrame = 0;

///**
// * @brief CTrackLayer constructor
// * @param pCanvas Pointer to the QgsMapCanvas
// */

//CTrackLayer::CTrackLayer(QgsMapCanvas *canvas)
//    : QgsMapCanvasItem(canvas), m_canvas(canvas)
//{
//    setZValue(101); // Ensure drawing order: above base map, below UI overlays
//    QObject::connect(&m_timer, &QTimer::timeout, this, &CTrackLayer::_UpdateAnimation);
//    m_timer.start(150); // ~10 FPS for smooth animation
//}

///**
// * @brief Returns bounding rectangle for the layer — covers the whole canvas
// * @return QRectF bounding rectangle
// */
//QRectF CTrackLayer::boundingRect() const
//{
//    return m_canvas->rect();
//}

//void CTrackLayer::_UpdateAnimation()
//{
//    nAnimFrame = (nAnimFrame + 2) % 20; // Loop from 0–19
//    update(); // Redraw
//}

///**
// * @brief Paints the tracks on the canvas
// * @param pPainter QPainter instance used for drawing
// */
//void CTrackLayer::paint(QPainter *pPainter)
//{
//    if (!pPainter) return;

//    pPainter->setRenderHint(QPainter::Antialiasing, true);

//    // Transform geographic positions to screen coordinates
//    const QgsMapToPixel &mapToPixel = m_canvas->mapSettings().mapToPixel();

//    QList<stTrackDisplayInfo> listTracks = CDataWarehouse::getInstance()->getTrackList();

//    for (const stTrackDisplayInfo &track : listTracks) {
//        QPointF ptScreen = mapToPixel.transform(QgsPointXY(track.lon, track.lat)).toQPointF();
//        double pixelPerDegree = 1.0 / m_canvas->mapUnitsPerPixel();
//        QColor  clr = Qt::cyan;
//        switch (track.nTrackIden)  {
//        case TRACK_IDENTITY_UNKNOWN : clr = Qt::yellow;
//                break;
//        case TRACK_IDENTITY_FRIEND :  clr  = Qt::green;
//           break;
//        case TRACK_IDENTITY_HOSTILE : clr =  Qt::red;;
//           break;

//        }
//        if ( pixelPerDegree > PPI_VISIBLE_THRESHOLD ) {
//            // Core dot
//            pPainter->setPen(clr);
//            pPainter->setBrush(clr);
//            pPainter->drawEllipse(ptScreen, 4, 4);

//            // Heading line
//            double dHeadingRad = qDegreesToRadians(track.heading);
//            QPointF ptTip(
//                ptScreen.x() + std::cos(dHeadingRad) * 10,
//                ptScreen.y() - std::sin(dHeadingRad) * 10
//            );
//            pPainter->drawLine(ptScreen, ptTip);

//            if ( pixelPerDegree > TEXT_VISIBLE_THRESHOLD ) {
//                pPainter->setFont(QFont("century",11,80,true));
//                // Label
//                pPainter->setPen(Qt::white);
//                pPainter->drawText(ptScreen + QPointF(6, -6), QString::number(track.nTrkId));
//            }
//        }

//        // Glowing blip animation
//        int nMaxRadius = 20;
//        int nCurrentRadius = 4 + (nAnimFrame * (nMaxRadius - 4) / 20);
//        int nAlpha = 255 - (nAnimFrame * 255 / 20); // Fades out

//        // Gradient blip: transparent center → bright edge
//        QRadialGradient gradient(ptScreen, nCurrentRadius);
//        QColor clrEdge(clr.red(), clr.green(), clr.blue(), nAlpha);    // Bright neon green at edge
//        //QColor clrCenter(0, 255, 255, 0);       // Fully transparent center

//        gradient.setColorAt(0, Qt::cyan);
//        gradient.setColorAt(0.5, clr);   // Center of the blip
//        gradient.setColorAt(1.0, clrEdge);     // Edge of the blip

//        pPainter->setPen(Qt::NoPen);
//        pPainter->setBrush(gradient);
//        pPainter->drawEllipse(ptScreen, nCurrentRadius, nCurrentRadius);
//    }
//}


#include "ctracklayer.h"
#include <qgsmaptopixel.h>
#include <QtMath>
#include <QPainter>
#include "../cdatawarehouse.h"
#include "globalmacros.h"
#include <QDateTime>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int nAnimFrame = 0;

/**
 * @brief CTrackLayer constructor
 * @param pCanvas Pointer to the QgsMapCanvas
 */
CTrackLayer::CTrackLayer(QgsMapCanvas *canvas)
    : QgsMapCanvasItem(canvas), m_canvas(canvas), m_hoveredTrackId(-1), m_rightClickedTrackId(-1), 
      m_contextMenu(nullptr), m_focusedTrackId(-1)
{
    setZValue(101); // Ensure drawing order: above base map, below UI overlays
    QObject::connect(&m_timer, &QTimer::timeout, this, &CTrackLayer::_UpdateAnimation);
    m_timer.start(150); // ~10 FPS for smooth animation

    // Enable mouse tracking on the canvas
    m_canvas->viewport()->setMouseTracking(true);
    m_canvas->viewport()->installEventFilter(this);
    
    // Create context menu
    createContextMenu();
}

CTrackLayer::~CTrackLayer()
{
    if (m_canvas && m_canvas->viewport()) {
        m_canvas->viewport()->removeEventFilter(this);
    }
}

/**
 * @brief Returns bounding rectangle for the layer — covers the whole canvas
 * @return QRectF bounding rectangle
 */
QRectF CTrackLayer::boundingRect() const
{
    return m_canvas->rect();
}

void CTrackLayer::_UpdateAnimation()
{
    nAnimFrame = (nAnimFrame + 2) % 20; // Loop from 0–19
    update(); // Redraw
}

/**
 * @brief Event filter to capture mouse events
 */
bool CTrackLayer::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_canvas->viewport()) {
        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            m_mousePos = mouseEvent->pos();

            int trackId = getTrackAtPosition(m_mousePos);

            if (trackId != m_hoveredTrackId) {
                m_hoveredTrackId = trackId;
                update(); // Redraw to show/hide tooltip
            }

            // Change cursor when hovering over track
            if (trackId != -1) {
                m_canvas->setCursor(Qt::PointingHandCursor);
            } else {
                m_canvas->unsetCursor();
            }
        } else if (event->type() == QEvent::Leave) {
            if (m_hoveredTrackId != -1) {
                m_hoveredTrackId = -1;
                m_canvas->unsetCursor();
                update();
            }
        } else if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::RightButton) {
                m_mousePos = mouseEvent->pos();
                int trackId = getTrackAtPosition(m_mousePos);
                
                if (trackId != -1) {
                    m_rightClickedTrackId = trackId;
                    QPoint globalPos = m_canvas->viewport()->mapToGlobal(mouseEvent->pos());
                    m_contextMenu->exec(globalPos);
                    return true; // Consume the event
                }
            }
        }
    }

    return QObject::eventFilter(obj, event);
}

/**
 * @brief Creates the context menu for tracks
 */
void CTrackLayer::createContextMenu()
{
    m_contextMenu = new QMenu();
    
    QAction *focusAction = m_contextMenu->addAction("🎯 Focus Track");
    connect(focusAction, &QAction::triggered, this, &CTrackLayer::onFocusTrack);
    
    m_contextMenu->addSeparator();
    
    int historyLimit = CDataWarehouse::getInstance()->getHistoryLimit();
    QAction *historyAction = m_contextMenu->addAction(QString("📍 Toggle History (Max %1)").arg(historyLimit));
    connect(historyAction, &QAction::triggered, this, &CTrackLayer::onToggleTrackHistory);
    
    QAction *highlightAction = m_contextMenu->addAction("✨ Toggle Highlight");
    connect(highlightAction, &QAction::triggered, this, &CTrackLayer::onHighlightTrack);
    
    m_contextMenu->addSeparator();
    
    QAction *imageAction = m_contextMenu->addAction("🖼️ Load Track Image");
    connect(imageAction, &QAction::triggered, this, &CTrackLayer::onLoadTrackImage);
    
    m_contextMenu->addSeparator();
    
    QAction *deleteAction = m_contextMenu->addAction("🗑️ Delete Track");
    connect(deleteAction, &QAction::triggered, this, &CTrackLayer::onDeleteTrack);
    
    // Style the context menu
    m_contextMenu->setStyleSheet(
        "QMenu {"
        "   background-color: #ffffff;"
        "   color: #1e293b;"
        "   border: 2px solid #e2e8f0;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "}"
        "QMenu::item {"
        "   padding: 8px 24px;"
        "   border-radius: 4px;"
        "   font-weight: 500;"
        "}"
        "QMenu::item:selected {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3b82f6, stop:1 #2563eb);"
        "   color: white;"
        "}"
        "QMenu::separator {"
        "   height: 1px;"
        "   background-color: #e2e8f0;"
        "   margin: 4px 16px;"
        "}"
    );
}

/**
 * @brief Context menu action slots
 */
void CTrackLayer::onFocusTrack()
{
    if (m_rightClickedTrackId == -1) return;
    
    // Toggle focus state
    if (m_focusedTrackId == m_rightClickedTrackId) {
        m_focusedTrackId = -1;
        qDebug() << "Unfocused track" << m_rightClickedTrackId;
    } else {
        m_focusedTrackId = m_rightClickedTrackId;
        qDebug() << "Focused on track" << m_rightClickedTrackId;
        
        // Center the canvas on the focused track
        QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
        for (const stTrackDisplayInfo &track : tracks) {
            if (track.nTrkId == m_rightClickedTrackId) {
                QgsPointXY centerPoint(track.lon, track.lat);
                m_canvas->setCenter(centerPoint);
                m_canvas->refresh();
                break;
            }
        }
    }
    
    update(); // Redraw to show focus changes
}

void CTrackLayer::onDeleteTrack()
{
    if (m_rightClickedTrackId == -1) return;
    
    // Remove from highlight and focus sets if present
    m_highlightedTracks.remove(m_rightClickedTrackId);
    if (m_focusedTrackId == m_rightClickedTrackId) {
        m_focusedTrackId = -1;
    }
    
    // Delete track from data warehouse
    CDataWarehouse::getInstance()->deleteTrack(m_rightClickedTrackId);
    qDebug() << "Track" << m_rightClickedTrackId << "deleted";
    
    update(); // Redraw to reflect changes
}

void CTrackLayer::onLoadTrackImage()
{
    if (m_rightClickedTrackId == -1) return;
    
    QString filter = "Image Files (*.png *.jpg *.jpeg *.bmp *.gif)";
    QString imagePath = QFileDialog::getOpenFileName(
        nullptr,
        QString("Load Image for Track #%1").arg(m_rightClickedTrackId),
        QString(),
        filter
    );
    
    if (!imagePath.isEmpty()) {
        qDebug() << "Load image for track" << m_rightClickedTrackId << ":" << imagePath;
        // TODO: Implement track image display
    }
}

void CTrackLayer::onToggleTrackHistory()
{
    if (m_rightClickedTrackId == -1) return;
    
    CDataWarehouse::getInstance()->toggleTrackHistory(m_rightClickedTrackId);
    qDebug() << "Toggle history for track" << m_rightClickedTrackId;
    
    // Force redraw to show/hide history
    update();
}

void CTrackLayer::onHighlightTrack()
{
    if (m_rightClickedTrackId == -1) return;
    
    if (m_highlightedTracks.contains(m_rightClickedTrackId)) {
        m_highlightedTracks.remove(m_rightClickedTrackId);
        qDebug() << "Removed highlight from track" << m_rightClickedTrackId;
    } else {
        m_highlightedTracks.insert(m_rightClickedTrackId);
        qDebug() << "Highlighted track" << m_rightClickedTrackId;
    }
    
    update(); // Redraw to show highlight changes
}

/**
 * @brief Detects if mouse is hovering over a track
 * @param pos Mouse position in screen coordinates
 * @return Track ID if hovering over a track, -1 otherwise
 */
int CTrackLayer::getTrackAtPosition(const QPointF &pos)
{
    const QgsMapToPixel &mapToPixel = m_canvas->mapSettings().mapToPixel();
    QList<stTrackDisplayInfo> listTracks = CDataWarehouse::getInstance()->getTrackList();

    // Detection radius in pixels
    const double detectionRadius = 20.0;

    for (const stTrackDisplayInfo &track : listTracks) {
        QPointF ptScreen = mapToPixel.transform(QgsPointXY(track.lon, track.lat)).toQPointF();

        // Calculate distance from mouse to track
        double distance = QLineF(pos, ptScreen).length();

        if (distance <= detectionRadius) {
            return track.nTrkId;
        }
    }

    return -1; // No track found
}

/**
 * @brief Draws the tooltip for the hovered track
 * @param pPainter QPainter instance
 * @param trackInfo Track information to display
 * @param screenPos Position on screen where to draw tooltip
 */
void CTrackLayer::drawTooltip(QPainter *pPainter, const stTrackDisplayInfo &trackInfo, const QPointF &screenPos)
{
    // Determine identity display
    QString identityStr;
    QString identityIcon;
    QColor identityColor;

    switch(trackInfo.nTrackIden) {
        case TRACK_IDENTITY_FRIEND:
            identityStr = "FRIENDLY";
            identityIcon = "✓";
            identityColor = QColor(46, 204, 113); // Modern green
            break;
        case TRACK_IDENTITY_HOSTILE:
            identityStr = "HOSTILE";
            identityIcon = "✖";
            identityColor = QColor(231, 76, 60); // Modern red
            break;
        case TRACK_IDENTITY_UNKNOWN:
            identityStr = "UNKNOWN";
            identityIcon = "?";
            identityColor = QColor(241, 196, 15); // Modern yellow
            break;
        default:
            identityStr = "UNDEFINED";
            identityIcon = "•";
            identityColor = QColor(149, 165, 166);
            break;
    }

    // Minimal tooltip content
    QStringList lines;
    lines << QString("ID %1").arg(trackInfo.nTrkId);
    lines << QString("%1 %2").arg(identityIcon).arg(identityStr);
    lines << "";
    lines << QString("📍 %1°, %2°").arg(trackInfo.lat, 0, 'f', 4).arg(trackInfo.lon, 0, 'f', 4);
    lines << QString("📏 %1 km").arg(trackInfo.range / 1000.0, 0, 'f', 1);
    lines << QString("🧭 %1°").arg(trackInfo.heading, 0, 'f', 0);
    lines << QString("⬆ %1 m").arg(trackInfo.alt, 0, 'f', 0);

    // Calculate dimensions
    QFont tooltipFont("Segoe UI", 10);
    pPainter->setFont(tooltipFont);
    QFontMetrics fm(tooltipFont);

    int maxWidth = 0;
    for (const QString &line : lines) {
        int lineWidth = fm.horizontalAdvance(line);
        if (lineWidth > maxWidth) {
            maxWidth = lineWidth;
        }
    }

    int padding = 15;
    int tooltipWidth = maxWidth + padding * 2;
    int lineHeight = fm.height() + 3;
    int tooltipHeight = lines.count() * lineHeight + padding * 2;

    // Position tooltip
    QPointF tooltipPos = screenPos + QPointF(25, -tooltipHeight / 2);

    // Keep within bounds
    if (tooltipPos.x() + tooltipWidth > m_canvas->width()) {
        tooltipPos.setX(screenPos.x() - tooltipWidth - 25);
    }
    if (tooltipPos.y() < 5) {
        tooltipPos.setY(5);
    }
    if (tooltipPos.y() + tooltipHeight > m_canvas->height()) {
        tooltipPos.setY(m_canvas->height() - tooltipHeight - 5);
    }

    QRectF tooltipRect(tooltipPos, QSizeF(tooltipWidth, tooltipHeight));

    // Draw subtle outer glow
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(QColor(0, 0, 0, 30));
    pPainter->drawRoundedRect(tooltipRect.adjusted(-2, -2, 2, 2), 12, 12);

    // Main background - highly transparent glass effect
    QLinearGradient bgGradient(tooltipRect.topLeft(), tooltipRect.bottomLeft());
    bgGradient.setColorAt(0, QColor(30, 30, 40, 120)); // More transparent
    bgGradient.setColorAt(1, QColor(20, 20, 30, 140)); // More transparent

    pPainter->setBrush(bgGradient);
    pPainter->setPen(Qt::NoPen);
    pPainter->drawRoundedRect(tooltipRect, 10, 10);

    // Glossy top highlight - very subtle
    QLinearGradient glossGradient(tooltipRect.topLeft(),
                                   QPointF(tooltipRect.left(), tooltipRect.top() + tooltipRect.height() * 0.3));
    glossGradient.setColorAt(0, QColor(255, 255, 255, 20));
    glossGradient.setColorAt(1, QColor(255, 255, 255, 0));

    pPainter->setBrush(glossGradient);
    pPainter->drawRoundedRect(tooltipRect, 10, 10);

    // Accent line on left side - semi-transparent
    QRectF accentRect(tooltipPos.x(), tooltipPos.y() + 5, 4, tooltipHeight - 10);
    pPainter->setPen(Qt::NoPen);
    QColor accentColor = identityColor;
    accentColor.setAlpha(180);
    pPainter->setBrush(accentColor);
    pPainter->drawRoundedRect(accentRect, 2, 2);

    // Draw text with subtle shadow
    int yOffset = padding + fm.ascent();

    for (int i = 0; i < lines.count(); i++) {
        const QString &line = lines[i];

        if (line.isEmpty()) {
            yOffset += lineHeight / 2;
            continue;
        }

        // Text shadow
        pPainter->setPen(QColor(0, 0, 0, 120));
        pPainter->drawText(QPointF(tooltipPos.x() + padding + 1, tooltipPos.y() + yOffset + 1), line);

        // Main text with colors
        if (i == 0) {
            // Track ID - bright cyan
            pPainter->setFont(QFont("Segoe UI", 11, QFont::Bold));
            pPainter->setPen(QColor(100, 200, 255));
        } else if (i == 1) {
            // Identity - use identity color
            pPainter->setFont(QFont("Segoe UI", 10, QFont::Bold));
            pPainter->setPen(identityColor);
        } else {
            // Regular info - bright for visibility on transparent bg
            pPainter->setFont(QFont("Segoe UI", 9));
            pPainter->setPen(QColor(240, 240, 240));
        }

        pPainter->drawText(QPointF(tooltipPos.x() + padding, tooltipPos.y() + yOffset), line);
        yOffset += lineHeight;
    }

    // Add small connection line from tooltip to track
    QPainterPath connectorPath;
    if (tooltipPos.x() > screenPos.x()) {
        // Tooltip on right
        connectorPath.moveTo(tooltipPos.x(), tooltipPos.y() + tooltipHeight / 2);
        connectorPath.lineTo(screenPos.x() + 10, screenPos.y());
    } else {
        // Tooltip on left
        connectorPath.moveTo(tooltipPos.x() + tooltipWidth, tooltipPos.y() + tooltipHeight / 2);
        connectorPath.lineTo(screenPos.x() - 10, screenPos.y());
    }

    QColor connectorColor = identityColor;
    connectorColor.setAlpha(120);
    pPainter->setPen(QPen(connectorColor, 1.5, Qt::DotLine));
    pPainter->setBrush(Qt::NoBrush);
    pPainter->drawPath(connectorPath);
}

/**
 * @brief Draws speed vector for a track
 * @param pPainter QPainter instance
 * @param trackInfo Track information
 * @param screenPos Screen position of track
 * @param trackColor Color of the track
 */
void CTrackLayer::drawSpeedVector(QPainter *pPainter, const stTrackDisplayInfo &trackInfo, 
                                 const QPointF &screenPos, const QColor &trackColor)
{
    if (trackInfo.velocity <= 0) return; // No vector for stationary targets
    
    // Calculate speed vector length (proportional to speed)
    // Scale factor: 1 m/s = 2 pixels, max length = 50 pixels
    double speedScale = 2.0;
    double maxVectorLength = 50.0;
    double vectorLength = qMin(trackInfo.velocity * speedScale, maxVectorLength);
    
    // Calculate speed vector direction (same as heading)
    double speedHeadingRad = qDegreesToRadians(trackInfo.heading);
    QPointF vectorEnd(
        screenPos.x() + std::cos(speedHeadingRad) * vectorLength,
        screenPos.y() - std::sin(speedHeadingRad) * vectorLength
    );
    
    // Draw speed vector line
    QColor vectorColor = trackColor;
    vectorColor.setAlpha(200);
    pPainter->setPen(QPen(vectorColor, 2, Qt::SolidLine));
    pPainter->drawLine(screenPos, vectorEnd);
    
    // Draw arrowhead at the end
    double arrowSize = 6.0;
    double arrowAngle = M_PI / 6; // 30 degrees
    
    QPointF arrowP1(
        vectorEnd.x() - arrowSize * std::cos(speedHeadingRad - arrowAngle),
        vectorEnd.y() + arrowSize * std::sin(speedHeadingRad - arrowAngle)
    );
    QPointF arrowP2(
        vectorEnd.x() - arrowSize * std::cos(speedHeadingRad + arrowAngle),
        vectorEnd.y() + arrowSize * std::sin(speedHeadingRad + arrowAngle)
    );
    
    pPainter->setPen(QPen(vectorColor, 2, Qt::SolidLine));
    pPainter->drawLine(vectorEnd, arrowP1);
    pPainter->drawLine(vectorEnd, arrowP2);
    
    // Optional: Draw speed text near the vector
    if (vectorLength > 20) { // Only show text if vector is long enough
        pPainter->setFont(QFont("Arial", 8));
        pPainter->setPen(Qt::white);
        QString speedText = QString("%1 m/s").arg(trackInfo.velocity, 0, 'f', 1);
        QPointF textPos = screenPos + QPointF(vectorLength * 0.6 * std::cos(speedHeadingRad), 
                                             -vectorLength * 0.6 * std::sin(speedHeadingRad));
        pPainter->drawText(textPos, speedText);
    }
}

/**
 * @brief Draws focused track datatip that follows the track
 * @param pPainter QPainter instance
 * @param trackInfo Track information
 * @param screenPos Screen position of track
 */
void CTrackLayer::drawFocusedTrackDatatip(QPainter *pPainter, const stTrackDisplayInfo &trackInfo, 
                                         const QPointF &screenPos)
{
    // Use a modified version of the tooltip for focused tracks
    // This will always be visible and follow the track
    
    // Determine identity display
    QString identityStr;
    QString identityIcon;
    QColor identityColor;

    switch(trackInfo.nTrackIden) {
        case TRACK_IDENTITY_FRIEND:
            identityStr = "FRIENDLY";
            identityIcon = "✓";
            identityColor = QColor(46, 204, 113);
            break;
        case TRACK_IDENTITY_HOSTILE:
            identityStr = "HOSTILE";
            identityIcon = "✖";
            identityColor = QColor(231, 76, 60);
            break;
        case TRACK_IDENTITY_UNKNOWN:
            identityStr = "UNKNOWN";
            identityIcon = "?";
            identityColor = QColor(241, 196, 15);
            break;
        default:
            identityStr = "UNDEFINED";
            identityIcon = "•";
            identityColor = QColor(149, 165, 166);
            break;
    }

    // Focused track tooltip content (more compact)
    QStringList lines;
    lines << QString("🎯 FOCUSED: ID %1").arg(trackInfo.nTrkId);
    lines << QString("%1 %2").arg(identityIcon).arg(identityStr);
    lines << QString("🚀 %1 m/s").arg(trackInfo.velocity, 0, 'f', 1);
    lines << QString("🧭 %1°").arg(trackInfo.heading, 0, 'f', 0);

    // Calculate dimensions
    QFont tooltipFont("Segoe UI", 9, QFont::Bold);
    pPainter->setFont(tooltipFont);
    QFontMetrics fm(tooltipFont);

    int maxWidth = 0;
    for (const QString &line : lines) {
        int lineWidth = fm.horizontalAdvance(line);
        if (lineWidth > maxWidth) {
            maxWidth = lineWidth;
        }
    }

    int padding = 10;
    int tooltipWidth = maxWidth + padding * 2;
    int lineHeight = fm.height() + 2;
    int tooltipHeight = lines.count() * lineHeight + padding * 2;

    // Position tooltip above and to the right of track
    QPointF tooltipPos = screenPos + QPointF(15, -tooltipHeight - 15);

    // Keep within bounds
    if (tooltipPos.x() + tooltipWidth > m_canvas->width()) {
        tooltipPos.setX(screenPos.x() - tooltipWidth - 15);
    }
    if (tooltipPos.y() < 5) {
        tooltipPos.setY(screenPos.y() + 15);
    }

    QRectF tooltipRect(tooltipPos, QSizeF(tooltipWidth, tooltipHeight));

    // Draw focused tooltip with stronger background
    QLinearGradient bgGradient(tooltipRect.topLeft(), tooltipRect.bottomLeft());
    bgGradient.setColorAt(0, QColor(30, 30, 40, 200));
    bgGradient.setColorAt(1, QColor(20, 20, 30, 220));

    pPainter->setBrush(bgGradient);
    pPainter->setPen(QPen(identityColor, 2));
    pPainter->drawRoundedRect(tooltipRect, 8, 8);

    // Draw text
    int yOffset = padding + fm.ascent();
    for (int i = 0; i < lines.count(); i++) {
        const QString &line = lines[i];

        if (i == 0) {
            // Focused header - bright cyan
            pPainter->setPen(QColor(100, 200, 255));
        } else if (i == 1) {
            // Identity - use identity color
            pPainter->setPen(identityColor);
        } else {
            // Regular info - bright white
            pPainter->setPen(QColor(255, 255, 255));
        }

        pPainter->drawText(QPointF(tooltipPos.x() + padding, tooltipPos.y() + yOffset), line);
        yOffset += lineHeight;
    }
}

/**
 * @brief Paints the tracks on the canvas
 * @param pPainter QPainter instance used for drawing
 */
void CTrackLayer::paint(QPainter *pPainter)
{
    if (!pPainter) return;

    pPainter->setRenderHint(QPainter::Antialiasing, true);

    // Transform geographic positions to screen coordinates
    const QgsMapToPixel &mapToPixel = m_canvas->mapSettings().mapToPixel();

    QList<stTrackDisplayInfo> listTracks = CDataWarehouse::getInstance()->getTrackList();

    stTrackDisplayInfo hoveredTrack;
    bool hasHoveredTrack = false;

    for (const stTrackDisplayInfo &track : listTracks) {
        QPointF ptScreen = mapToPixel.transform(QgsPointXY(track.lon, track.lat)).toQPointF();
        double pixelPerDegree = 1.0 / m_canvas->mapUnitsPerPixel();
        QColor clr = Qt::cyan;

        // Check track states
        bool isHovered = (track.nTrkId == m_hoveredTrackId);
        bool isHighlighted = m_highlightedTracks.contains(track.nTrkId);
        bool isFocused = (track.nTrkId == m_focusedTrackId);
        
        if (isHovered) {
            hoveredTrack = track;
            hasHoveredTrack = true;
        }

        switch (track.nTrackIden) {
        case TRACK_IDENTITY_UNKNOWN:
            clr = Qt::yellow;
            break;
        case TRACK_IDENTITY_FRIEND:
            clr = Qt::green;
            break;
        case TRACK_IDENTITY_HOSTILE:
            clr = Qt::red;
            break;
        }

        if (pixelPerDegree > PPI_VISIBLE_THRESHOLD) {
            // Determine track size based on state
            double trackSize = 4;
            if (isHighlighted) trackSize = 8;  // Larger for highlighted tracks
            if (isFocused) trackSize = 10;     // Even larger for focused tracks
            
            // Highlight effects
            if (isHighlighted || isFocused) {
                // Outer highlight ring
                pPainter->setPen(QPen(Qt::white, 3));
                pPainter->setBrush(Qt::NoBrush);
                pPainter->drawEllipse(ptScreen, trackSize + 6, trackSize + 6);

                // Inner glow effect
                pPainter->setPen(QPen(clr, 2));
                pPainter->drawEllipse(ptScreen, trackSize + 3, trackSize + 3);
            }
            
            // Hover effect (additional to highlight/focus)
            if (isHovered) {
                pPainter->setPen(QPen(Qt::cyan, 2));
                pPainter->setBrush(Qt::NoBrush);
                pPainter->drawEllipse(ptScreen, trackSize + 8, trackSize + 8);
            }

            // Core dot
            pPainter->setPen(clr);
            pPainter->setBrush(clr);
            pPainter->drawEllipse(ptScreen, trackSize, trackSize);

            // Draw speed vector instead of simple heading line
            drawSpeedVector(pPainter, track, ptScreen, clr);

            if (pixelPerDegree > TEXT_VISIBLE_THRESHOLD) {
                pPainter->setFont(QFont("century", 11, 80, true));
                // Label
                pPainter->setPen(Qt::white);
                pPainter->drawText(ptScreen + QPointF(6, -6), QString::number(track.nTrkId));
            }
        }

        // Glowing blip animation
        int nMaxRadius = 20;
        int nCurrentRadius = 4 + (nAnimFrame * (nMaxRadius - 4) / 20);
        int nAlpha = 255 - (nAnimFrame * 255 / 20); // Fades out

        // Gradient blip: transparent center → bright edge
        QRadialGradient gradient(ptScreen, nCurrentRadius);
        QColor clrEdge(clr.red(), clr.green(), clr.blue(), nAlpha);

        gradient.setColorAt(0, Qt::cyan);
        gradient.setColorAt(0.5, clr);
        gradient.setColorAt(1.0, clrEdge);

        pPainter->setPen(Qt::NoPen);
        pPainter->setBrush(gradient);
        pPainter->drawEllipse(ptScreen, nCurrentRadius, nCurrentRadius);
        
        // Draw history trail if enabled
        if (track.showHistory && !track.historyPoints.isEmpty()) {
            QPainterPath historyPath;
            bool firstPoint = true;
            
            // Calculate fade effect based on history point age
            int totalPoints = track.historyPoints.size();
            
            for (int i = 0; i < totalPoints; ++i) {
                const stTrackHistoryPoint &histPoint = track.historyPoints[i];
                QPointF histScreen = mapToPixel.transform(QgsPointXY(histPoint.lon, histPoint.lat)).toQPointF();
                
                if (firstPoint) {
                    historyPath.moveTo(histScreen);
                    firstPoint = false;
                } else {
                    historyPath.lineTo(histScreen);
                }
                
                // Draw small dot for each history point with fading effect
                // Older points are more transparent
                int alpha = 50 + (i * 150 / totalPoints);  // Fade from 50 to 200
                QColor dotColor = clr;
                dotColor.setAlpha(alpha);
                
                pPainter->setPen(Qt::NoPen);
                pPainter->setBrush(dotColor);
                pPainter->drawEllipse(histScreen, 2, 2);
            }
            
            // Draw the history trail line
            QColor trailColor = clr;
            trailColor.setAlpha(120);
            pPainter->setPen(QPen(trailColor, 2, Qt::DashLine));
            pPainter->setBrush(Qt::NoBrush);
            pPainter->drawPath(historyPath);
            
            // Draw line from last history point to current position
            if (!track.historyPoints.isEmpty()) {
                const stTrackHistoryPoint &lastPoint = track.historyPoints.last();
                QPointF lastScreen = mapToPixel.transform(QgsPointXY(lastPoint.lon, lastPoint.lat)).toQPointF();
                
                QColor connectColor = clr;
                connectColor.setAlpha(180);
                pPainter->setPen(QPen(connectColor, 2, Qt::SolidLine));
                pPainter->drawLine(lastScreen, ptScreen);
            }
        }
    }

    // Draw focused track datatip (always visible, follows track)
    if (m_focusedTrackId != -1) {
        for (const stTrackDisplayInfo &track : listTracks) {
            if (track.nTrkId == m_focusedTrackId) {
                QPointF focusedScreen = mapToPixel.transform(QgsPointXY(track.lon, track.lat)).toQPointF();
                drawFocusedTrackDatatip(pPainter, track, focusedScreen);
                break;
            }
        }
    }
    
    // Draw tooltip for hovered track (draw last so it's on top, but not for focused tracks)
    if (hasHoveredTrack && m_hoveredTrackId != -1 && m_hoveredTrackId != m_focusedTrackId) {
        drawTooltip(pPainter, hoveredTrack, m_mousePos);
    }
    
    // Draw drone internal details for all drone tracks
    for (const stTrackDisplayInfo &track : listTracks) {
        if (track.isDrone) {
            QPointF droneScreen = mapToPixel.transform(QgsPointXY(track.lon, track.lat)).toQPointF();
            drawDroneInternalDetails(pPainter, track, droneScreen);
        }
    }
}

/**
 * @brief Draws drone-specific internal details
 */
void CTrackLayer::drawDroneInternalDetails(QPainter *pPainter, const stTrackDisplayInfo &trackInfo, 
                                          const QPointF &screenPos)
{
    if (!trackInfo.isDrone) return;
    
    double pixelPerDegree = 1.0 / m_canvas->mapUnitsPerPixel();
    
    // Only draw details at appropriate zoom levels
    if (pixelPerDegree < PPI_VISIBLE_THRESHOLD * 2) return;
    
    // Draw attitude indicator
    drawDroneAttitudeIndicator(pPainter, trackInfo, screenPos, 25.0);
    
    // Draw health status indicators
    drawDroneHealthStatus(pPainter, trackInfo, screenPos);
    
    // Draw battery level indicator
    QRectF batteryRect(screenPos.x() + 35, screenPos.y() - 15, 20, 8);
    
    // Battery outline
    pPainter->setPen(QPen(Qt::white, 1));
    pPainter->setBrush(Qt::NoBrush);
    pPainter->drawRect(batteryRect);
    
    // Battery terminal
    QRectF terminalRect(batteryRect.right(), batteryRect.y() + 2, 2, 4);
    pPainter->setBrush(Qt::white);
    pPainter->drawRect(terminalRect);
    
    // Battery level fill
    double fillWidth = batteryRect.width() * (trackInfo.batteryLevel / 100.0);
    QRectF fillRect(batteryRect.x(), batteryRect.y(), fillWidth, batteryRect.height());
    
    QColor batteryColor;
    if (trackInfo.batteryLevel > 50) {
        batteryColor = Qt::green;
    } else if (trackInfo.batteryLevel > 20) {
        batteryColor = Qt::yellow;
    } else {
        batteryColor = Qt::red;
    }
    
    pPainter->setBrush(batteryColor);
    pPainter->setPen(Qt::NoPen);
    pPainter->drawRect(fillRect);
    
    // Battery percentage text
    pPainter->setFont(QFont("Arial", 7));
    pPainter->setPen(Qt::white);
    pPainter->drawText(batteryRect.adjusted(0, -12, 0, 0), Qt::AlignCenter, 
                      QString("%1%").arg(trackInfo.batteryLevel, 0, 'f', 0));
    
    // Signal strength indicator
    QPointF signalPos(screenPos.x() + 35, screenPos.y() + 25);
    int signalBars = qRound(trackInfo.signalStrength / 25.0); // 0-4 bars
    
    for (int i = 0; i < 4; i++) {
        QRectF barRect(signalPos.x() + i * 4, signalPos.y() - (i + 1) * 2, 3, (i + 1) * 2);
        
        if (i < signalBars) {
            if (trackInfo.signalStrength > 75) {
                pPainter->setBrush(Qt::green);
            } else if (trackInfo.signalStrength > 50) {
                pPainter->setBrush(Qt::yellow);
            } else {
                pPainter->setBrush(Qt::red);
            }
        } else {
            pPainter->setBrush(QColor(100, 100, 100, 100));
        }
        
        pPainter->setPen(Qt::NoPen);
        pPainter->drawRect(barRect);
    }
    
    // Flight mode indicator
    pPainter->setFont(QFont("Arial", 8, QFont::Bold));
    pPainter->setPen(Qt::cyan);
    pPainter->drawText(screenPos + QPointF(-30, 35), trackInfo.flightMode);
    
    // System status indicator
    QColor statusColor;
    if (trackInfo.systemStatus == "ACTIVE") {
        statusColor = Qt::green;
    } else if (trackInfo.systemStatus == "CRITICAL") {
        statusColor = Qt::red;
    } else if (trackInfo.systemStatus == "STANDBY") {
        statusColor = Qt::yellow;
    } else {
        statusColor = Qt::gray;
    }
    
    pPainter->setPen(statusColor);
    pPainter->drawText(screenPos + QPointF(-30, 45), trackInfo.systemStatus);
    
    // Waypoint progress indicator
    if (trackInfo.waypointIndex >= 0 && trackInfo.totalWaypoints > 0) {
        pPainter->setFont(QFont("Arial", 7));
        pPainter->setPen(Qt::white);
        QString waypointText = QString("WP %1/%2").arg(trackInfo.waypointIndex + 1).arg(trackInfo.totalWaypoints);
        pPainter->drawText(screenPos + QPointF(35, 45), waypointText);
        
        // Progress bar
        QRectF progressRect(screenPos.x() + 35, screenPos.y() + 50, 30, 4);
        pPainter->setPen(QPen(Qt::white, 1));
        pPainter->setBrush(Qt::NoBrush);
        pPainter->drawRect(progressRect);
        
        double progress = (double)(trackInfo.waypointIndex + 1) / trackInfo.totalWaypoints;
        QRectF progressFill(progressRect.x(), progressRect.y(), 
                           progressRect.width() * progress, progressRect.height());
        pPainter->setBrush(Qt::cyan);
        pPainter->setPen(Qt::NoPen);
        pPainter->drawRect(progressFill);
    }
}

/**
 * @brief Draws drone attitude indicator (pitch/roll visualization)
 */
void CTrackLayer::drawDroneAttitudeIndicator(QPainter *pPainter, const stTrackDisplayInfo &trackInfo, 
                                            const QPointF &screenPos, double size)
{
    if (!trackInfo.isDrone) return;
    
    pPainter->save();
    
    // Translate to drone position
    pPainter->translate(screenPos);
    
    // Draw attitude indicator circle
    pPainter->setPen(QPen(Qt::white, 2));
    pPainter->setBrush(QColor(0, 0, 0, 100));
    pPainter->drawEllipse(QRectF(-size/2, -size/2, size, size));
    
    // Draw horizon line (affected by roll)
    pPainter->rotate(trackInfo.roll);
    
    // Horizon line
    double horizonOffset = (trackInfo.pitch / 90.0) * (size / 4); // Scale pitch to indicator
    pPainter->setPen(QPen(Qt::green, 2));
    pPainter->drawLine(QPointF(-size/3, horizonOffset), QPointF(size/3, horizonOffset));
    
    // Sky/ground representation
    if (std::abs(trackInfo.pitch) < 45) {
        QRectF skyRect(-size/2, -size/2, size, size/2 + horizonOffset);
        QRectF groundRect(-size/2, horizonOffset, size, size/2 - horizonOffset);
        
        pPainter->setPen(Qt::NoPen);
        pPainter->setBrush(QColor(135, 206, 235, 100)); // Sky blue
        pPainter->drawRect(skyRect);
        
        pPainter->setBrush(QColor(139, 69, 19, 100)); // Brown ground
        pPainter->drawRect(groundRect);
    }
    
    pPainter->restore();
    
    // Draw aircraft symbol (fixed, not rotated)
    pPainter->setPen(QPen(Qt::yellow, 3));
    pPainter->drawLine(screenPos + QPointF(-8, 0), screenPos + QPointF(8, 0));
    pPainter->drawLine(screenPos + QPointF(0, -3), screenPos + QPointF(0, 3));
    
    // Pitch and roll text
    pPainter->setFont(QFont("Arial", 7));
    pPainter->setPen(Qt::white);
    pPainter->drawText(screenPos + QPointF(-35, -25), 
                      QString("P:%1°").arg(trackInfo.pitch, 0, 'f', 1));
    pPainter->drawText(screenPos + QPointF(-35, -15), 
                      QString("R:%1°").arg(trackInfo.roll, 0, 'f', 1));
}

/**
 * @brief Draws drone health status indicators
 */
void CTrackLayer::drawDroneHealthStatus(QPainter *pPainter, const stTrackDisplayInfo &trackInfo, 
                                       const QPointF &screenPos)
{
    if (!trackInfo.isDrone) return;
    
    // Health status color coding
    QColor healthColor;
    if (trackInfo.healthSummary == "ALL SYSTEMS OK") {
        healthColor = Qt::green;
    } else if (trackInfo.healthSummary == "MOSTLY HEALTHY") {
        healthColor = Qt::yellow;
    } else if (trackInfo.healthSummary == "DEGRADED") {
        healthColor = QColor(255, 165, 0); // Orange
    } else {
        healthColor = Qt::red;
    }
    
    // Draw health status circle
    pPainter->setPen(QPen(healthColor, 2));
    pPainter->setBrush(QColor(healthColor.red(), healthColor.green(), healthColor.blue(), 50));
    pPainter->drawEllipse(screenPos + QPointF(-45, -10), 8, 8);
    
    // Health status text
    pPainter->setFont(QFont("Arial", 6));
    pPainter->setPen(healthColor);
    pPainter->drawText(screenPos + QPointF(-70, -20), "HEALTH");
    pPainter->drawText(screenPos + QPointF(-70, -12), trackInfo.healthSummary);
    
    // Vertical speed indicator (simple arrow)
    if (std::abs(trackInfo.verticalSpeed) > 0.5) {
        QPointF arrowBase = screenPos + QPointF(50, 0);
        double arrowLength = qMin(std::abs(trackInfo.verticalSpeed) * 3, 20.0);
        
        if (trackInfo.verticalSpeed > 0) {
            // Climbing
            pPainter->setPen(QPen(Qt::green, 2));
            pPainter->drawLine(arrowBase, arrowBase + QPointF(0, -arrowLength));
            // Arrow head
            pPainter->drawLine(arrowBase + QPointF(0, -arrowLength), 
                              arrowBase + QPointF(-3, -arrowLength + 3));
            pPainter->drawLine(arrowBase + QPointF(0, -arrowLength), 
                              arrowBase + QPointF(3, -arrowLength + 3));
        } else {
            // Descending
            pPainter->setPen(QPen(Qt::red, 2));
            pPainter->drawLine(arrowBase, arrowBase + QPointF(0, arrowLength));
            // Arrow head
            pPainter->drawLine(arrowBase + QPointF(0, arrowLength), 
                              arrowBase + QPointF(-3, arrowLength - 3));
            pPainter->drawLine(arrowBase + QPointF(0, arrowLength), 
                              arrowBase + QPointF(3, arrowLength - 3));
        }
        
        // Vertical speed text
        pPainter->setFont(QFont("Arial", 7));
        pPainter->setPen(Qt::white);
        pPainter->drawText(arrowBase + QPointF(8, 5), 
                          QString("%1 m/s").arg(trackInfo.verticalSpeed, 0, 'f', 1));
    }
}

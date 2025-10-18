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
#include <QInputDialog>

int nAnimFrame = 0;

/**
 * @brief CTrackLayer constructor
 * @param pCanvas Pointer to the QgsMapCanvas
 */
CTrackLayer::CTrackLayer(QgsMapCanvas *canvas)
    : QgsMapCanvasItem(canvas), m_canvas(canvas), m_hoveredTrackId(-1), m_rightClickedTrackId(-1), m_contextMenu(nullptr)
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
                    
                    // Update context menu items based on current state
                    updateContextMenuItems();
                    
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
    
    m_historyAction = m_contextMenu->addAction("📍 Toggle History (Max 50)");
    connect(m_historyAction, &QAction::triggered, this, &CTrackLayer::onToggleTrackHistory);
    
    QAction *highlightAction = m_contextMenu->addAction("✨ Highlight & Follow");
    connect(highlightAction, &QAction::triggered, this, &CTrackLayer::onHighlightTrack);
    
    m_contextMenu->addSeparator();
    
    QAction *imageAction = m_contextMenu->addAction("🖼️ Load Track Image");
    connect(imageAction, &QAction::triggered, this, &CTrackLayer::onLoadTrackImage);
    
    m_contextMenu->addSeparator();
    
    QAction *configAction = m_contextMenu->addAction("⚙️ Configure History");
    connect(configAction, &QAction::triggered, this, &CTrackLayer::onConfigureHistory);
    
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
 * @brief Updates context menu items based on current track state
 */
void CTrackLayer::updateContextMenuItems()
{
    if (m_rightClickedTrackId == -1 || !m_historyAction) return;
    
    bool historyEnabled = CDataWarehouse::getInstance()->isTrackHistoryEnabled(m_rightClickedTrackId);
    stTrackHistoryConfig config = CDataWarehouse::getInstance()->getHistoryConfig();
    
    if (historyEnabled) {
        QList<stTrackHistoryPoint> history = CDataWarehouse::getInstance()->getTrackHistory(m_rightClickedTrackId);
        m_historyAction->setText(QString("📍 Hide History (%1/%2 points)").arg(history.size()).arg(config.maxHistoryPoints));
    } else {
        m_historyAction->setText(QString("📍 Show History (Max %1 points)").arg(config.maxHistoryPoints));
    }
}

/**
 * @brief Context menu action slots
 */
void CTrackLayer::onFocusTrack()
{
    if (m_rightClickedTrackId == -1) return;
    
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == m_rightClickedTrackId) {
            QgsPointXY centerPoint(track.lon, track.lat);
            m_canvas->setCenter(centerPoint);
            m_canvas->refresh();
            qDebug() << "Focused on track" << m_rightClickedTrackId;
            break;
        }
    }
}

void CTrackLayer::onDeleteTrack()
{
    if (m_rightClickedTrackId == -1) return;
    
    // TODO: Implement track deletion in data warehouse
    qDebug() << "Delete track requested:" << m_rightClickedTrackId;
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
    
    bool historyEnabled = CDataWarehouse::getInstance()->toggleTrackHistory(m_rightClickedTrackId);
    
    if (historyEnabled) {
        qDebug() << "History enabled for track" << m_rightClickedTrackId;
    } else {
        qDebug() << "History disabled for track" << m_rightClickedTrackId;
    }
    
    // Force redraw to show/hide history
    update();
}

void CTrackLayer::onHighlightTrack()
{
    if (m_rightClickedTrackId == -1) return;
    
    qDebug() << "Highlight and follow track" << m_rightClickedTrackId;
    // TODO: Implement track highlighting and following
}

void CTrackLayer::onConfigureHistory()
{
    stTrackHistoryConfig config = CDataWarehouse::getInstance()->getHistoryConfig();
    
    bool ok;
    int newMaxPoints = QInputDialog::getInt(
        nullptr,
        "Configure History Points",
        QString("Maximum history points per track:\n(Current: %1, Range: 1-1000)").arg(config.maxHistoryPoints),
        config.maxHistoryPoints,
        1,
        1000,
        1,
        &ok
    );
    
    if (ok && newMaxPoints != config.maxHistoryPoints) {
        CDataWarehouse::getInstance()->setMaxHistoryPoints(newMaxPoints);
        qDebug() << "History configuration updated: max points =" << newMaxPoints;
        
        // Force redraw to apply changes
        update();
    }
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
 * @brief Draws track history trail
 * @param pPainter QPainter instance
 * @param trackId Track ID to draw history for
 * @param mapToPixel Map to pixel transformation
 */
void CTrackLayer::drawTrackHistory(QPainter *pPainter, int trackId, const QgsMapToPixel &mapToPixel)
{
    QList<stTrackHistoryPoint> history = CDataWarehouse::getInstance()->getTrackHistory(trackId);
    if (history.size() < 2) return; // Need at least 2 points to draw a line
    
    stTrackHistoryConfig config = CDataWarehouse::getInstance()->getHistoryConfig();
    
    // Get track identity for color
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();
    QColor baseColor = Qt::cyan;
    for (const stTrackDisplayInfo &track : tracks) {
        if (track.nTrkId == trackId) {
            switch (track.nTrackIden) {
                case TRACK_IDENTITY_FRIEND:
                    baseColor = Qt::green;
                    break;
                case TRACK_IDENTITY_HOSTILE:
                    baseColor = Qt::red;
                    break;
                case TRACK_IDENTITY_UNKNOWN:
                    baseColor = Qt::yellow;
                    break;
                default:
                    baseColor = Qt::cyan;
                    break;
            }
            break;
        }
    }
    
    // Draw history trail with fading effect
    QPainterPath historyPath;
    QPointF firstPoint = mapToPixel.transform(QgsPointXY(history[0].lon, history[0].lat)).toQPointF();
    historyPath.moveTo(firstPoint);
    
    for (int i = 1; i < history.size(); ++i) {
        QPointF point = mapToPixel.transform(QgsPointXY(history[i].lon, history[i].lat)).toQPointF();
        historyPath.lineTo(point);
        
        // Calculate alpha based on age (newer points are more opaque)
        double alpha = config.historyAlpha * (double(i) / double(history.size() - 1));
        alpha = qMax(0.2, alpha); // Minimum visibility
        
        QColor lineColor = baseColor;
        lineColor.setAlphaF(alpha);
        
        // Draw line segment
        pPainter->setPen(QPen(lineColor, config.historyLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        pPainter->setBrush(Qt::NoBrush);
        
        if (i > 0) {
            QPointF prevPoint = mapToPixel.transform(QgsPointXY(history[i-1].lon, history[i-1].lat)).toQPointF();
            pPainter->drawLine(prevPoint, point);
        }
    }
    
    // Draw small dots at history points
    for (int i = 0; i < history.size(); ++i) {
        QPointF point = mapToPixel.transform(QgsPointXY(history[i].lon, history[i].lat)).toQPointF();
        
        // Calculate alpha and size based on age
        double alpha = config.historyAlpha * (double(i) / double(history.size() - 1));
        alpha = qMax(0.3, alpha);
        
        double dotSize = 2.0 + (2.0 * alpha); // Newer points are larger
        
        QColor dotColor = baseColor;
        dotColor.setAlphaF(alpha);
        
        pPainter->setPen(Qt::NoPen);
        pPainter->setBrush(dotColor);
        pPainter->drawEllipse(point, dotSize, dotSize);
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

        // Check if this is the hovered track
        bool isHovered = (track.nTrkId == m_hoveredTrackId);
        if (isHovered) {
            hoveredTrack = track;
            hasHoveredTrack = true;
        }
        
        // Draw track history if enabled
        if (CDataWarehouse::getInstance()->isTrackHistoryEnabled(track.nTrkId)) {
            drawTrackHistory(pPainter, track.nTrkId, mapToPixel);
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
            // Highlight hovered track with pulsing circle
            if (isHovered) {
                pPainter->setPen(QPen(Qt::white, 3));
                pPainter->setBrush(Qt::NoBrush);
                pPainter->drawEllipse(ptScreen, 10, 10);

                // Add an extra glow effect
                pPainter->setPen(QPen(clr, 2));
                pPainter->drawEllipse(ptScreen, 12, 12);
            }

            // Core dot
            pPainter->setPen(clr);
            pPainter->setBrush(clr);
            pPainter->drawEllipse(ptScreen, 4, 4);

            // Heading line
            double dHeadingRad = qDegreesToRadians(track.heading);
            QPointF ptTip(
                ptScreen.x() + std::cos(dHeadingRad) * 10,
                ptScreen.y() - std::sin(dHeadingRad) * 10
            );
            pPainter->drawLine(ptScreen, ptTip);

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
    }

    // Draw tooltip for hovered track (draw last so it's on top)
    if (hasHoveredTrack && m_hoveredTrackId != -1) {
        drawTooltip(pPainter, hoveredTrack, m_mousePos);
    }
}

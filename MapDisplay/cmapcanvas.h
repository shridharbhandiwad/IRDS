#ifndef CMAPCANVAS_H
#define CMAPCANVAS_H

#include <QObject>
#include <QWidget>
#include "qgsmapcanvas.h"
#include <QPoint>
#include "cppilayer.h"
#include "ctracklayer.h"
#include "qgsrasterlayer.h"
#include <QProcess>
#include <QProgressDialog>


class CMapCanvas : public QgsMapCanvas
{
    Q_OBJECT

public:
    explicit CMapCanvas(QWidget *parent = nullptr);

    void Initialize();

    void mapHome();

    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void loadRasterFile(QString rasterPath);
    void importRasterMap(QString inputPath);
    
    // Getter for track layer
    CTrackLayer* getTrackLayer() const { return _m_trackLayer; }
    
    // Map enable/disable functionality
    void enableMap(bool enabled);
    bool isMapEnabled() const { return m_mapEnabled; }
private:

    QProcess* m_translateProcess = nullptr;
    QProcess* m_addoProcess = nullptr;
    QString m_inputPath;
    QString m_outputPath;

    QProgressDialog* m_progressDialog = nullptr;

    QgsRectangle mWorldExtentPadded;
    void zoomBy(double factor);
    void panCanvas(double dx, double dy);

    QPoint mLastMousePos;
    bool mPanning = false;

    void _loadVectorMaps();
    void loadShapeFile(const QString &shpPath);

    CPPILayer *_m_ppiLayer;
    CTrackLayer *_m_trackLayer;
    void _loadLayers();
    void convertAndCacheRaster(const QString inputPath);
    void _loadRasterMaps();
    
    // Map state
    bool m_mapEnabled;
    QList<QgsMapLayer*> m_mapLayers;  // Store map layers for enable/disable
signals:
    void signalMouseRead(QString);
public slots:
private slots:
    void startGdalTranslate();
    void startGdalAddo();
    void handleGdalStdout();
    void loadCachedAfterProcessing();
};

#endif // CMAPCANVAS_H

#ifndef CPPIWINDOW_H
#define CPPIWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QDockWidget>
#include "../cmapcanvas.h"

// Forward declarations
class CTrackTableWidget;

/**
 * @brief Window for PPI display and track table (Monitor 1)
 * 
 * This window contains:
 * - Map canvas with PPI overlay
 * - Track table widget
 * - Settings button for map controls
 * - Right-click context menu for tracks
 */
class CPPIWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CPPIWindow(QWidget *parent = nullptr);
    ~CPPIWindow();

    /**
     * @brief Get the map canvas instance
     * @return Pointer to map canvas
     */
    CMapCanvas* getMapCanvas() { return m_mapCanvas; }

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    // Settings menu actions
    void onLoadNewMap();
    void onDisableMap();
    void onZoomFitToMax();
    
    // Track context menu actions
    void onFocusTrack();
    void onDeleteTrack();
    void onLoadTrackImage();
    void onHighlightTrack();
    void onSetHistoryPoints();
    
    // Track table interaction
    void onTrackSelected(int trackId);
    void onTrackDoubleClicked(int trackId);
    
    // Mouse position updates
    void onMousePositionChanged(QString mouseRead);

private:
    void setupUI();
    void setupMapCanvas();
    void setupTrackTable();
    void setupSettingsButton();
    void applyLightTheme();
    
    /**
     * @brief Get track ID at given screen position
     * @param globalPos Global screen position
     * @return Track ID if found, -1 otherwise
     */
    int getTrackAtPosition(const QPoint &globalPos);

private:
    CMapCanvas *m_mapCanvas;
    CTrackTableWidget *m_trackTable;
    QPushButton *m_settingsButton;
    QMenu *m_settingsMenu;
    
    int m_contextMenuTrackId; // Track ID for context menu
    int m_selectedTrackId;    // Currently selected track
};

#endif // CPPIWINDOW_H

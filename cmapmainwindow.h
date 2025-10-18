//#ifndef CMAPMAINWINDOW_H
//#define CMAPMAINWINDOW_H

//#include <QMainWindow>
//#include <QTimer>

//namespace Ui {
//class CMapMainWindow;
//}

//class CMapMainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    explicit CMapMainWindow(QWidget *parent = nullptr);
//    ~CMapMainWindow();

//protected:
//    void keyPressEvent(QKeyEvent *event);

//private slots:
//    void slotMouseRead(QString mouseRead);
//    void on_pushButton_MapHome_clicked();

//    void on_pushButton_OpenMaps_clicked();

//    void on_pushButton_FLUSH_clicked();

//    void on_pushButton_EXIT_clicked();

//    void updateTrackTable();
//private:
//    Ui::CMapMainWindow *ui;
//    QTimer _m_updateTimer;
//};

//#endif // CMAPMAINWINDOW_H



//#ifndef CMAPMAINWINDOW_H
//#define CMAPMAINWINDOW_H

//#include <QMainWindow>
//#include <QTimer>
//#include <QKeyEvent>

//// Forward declarations
//class CTrackTableWidget;

//namespace Ui {
//class CMapMainWindow;
//}

//class CMapMainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    explicit CMapMainWindow(QWidget *parent = nullptr);
//    ~CMapMainWindow();

//protected:
//    /**
//     * @brief Handle keyboard shortcuts
//     * @param event Key event
//     *
//     * Shortcuts:
//     * - T: Toggle track table visibility
//     * - H: Map home view
//     * - F: Toggle controls
//     */
//    void keyPressEvent(QKeyEvent *event) override;

//private slots:
//    /**
//     * @brief Update status bar with mouse position
//     * @param mouseRead Mouse position string
//     */
//    void slotMouseRead(QString mouseRead);

//    /**
//     * @brief Reset map to home view
//     */
//    void on_pushButton_MapHome_clicked();

//    /**
//     * @brief Open raster map file dialog
//     */
//    void on_pushButton_OpenMaps_clicked();

//    /**
//     * @brief Flush/clear operation
//     */
//    void on_pushButton_FLUSH_clicked();

//    /**
//     * @brief Exit application
//     */
//    void on_pushButton_EXIT_clicked();

//    /**
//     * @brief Update track table with current data
//     * @note This is kept for backward compatibility
//     * The CTrackTableWidget handles updates automatically
//     */
//    void updateTrackTable();

//    /**
//     * @brief Handle track selection from table
//     * @param trackId Selected track ID
//     */
//    void onTrackSelected(int trackId);

//    /**
//     * @brief Handle track double-click from table
//     * @param trackId Double-clicked track ID
//     * Centers map on the selected track
//     */
//    void onTrackDoubleClicked(int trackId);

//private:
//    Ui::CMapMainWindow *ui;
//    QTimer _m_updateTimer;

//    /**
//     * @brief Rich dockable track table widget
//     */
//    CTrackTableWidget *m_trackTable;

//    /**
//     * @brief Initialize and setup the dockable track table
//     */
//    void setupTrackTable();

//    /**
//     * @brief Apply modern dark theme to the application
//     */
//    void applyModernTheme();
//};

//#endif // CMAPMAINWINDOW_H



#ifndef CMAPMAINWINDOW_H
#define CMAPMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

// Forward declarations
class CPPIWindow;
class CControlsWindow;

namespace Ui {
class CMapMainWindow;
}

/**
 * @brief Main window managing dual-monitor setup
 * 
 * This window orchestrates two separate windows:
 * - CPPIWindow: PPI display + Track table (Monitor 1)
 * - CControlsWindow: All controls and tabs (Monitor 2)
 */
class CMapMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMapMainWindow(QWidget *parent = nullptr);
    ~CMapMainWindow();

protected:
    /**
     * @brief Handle keyboard shortcuts
     * @param event Key event
     *
     * Shortcuts:
     * - F1: Show/Hide PPI Window
     * - F2: Show/Hide Controls Window
     * - H: Map home view
     * - Esc: Exit application
     */
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    // Control window signal handlers
    void onMapHomeRequested();
    void onOpenMapsRequested();
    void onFlushRequested();
    void onExitRequested();
    void onZoomChanged(double zoom);
    void onOpacityChanged(int opacity);
    void onTrackSizeChanged(int size);
    void onTrackFilterChanged(bool showFriend, bool showHostile, bool showUnknown);
    void onAnimationSpeedChanged(int speed);
    void onGridVisibilityChanged(bool visible);
    void onCompassVisibilityChanged(bool visible);

private:
    Ui::CMapMainWindow *ui;

    /**
     * @brief PPI display window (Monitor 1)
     */
    CPPIWindow *m_ppiWindow;

    /**
     * @brief Controls window (Monitor 2)
     */
    CControlsWindow *m_controlsWindow;

    /**
     * @brief Initialize and setup dual-monitor windows
     */
    void setupDualMonitorWindows();

    /**
     * @brief Apply light theme to the application
     */
    void applyLightTheme();

    /**
     * @brief Position windows for dual-monitor setup
     */
    void positionWindowsForDualMonitor();
};

#endif // CMAPMAINWINDOW_H

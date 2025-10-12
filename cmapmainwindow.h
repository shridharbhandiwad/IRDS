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
class CTrackTableWidget;
class CConfigPanelWidget;
class CChartsWidget;

namespace Ui {
class CMapMainWindow;
}

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
     * - T: Toggle track table visibility
     * - C: Toggle control panel visibility
     * - H: Map home view
     * - F: Toggle old controls (deprecated)
     */
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    /**
     * @brief Update status bar with mouse position
     * @param mouseRead Mouse position string
     */
    void slotMouseRead(QString mouseRead);

    /**
     * @brief Reset map to home view
     */
    void on_pushButton_MapHome_clicked();

    /**
     * @brief Open raster map file dialog
     */
    void on_pushButton_OpenMaps_clicked();

    /**
     * @brief Flush/clear operation
     */
    void on_pushButton_FLUSH_clicked();

    /**
     * @brief Exit application
     */
    void on_pushButton_EXIT_clicked();

    /**
     * @brief Update track table with current data
     */
    void updateTrackTable();

    /**
     * @brief Handle track selection from table
     * @param trackId Selected track ID
     */
    void onTrackSelected(int trackId);

    /**
     * @brief Handle track double-click from table
     * @param trackId Double-clicked track ID
     */
    void onTrackDoubleClicked(int trackId);

    // Config panel slots
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
    QTimer _m_updateTimer;

    /**
     * @brief Rich dockable track table widget
     */
    CTrackTableWidget *m_trackTable;

    /**
     * @brief Rich dockable configuration panel
     */
    CConfigPanelWidget *m_configPanel;

    /**
     * @brief Initialize and setup the dockable track table
     */
    void setupTrackTable();

    /**
     * @brief Initialize and setup the dockable config panel
     */
    void setupConfigPanel();

    /**
     * @brief Apply modern dark theme to the application
     */
    void applyModernTheme();

    CChartsWidget *m_chartsWidget;  // ADD THIS member

    void setupChartsWidget();  // ADD THIS method
    void onChartsRequested();  // ADD THIS slot
};

#endif // CMAPMAINWINDOW_H

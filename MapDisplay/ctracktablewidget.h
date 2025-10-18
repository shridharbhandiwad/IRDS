#ifndef CTRACKTABLEWIDGET_H
#define CTRACKTABLEWIDGET_H

#include <QDockWidget>
#include <QTableWidget>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QMenu>
#include <QAction>

class CTrackTableWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CTrackTableWidget(QWidget *parent = nullptr);
    ~CTrackTableWidget();

private slots:
    void updateTrackTable();
    void onTrackSelectionChanged();
    void onFilterChanged(const QString &text);
    void onIdentityFilterChanged(int index);
    void onClearAllTracks();
    void onExportTracks();
    void onTableContextMenuRequested(const QPoint& pos);
    void onFocusTrack();
    void onDeleteTrack();
    void onLoadTrackImage();
    void onToggleTrackHistory();
    void onHighlightTrack();

signals:
    void trackSelected(int trackId);
    void trackDoubleClicked(int trackId);
    void trackRightClicked(int trackId, const QPoint& globalPos);

private:
    void setupUI();
    void applyFilters();
    void setupContextMenu();
    QString getIdentityString(int identity);
    QColor getIdentityColor(int identity);

    QTableWidget *m_tableWidget;
    QTimer *m_updateTimer;
    QLineEdit *m_filterEdit;
    QComboBox *m_identityFilter;
    QPushButton *m_clearButton;
    QPushButton *m_exportButton;

    QString m_currentFilter;
    int m_currentIdentityFilter;
    
    // Context menu
    QMenu *m_contextMenu;
    QAction *m_focusAction;
    QAction *m_deleteAction;
    QAction *m_loadImageAction;
    QAction *m_toggleHistoryAction;
    QAction *m_highlightAction;
    int m_contextTrackId;
};

#endif // CTRACKTABLEWIDGET_H

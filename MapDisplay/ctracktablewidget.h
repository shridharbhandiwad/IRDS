#ifndef CTRACKTABLEWIDGET_H
#define CTRACKTABLEWIDGET_H

#include <QDockWidget>
#include <QTableWidget>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

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

signals:
    void trackSelected(int trackId);
    void trackDoubleClicked(int trackId);

private:
    void setupUI();
    void applyFilters();
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
};

#endif // CTRACKTABLEWIDGET_H

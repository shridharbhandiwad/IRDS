#include "ctracktablewidget.h"
#include "../cdatawarehouse.h"
#include "globalmacros.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QDateTime>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

CTrackTableWidget::CTrackTableWidget(QWidget *parent)
    : QDockWidget("Track Table", parent),
      m_currentFilter(""),
      m_currentIdentityFilter(-1),
      m_contextTrackId(-1)
{
    setupUI();
    setupContextMenu();

    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &CTrackTableWidget::updateTrackTable);
    m_updateTimer->start(1000); // Update every second

    updateTrackTable();
}

CTrackTableWidget::~CTrackTableWidget()
{
}

void CTrackTableWidget::setupUI()
{
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setSpacing(8);
    mainLayout->setContentsMargins(8, 8, 8, 8);

    // Toolbar
    QHBoxLayout *toolbarLayout = new QHBoxLayout();

    // Filter by ID/text
    QLabel *filterLabel = new QLabel("Filter:");
    filterLabel->setStyleSheet("color: #1e293b; font-weight: bold;");
    toolbarLayout->addWidget(filterLabel);

    m_filterEdit = new QLineEdit();
    m_filterEdit->setPlaceholderText("Search by Track ID...");
    m_filterEdit->setStyleSheet(
        "QLineEdit {"
        "   background-color: #ffffff;"
        "   color: #1e293b;"
        "   border: 2px solid #e2e8f0;"
        "   border-radius: 6px;"
        "   padding: 8px 12px;"
        "   font-size: 12px;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #3b82f6;"
        "}"
    );
    connect(m_filterEdit, &QLineEdit::textChanged, this, &CTrackTableWidget::onFilterChanged);
    toolbarLayout->addWidget(m_filterEdit);

    // Identity filter
    m_identityFilter = new QComboBox();
    m_identityFilter->addItem("All Identities", -1);
    m_identityFilter->addItem("✓ Friendly", TRACK_IDENTITY_FRIEND);
    m_identityFilter->addItem("✖ Hostile", TRACK_IDENTITY_HOSTILE);
    m_identityFilter->addItem("? Unknown", TRACK_IDENTITY_UNKNOWN);
    m_identityFilter->setStyleSheet(
        "QComboBox {"
        "   background-color: #ffffff;"
        "   color: #1e293b;"
        "   border: 2px solid #e2e8f0;"
        "   border-radius: 6px;"
        "   padding: 8px 12px;"
        "   font-size: 12px;"
        "   min-width: 120px;"
        "}"
        "QComboBox:hover {"
        "   border: 2px solid #3b82f6;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #ffffff;"
        "   color: #1e293b;"
        "   selection-background-color: #3b82f6;"
        "   selection-color: white;"
        "}"
    );
    connect(m_identityFilter, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CTrackTableWidget::onIdentityFilterChanged);
    toolbarLayout->addWidget(m_identityFilter);

    toolbarLayout->addStretch();

    // Export button
    m_exportButton = new QPushButton("Export CSV");
    m_exportButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3b82f6, stop:1 #2563eb);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 16px;"
        "   font-weight: 600;"
        "   font-size: 12px;"
        "   min-height: 28px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2563eb, stop:1 #1d4ed8);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1d4ed8, stop:1 #1e40af);"
        "}"
    );
    connect(m_exportButton, &QPushButton::clicked, this, &CTrackTableWidget::onExportTracks);
    toolbarLayout->addWidget(m_exportButton);

    mainLayout->addLayout(toolbarLayout);

    // Table
    m_tableWidget = new QTableWidget(0, 9, this);
    m_tableWidget->setHorizontalHeaderLabels({
        "ID", "Identity", "Lat", "Lon", "Alt (m)", "Range (km)", "Heading (°)", "Azimuth (°)", "Updated"
    });

    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->verticalHeader()->setVisible(false);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableWidget->setAlternatingRowColors(true);
    m_tableWidget->setSortingEnabled(true);

    m_tableWidget->setStyleSheet(
        "QTableWidget {"
        "   background-color: #ffffff;"
        "   alternate-background-color: #f8fafc;"
        "   color: #1e293b;"
        "   gridline-color: #e2e8f0;"
        "   border: 2px solid #e2e8f0;"
        "   border-radius: 8px;"
        "   font-size: 12px;"
        "}"
        "QTableWidget::item {"
        "   padding: 10px;"
        "   border-bottom: 1px solid #f1f5f9;"
        "}"
        "QTableWidget::item:selected {"
        "   background-color: #3b82f6;"
        "   color: white;"
        "}"
        "QTableWidget::item:hover {"
        "   background-color: #f1f5f9;"
        "}"
        "QHeaderView::section {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f8fafc, stop:1 #e2e8f0);"
        "   color: #334155;"
        "   padding: 12px;"
        "   border: none;"
        "   border-bottom: 2px solid #3b82f6;"
        "   font-weight: 600;"
        "   font-size: 12px;"
        "}"
        "QHeaderView::section:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e2e8f0, stop:1 #cbd5e1);"
        "}"
        "QScrollBar:vertical {"
        "   background-color: #f8fafc;"
        "   width: 12px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background-color: #3b82f6;"
        "   border-radius: 6px;"
        "   min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "   background-color: #2563eb;"
        "}"
        "QScrollBar:horizontal {"
        "   background-color: #f8fafc;"
        "   height: 12px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "   background-color: #3b82f6;"
        "   border-radius: 6px;"
        "   min-width: 20px;"
        "}"
        "QScrollBar::add-line, QScrollBar::sub-line {"
        "   background: none;"
        "   border: none;"
        "}"
    );

    connect(m_tableWidget, &QTableWidget::itemSelectionChanged,
            this, &CTrackTableWidget::onTrackSelectionChanged);
    connect(m_tableWidget, &QTableWidget::cellDoubleClicked,
            [this](int row, int column) {
        Q_UNUSED(column);
        int trackId = m_tableWidget->item(row, 0)->text().toInt();
        emit trackDoubleClicked(trackId);
    });
    
    // Enable context menu on table
    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested,
            this, &CTrackTableWidget::onTableContextMenuRequested);

    mainLayout->addWidget(m_tableWidget);

    setWidget(mainWidget);

    // Dock widget styling
    setStyleSheet(
        "QDockWidget {"
        "   background-color: #f8fafc;"
        "   color: #1e293b;"
        "   font-size: 13px;"
        "   font-weight: 600;"
        "}"
        "QDockWidget::title {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3b82f6, stop:1 #2563eb);"
        "   color: white;"
        "   padding: 10px;"
        "   border-bottom: none;"
        "   font-weight: 600;"
        "}"
        "QDockWidget::close-button, QDockWidget::float-button {"
        "   background-color: rgba(255, 255, 255, 0.2);"
        "   border-radius: 4px;"
        "   padding: 4px;"
        "}"
        "QDockWidget::close-button:hover, QDockWidget::float-button:hover {"
        "   background-color: rgba(255, 255, 255, 0.3);"
        "}"
    );
}

QString CTrackTableWidget::getIdentityString(int identity)
{
    switch (identity) {
        case TRACK_IDENTITY_FRIEND: return "✓ Friendly";
        case TRACK_IDENTITY_HOSTILE: return "✖ Hostile";
        case TRACK_IDENTITY_UNKNOWN: return "? Unknown";
        default: return "• Undefined";
    }
}

QColor CTrackTableWidget::getIdentityColor(int identity)
{
    switch (identity) {
        case TRACK_IDENTITY_FRIEND: return QColor(46, 204, 113);
        case TRACK_IDENTITY_HOSTILE: return QColor(231, 76, 60);
        case TRACK_IDENTITY_UNKNOWN: return QColor(241, 196, 15);
        default: return QColor(149, 165, 166);
    }
}

void CTrackTableWidget::updateTrackTable()
{
    QList<stTrackDisplayInfo> tracks = CDataWarehouse::getInstance()->getTrackList();

    m_tableWidget->setSortingEnabled(false);
    m_tableWidget->setRowCount(0);

    int row = 0;
    for (const stTrackDisplayInfo &track : tracks) {
        // Apply filters
        if (!m_currentFilter.isEmpty()) {
            if (!QString::number(track.nTrkId).contains(m_currentFilter, Qt::CaseInsensitive)) {
                continue;
            }
        }

        if (m_currentIdentityFilter != -1) {
            if (track.nTrackIden != m_currentIdentityFilter) {
                continue;
            }
        }

        m_tableWidget->insertRow(row);

        // ID
        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(track.nTrkId));
        idItem->setTextAlignment(Qt::AlignCenter);
        idItem->setFont(QFont("Segoe UI", 10, QFont::Bold));
        m_tableWidget->setItem(row, 0, idItem);

        // Identity
        QTableWidgetItem *identItem = new QTableWidgetItem(getIdentityString(track.nTrackIden));
        identItem->setTextAlignment(Qt::AlignCenter);
        identItem->setForeground(QBrush(getIdentityColor(track.nTrackIden)));
        identItem->setFont(QFont("Segoe UI", 10, QFont::Bold));
        m_tableWidget->setItem(row, 1, identItem);

        // Latitude
        QTableWidgetItem *latItem = new QTableWidgetItem(QString::number(track.lat, 'f', 5));
        latItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 2, latItem);

        // Longitude
        QTableWidgetItem *lonItem = new QTableWidgetItem(QString::number(track.lon, 'f', 5));
        lonItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 3, lonItem);

        // Altitude
        QTableWidgetItem *altItem = new QTableWidgetItem(QString::number(track.alt, 'f', 0));
        altItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 4, altItem);

        // Range
        QTableWidgetItem *rangeItem = new QTableWidgetItem(QString::number(track.range / 1000.0, 'f', 2));
        rangeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 5, rangeItem);

        // Heading
        QTableWidgetItem *headItem = new QTableWidgetItem(QString::number(track.heading, 'f', 1));
        headItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 6, headItem);

        // Azimuth
        QTableWidgetItem *azItem = new QTableWidgetItem(QString::number(track.azimuth, 'f', 2));
        azItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 7, azItem);

        // Last Update
        QDateTime updateTime = QDateTime::fromSecsSinceEpoch(track.nTrackTime);
        QTableWidgetItem *timeItem = new QTableWidgetItem(updateTime.toString("hh:mm:ss"));
        timeItem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(row, 8, timeItem);

        row++;
    }

    m_tableWidget->setSortingEnabled(true);

    // Update title with track count
    setWindowTitle(QString("Track Table (%1 tracks)").arg(row));
}

void CTrackTableWidget::onTrackSelectionChanged()
{
    QList<QTableWidgetItem*> selectedItems = m_tableWidget->selectedItems();
    if (!selectedItems.isEmpty()) {
        int trackId = m_tableWidget->item(selectedItems[0]->row(), 0)->text().toInt();
        emit trackSelected(trackId);
    }
}

void CTrackTableWidget::onFilterChanged(const QString &text)
{
    m_currentFilter = text;
    updateTrackTable();
}

void CTrackTableWidget::onIdentityFilterChanged(int index)
{
    m_currentIdentityFilter = m_identityFilter->itemData(index).toInt();
    updateTrackTable();
}

void CTrackTableWidget::onClearAllTracks()
{
    // Placeholder for clear functionality
}

void CTrackTableWidget::onExportTracks()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export Tracks",
        QDir::homePath() + "/tracks_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".csv",
        "CSV Files (*.csv);;All Files (*)"
    );

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open file for writing!");
        return;
    }

    QTextStream out(&file);

    // Write header
    out << "Track ID,Identity,Latitude,Longitude,Altitude (m),Range (km),Heading (°),Azimuth (°),Last Update\n";

    // Write data
    for (int row = 0; row < m_tableWidget->rowCount(); ++row) {
        for (int col = 0; col < m_tableWidget->columnCount(); ++col) {
            out << m_tableWidget->item(row, col)->text();
            if (col < m_tableWidget->columnCount() - 1) {
                out << ",";
            }
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "Success", QString("Tracks exported successfully to:\n%1").arg(fileName));
}

void CTrackTableWidget::setupContextMenu()
{
    m_contextMenu = new QMenu(this);
    
    m_focusAction = m_contextMenu->addAction("🎯 Focus Track");
    m_contextMenu->addSeparator();
    m_toggleHistoryAction = m_contextMenu->addAction("📍 Toggle History");
    m_highlightAction = m_contextMenu->addAction("✨ Highlight & Follow");
    m_contextMenu->addSeparator();
    m_loadImageAction = m_contextMenu->addAction("🖼️ Load Track Image");
    m_contextMenu->addSeparator();
    m_deleteAction = m_contextMenu->addAction("🗑️ Delete Track");
    
    // Connect actions
    connect(m_focusAction, &QAction::triggered, this, &CTrackTableWidget::onFocusTrack);
    connect(m_deleteAction, &QAction::triggered, this, &CTrackTableWidget::onDeleteTrack);
    connect(m_loadImageAction, &QAction::triggered, this, &CTrackTableWidget::onLoadTrackImage);
    connect(m_toggleHistoryAction, &QAction::triggered, this, &CTrackTableWidget::onToggleTrackHistory);
    connect(m_highlightAction, &QAction::triggered, this, &CTrackTableWidget::onHighlightTrack);
    
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

void CTrackTableWidget::onTableContextMenuRequested(const QPoint& pos)
{
    QTableWidgetItem* item = m_tableWidget->itemAt(pos);
    if (item) {
        int row = item->row();
        m_contextTrackId = m_tableWidget->item(row, 0)->text().toInt();
        
        QPoint globalPos = m_tableWidget->mapToGlobal(pos);
        m_contextMenu->exec(globalPos);
        
        emit trackRightClicked(m_contextTrackId, globalPos);
    }
}

void CTrackTableWidget::onFocusTrack()
{
    if (m_contextTrackId != -1) {
        qDebug() << "Focus track requested:" << m_contextTrackId;
        // This will be handled by the PPI window
    }
}

void CTrackTableWidget::onDeleteTrack()
{
    if (m_contextTrackId != -1) {
        qDebug() << "Delete track requested:" << m_contextTrackId;
        // This will be handled by the PPI window
    }
}

void CTrackTableWidget::onLoadTrackImage()
{
    if (m_contextTrackId != -1) {
        qDebug() << "Load track image requested:" << m_contextTrackId;
        // This will be handled by the PPI window
    }
}

void CTrackTableWidget::onToggleTrackHistory()
{
    if (m_contextTrackId != -1) {
        qDebug() << "Toggle track history requested:" << m_contextTrackId;
        // This will be handled by the PPI window
    }
}

void CTrackTableWidget::onHighlightTrack()
{
    if (m_contextTrackId != -1) {
        qDebug() << "Highlight track requested:" << m_contextTrackId;
        // This will be handled by the PPI window
    }
}

void CTrackTableWidget::applyFilters()
{
    updateTrackTable();
}

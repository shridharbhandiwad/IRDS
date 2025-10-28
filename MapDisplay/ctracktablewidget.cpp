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
      m_contextMenu(nullptr),
      m_rightClickedTrackId(-1)
{
    setupUI();
    createContextMenu();

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
    filterLabel->setStyleSheet("color: #000000; font-weight: bold;");
    toolbarLayout->addWidget(filterLabel);

    m_filterEdit = new QLineEdit();
    m_filterEdit->setPlaceholderText("Search by Track ID...");
    m_filterEdit->setStyleSheet(
        "QLineEdit {"
        "   background-color: #FFF8E7;"
        "   color: #000000;"
        "   border: 2px solid #F5DEB3;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "   font-size: 11px;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #FFE4B5;"
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
        "   background-color: #FFF8E7;"
        "   color: #000000;"
        "   border: 2px solid #F5DEB3;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "   font-size: 11px;"
        "   min-width: 120px;"
        "}"
        "QComboBox:hover {"
        "   border: 2px solid #FFE4B5;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #FFF8E7;"
        "   color: #000000;"
        "   selection-background-color: #FFE4B5;"
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
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFE4B5, stop:1 #FFDEAD);"
        "   color: #000000;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 6px 12px;"
        "   font-weight: bold;"
        "   font-size: 11px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFDEAD, stop:1 #DEB887);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #DEB887, stop:1 #D2B48C);"
        "}"
    );
    connect(m_exportButton, &QPushButton::clicked, this, &CTrackTableWidget::onExportTracks);
    toolbarLayout->addWidget(m_exportButton);

    mainLayout->addLayout(toolbarLayout);

    // Table
    m_tableWidget = new QTableWidget(0, 8, this);
    m_tableWidget->setHorizontalHeaderLabels({
        "ID", "Range (km)", "Azimuth (°)", "Elevation (°)", "Alt (m)", "Speed (m/s)", "Span (s)", "Identity"
    });

    // Set resize mode to interactive for better control, but stretch last column
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
    
    // Set minimum column widths to ensure all headers are visible
    m_tableWidget->setColumnWidth(0, 60);   // ID
    m_tableWidget->setColumnWidth(1, 100);  // Range (km)
    m_tableWidget->setColumnWidth(2, 110);  // Azimuth (°)
    m_tableWidget->setColumnWidth(3, 110);  // Elevation (°)
    m_tableWidget->setColumnWidth(4, 85);   // Alt (m)
    m_tableWidget->setColumnWidth(5, 105);  // Speed (m/s)
    m_tableWidget->setColumnWidth(6, 95);   // Span (s)
    m_tableWidget->setColumnWidth(7, 110);  // Identity
    // Updated column will stretch
    m_tableWidget->verticalHeader()->setVisible(false);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableWidget->setAlternatingRowColors(true);
    m_tableWidget->setSortingEnabled(true);

    m_tableWidget->setStyleSheet(
        "QTableWidget {"
        "   background-color: rgba(255, 255, 255, 0.95);"
        "   alternate-background-color: rgba(248, 250, 252, 0.95);"
        "   color: #000000;"
        "   gridline-color: #F5DEB3;"
        "   border: 2px solid #DEB887;"
        "   border-radius: 8px;"
        "   font-size: 11px;"
        "   selection-background-color: #FFE4B5;"
        "}"
        "QTableWidget::item {"
        "   padding: 8px;"
        "   color: #000000;"
        "}"
        "QTableWidget::item:selected {"
        "   background-color: #FFE4B5;"
        "   color: #000000;"
        "}"
        "QTableWidget::item:hover {"
        "   background-color: #e0e7ff;"
        "}"
        "QHeaderView::section {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(241, 245, 249, 0.95), stop:1 rgba(226, 232, 240, 0.95));"
        "   color: #000000;"
        "   padding: 10px;"
        "   border: none;"
        "   border-bottom: 2px solid #FFE4B5;"
        "   font-weight: bold;"
        "   font-size: 11px;"
        "   text-align: center;"
        "}"
        "QHeaderView::section:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F5DEB3, stop:1 #DEB887);"
        "}"
        "QScrollBar:vertical {"
        "   background-color: #FFEFD5;"
        "   width: 12px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background-color: #FFE4B5;"
        "   border-radius: 6px;"
        "   min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "   background-color: #FFDEAD;"
        "}"
        "QScrollBar:horizontal {"
        "   background-color: #FFEFD5;"
        "   height: 12px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "   background-color: #FFE4B5;"
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
    
    // Enable context menu
    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested,
            this, &CTrackTableWidget::onTableContextMenu);

    mainLayout->addWidget(m_tableWidget);

    setWidget(mainWidget);

    // Dock widget styling with light transparent theme
    setStyleSheet(
        "QDockWidget {"
        "   background-color: rgba(248, 250, 252, 0.95);"
        "   color: #000000;"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "}"
        "QDockWidget::title {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(241, 245, 249, 0.95), stop:1 rgba(226, 232, 240, 0.95));"
        "   padding: 10px;"
        "   border-bottom: 2px solid #FFE4B5;"
        "   border-radius: 6px 6px 0px 0px;"
        "   color: #000000;"
        "   font-weight: 600;"
        "}"
        "QDockWidget::close-button, QDockWidget::float-button {"
        "   background-color: rgba(226, 232, 240, 0.9);"
        "   border-radius: 4px;"
        "   padding: 2px;"
        "}"
        "QDockWidget::close-button:hover, QDockWidget::float-button:hover {"
        "   background-color: #FFE4B5;"
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

        // Range (km)
        QTableWidgetItem *rangeItem = new QTableWidgetItem(QString::number(track.range / 1000.0, 'f', 2));
        rangeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 1, rangeItem);

        // Azimuth (°)
        QTableWidgetItem *azItem = new QTableWidgetItem(QString::number(track.azimuth, 'f', 2));
        azItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 2, azItem);

        // Elevation (°)
        QTableWidgetItem *elItem = new QTableWidgetItem(QString::number(track.elevation, 'f', 2));
        elItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 3, elItem);

        // Altitude (m)
        QTableWidgetItem *altItem = new QTableWidgetItem(QString::number(track.alt, 'f', 0));
        altItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 4, altItem);

        // Speed (m/s)
        QTableWidgetItem *spdItem = new QTableWidgetItem(QString::number(track.velocity, 'f', 1));
        spdItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 5, spdItem);

        // Track Span (s)
        qint64 nowSecs = QDateTime::currentDateTime().toSecsSinceEpoch();
        qint64 spanSecs = (track.firstSeenTime > 0) ? (nowSecs - track.firstSeenTime) : 0;
        QTableWidgetItem *spanItem = new QTableWidgetItem(QString::number(spanSecs));
        spanItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_tableWidget->setItem(row, 6, spanItem);

        // Identity
        QTableWidgetItem *identItem = new QTableWidgetItem(getIdentityString(track.nTrackIden));
        identItem->setTextAlignment(Qt::AlignCenter);
        identItem->setForeground(QBrush(getIdentityColor(track.nTrackIden)));
        identItem->setFont(QFont("Segoe UI", 10, QFont::Bold));
        m_tableWidget->setItem(row, 7, identItem);

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
    out << "Track ID,Range (km),Azimuth (°),Elevation (°),Altitude (m),Speed (m/s),Span (s),Identity\n";

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

void CTrackTableWidget::applyFilters()
{
    updateTrackTable();
}

void CTrackTableWidget::createContextMenu()
{
    m_contextMenu = new QMenu(this);
    
    int historyLimit = CDataWarehouse::getInstance()->getHistoryLimit();
    
    QAction *focusAction = m_contextMenu->addAction("🎯 Focus Track");
    QAction *historyAction = m_contextMenu->addAction(QString("📍 Toggle History (Max %1)").arg(historyLimit));
    QAction *highlightAction = m_contextMenu->addAction("✨ Highlight & Follow");
    m_contextMenu->addSeparator();
    QAction *imageAction = m_contextMenu->addAction("🖼️ Load Track Image");
    m_contextMenu->addSeparator();
    QAction *deleteAction = m_contextMenu->addAction("🗑️ Delete Track");
    
    // Connect actions
    connect(focusAction, &QAction::triggered, [this]() {
        if (m_rightClickedTrackId != -1) {
            emit trackDoubleClicked(m_rightClickedTrackId);
        }
    });
    
    connect(deleteAction, &QAction::triggered, [this]() {
        if (m_rightClickedTrackId != -1) {
            int ret = QMessageBox::question(this, "Delete Track",
                QString("Are you sure you want to delete Track #%1?").arg(m_rightClickedTrackId),
                QMessageBox::Yes | QMessageBox::No);
            
            if (ret == QMessageBox::Yes) {
                qDebug() << "Delete track requested:" << m_rightClickedTrackId;
                // TODO: Implement track deletion
            }
        }
    });
    
    connect(imageAction, &QAction::triggered, [this]() {
        if (m_rightClickedTrackId != -1) {
            QString filter = "Image Files (*.png *.jpg *.jpeg *.bmp *.gif)";
            QString imagePath = QFileDialog::getOpenFileName(
                this,
                QString("Load Image for Track #%1").arg(m_rightClickedTrackId),
                QString(),
                filter
            );
            
            if (!imagePath.isEmpty()) {
                qDebug() << "Load image for track" << m_rightClickedTrackId << ":" << imagePath;
                emit trackImageLoaded(m_rightClickedTrackId, imagePath);
            }
        }
    });
    
    connect(historyAction, &QAction::triggered, [this]() {
        if (m_rightClickedTrackId != -1) {
            CDataWarehouse::getInstance()->toggleTrackHistory(m_rightClickedTrackId);
            qDebug() << "Toggle history for track" << m_rightClickedTrackId;
        }
    });
    
    connect(highlightAction, &QAction::triggered, [this]() {
        if (m_rightClickedTrackId != -1) {
            qDebug() << "Highlight and follow track" << m_rightClickedTrackId;
        }
    });
    
    // Style the context menu
    m_contextMenu->setStyleSheet(
        "QMenu {"
        "   background-color: #FFF8E7;"
        "   color: #000000;"
        "   border: 2px solid #F5DEB3;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "}"
        "QMenu::item {"
        "   padding: 8px 24px;"
        "   border-radius: 4px;"
        "   font-weight: 500;"
        "}"
        "QMenu::item:selected {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FFE4B5, stop:1 #FFDEAD);"
        "   color: #000000;"
        "}"
        "QMenu::separator {"
        "   height: 1px;"
        "   background-color: #F5DEB3;"
        "   margin: 4px 16px;"
        "}"
    );
}

void CTrackTableWidget::onTableContextMenu(const QPoint &pos)
{
    QTableWidgetItem *item = m_tableWidget->itemAt(pos);
    if (item) {
        int row = item->row();
        m_rightClickedTrackId = m_tableWidget->item(row, 0)->text().toInt();
        QPoint globalPos = m_tableWidget->mapToGlobal(pos);
        emit trackRightClicked(m_rightClickedTrackId, globalPos);
        m_contextMenu->exec(globalPos);
    }
}

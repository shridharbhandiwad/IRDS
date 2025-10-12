/********************************************************************************
** Form generated from reading UI file 'cmapmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAPMAINWINDOW_H
#define UI_CMAPMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "MapDisplay/cmapcanvas.h"

QT_BEGIN_NAMESPACE

class Ui_CMapMainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    CMapCanvas *widgetMapCanvas;
    QWidget *widget_TextualControl;
    QGridLayout *gridLayout_2;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_FLUSH;
    QPushButton *pushButton_RCHMI;
    QPushButton *pushButton_SERVO;
    QPushButton *pushButton_EXIT;
    QPushButton *pushButton_MapHome;
    QPushButton *pushButton_OpenMaps;
    QTableWidget *tableWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMapMainWindow)
    {
        if (CMapMainWindow->objectName().isEmpty())
            CMapMainWindow->setObjectName(QString::fromUtf8("CMapMainWindow"));
        CMapMainWindow->resize(1920, 1080);
        CMapMainWindow->setMinimumSize(QSize(1200, 800));
        CMapMainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {background:  #050D1A;};"));
        centralWidget = new QWidget(CMapMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("QMainWindow { background-color: #F0F8FF; }\n"
"            QPushButton { background-color: #00B8D4; color: white; font-size: 16px; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; font-weight: bold; border-radius: 8px; padding: 10px; }\n"
"            QPushButton:hover { background-color: #00A4C6; }\n"
"			QPushButton:checked { border : 4px solid white }\n"
"            QPushButton:pressed { background-color: #0091A1; }\n"
"            QTableWidget { background-color: #000000; alternate-background-color: #202020; gridline-color: #404040;color: #333333; font-size: 14px; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; border: 1px solid #00B8D4; border-radius: 6px; padding: 10px; gridline-color: #80DEEA; }\n"
"            QHeaderView::section { background-color: #00B8D4; color: white; font-size: 15px; font-weight: bold; padding: 10px; border: none; }\n"
"            QTableWidget QTableCornerButton::section { background-color: #00B8D4; }"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        widgetMapCanvas = new CMapCanvas(centralWidget);
        widgetMapCanvas->setObjectName(QString::fromUtf8("widgetMapCanvas"));
        widgetMapCanvas->setMinimumSize(QSize(800, 600));
        widgetMapCanvas->setStyleSheet(QString::fromUtf8("\n"
"         border: 2px solid #667eea; \n"
"         border-radius: 8px; \n"
"         background-color: #0f172a;\n"
"         margin: 2px;\n"
"       "));

        gridLayout->addWidget(widgetMapCanvas, 0, 0, 1, 1);

        widget_TextualControl = new QWidget(centralWidget);
        widget_TextualControl->setObjectName(QString::fromUtf8("widget_TextualControl"));
        widget_TextualControl->setMaximumSize(QSize(700, 16777215));
        gridLayout_2 = new QGridLayout(widget_TextualControl);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(widget_TextualControl);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 0, -1, 0);
        pushButton_FLUSH = new QPushButton(widget_3);
        pushButton_FLUSH->setObjectName(QString::fromUtf8("pushButton_FLUSH"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_FLUSH->sizePolicy().hasHeightForWidth());
        pushButton_FLUSH->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_FLUSH, 1, 2, 1, 1);

        pushButton_RCHMI = new QPushButton(widget_3);
        pushButton_RCHMI->setObjectName(QString::fromUtf8("pushButton_RCHMI"));
        sizePolicy.setHeightForWidth(pushButton_RCHMI->sizePolicy().hasHeightForWidth());
        pushButton_RCHMI->setSizePolicy(sizePolicy);
        pushButton_RCHMI->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pushButton_RCHMI, 1, 0, 1, 1);

        pushButton_SERVO = new QPushButton(widget_3);
        pushButton_SERVO->setObjectName(QString::fromUtf8("pushButton_SERVO"));
        sizePolicy.setHeightForWidth(pushButton_SERVO->sizePolicy().hasHeightForWidth());
        pushButton_SERVO->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_SERVO, 1, 1, 1, 1);

        pushButton_EXIT = new QPushButton(widget_3);
        pushButton_EXIT->setObjectName(QString::fromUtf8("pushButton_EXIT"));
        sizePolicy.setHeightForWidth(pushButton_EXIT->sizePolicy().hasHeightForWidth());
        pushButton_EXIT->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_EXIT, 1, 3, 1, 1);

        pushButton_MapHome = new QPushButton(widget_3);
        pushButton_MapHome->setObjectName(QString::fromUtf8("pushButton_MapHome"));
        sizePolicy.setHeightForWidth(pushButton_MapHome->sizePolicy().hasHeightForWidth());
        pushButton_MapHome->setSizePolicy(sizePolicy);
        pushButton_MapHome->setMinimumSize(QSize(0, 40));
        pushButton_MapHome->setCheckable(false);
        pushButton_MapHome->setChecked(false);

        gridLayout_3->addWidget(pushButton_MapHome, 0, 0, 1, 1);

        pushButton_OpenMaps = new QPushButton(widget_3);
        pushButton_OpenMaps->setObjectName(QString::fromUtf8("pushButton_OpenMaps"));
        sizePolicy.setHeightForWidth(pushButton_OpenMaps->sizePolicy().hasHeightForWidth());
        pushButton_OpenMaps->setSizePolicy(sizePolicy);
        pushButton_OpenMaps->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pushButton_OpenMaps, 0, 1, 1, 1);


        gridLayout_2->addWidget(widget_3, 0, 0, 1, 1);

        tableWidget = new QTableWidget(widget_TextualControl);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        if (tableWidget->rowCount() < 100)
            tableWidget->setRowCount(100);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(false);
        QPalette palette;
        QBrush brush(QColor(51, 51, 51, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(32, 32, 32, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush3(QColor(51, 51, 51, 128));
        brush3.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush3);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        QBrush brush4(QColor(51, 51, 51, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush4);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        QBrush brush5(QColor(51, 51, 51, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        tableWidget->setPalette(palette);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setRowCount(100);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setMinimumSectionSize(60);
        tableWidget->horizontalHeader()->setDefaultSectionSize(95);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);

        gridLayout_2->addWidget(tableWidget, 1, 0, 1, 1);


        gridLayout->addWidget(widget_TextualControl, 0, 1, 1, 1);

        CMapMainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CMapMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        statusBar->setFont(font);
        statusBar->setStyleSheet(QString::fromUtf8("color:white"));
        CMapMainWindow->setStatusBar(statusBar);

        retranslateUi(CMapMainWindow);

        QMetaObject::connectSlotsByName(CMapMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMapMainWindow)
    {
        CMapMainWindow->setWindowTitle(QCoreApplication::translate("CMapMainWindow", "CMapMainWindow", nullptr));
        pushButton_FLUSH->setText(QCoreApplication::translate("CMapMainWindow", "FLUSH", nullptr));
        pushButton_RCHMI->setText(QCoreApplication::translate("CMapMainWindow", "RC HMI", nullptr));
        pushButton_SERVO->setText(QCoreApplication::translate("CMapMainWindow", "SERVO", nullptr));
        pushButton_EXIT->setText(QCoreApplication::translate("CMapMainWindow", "EXIT", nullptr));
        pushButton_MapHome->setText(QCoreApplication::translate("CMapMainWindow", "MAP HOME", nullptr));
        pushButton_OpenMaps->setText(QCoreApplication::translate("CMapMainWindow", "OPEN MAPS", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CMapMainWindow", "TID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CMapMainWindow", "Range (m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CMapMainWindow", "Az \302\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CMapMainWindow", "Elev \302\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CMapMainWindow", "Head \302\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("CMapMainWindow", "Spd (mps)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("CMapMainWindow", "SNR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMapMainWindow: public Ui_CMapMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAPMAINWINDOW_H

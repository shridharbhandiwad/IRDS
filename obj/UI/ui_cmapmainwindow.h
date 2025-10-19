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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMapMainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *windowButtonsLayout;
    QPushButton *showPPIButton;
    QPushButton *showControlsButton;
    QHBoxLayout *arrangementButtonsLayout;
    QPushButton *arrangeDualButton;
    QPushButton *fullscreenButton;
    QLabel *helpLabel;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMapMainWindow)
    {
        if (CMapMainWindow->objectName().isEmpty())
            CMapMainWindow->setObjectName(QString::fromUtf8("CMapMainWindow"));
        CMapMainWindow->resize(400, 200);
        CMapMainWindow->setMinimumSize(QSize(400, 200));
        CMapMainWindow->setMaximumSize(QSize(500, 250));
        CMapMainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f8fafc, stop:1 #e2e8f0);\n"
"}"));
        centralWidget = new QWidget(CMapMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #f8fafc;\n"
"    color: #1e293b;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3b82f6, stop:1 #2563eb);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"    font-weight: 600;\n"
"    font-size: 12px;\n"
"    min-height: 28px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2563eb, stop:1 #1d4ed8);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1d4ed8, stop:1 #1e40af);\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #334155;\n"
"    font-weight: 600;\n"
"    font-size: 14px;\n"
"}"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(12);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        titleLabel = new QLabel(centralWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        windowButtonsLayout = new QHBoxLayout();
        windowButtonsLayout->setSpacing(8);
        windowButtonsLayout->setObjectName(QString::fromUtf8("windowButtonsLayout"));
        showPPIButton = new QPushButton(centralWidget);
        showPPIButton->setObjectName(QString::fromUtf8("showPPIButton"));

        windowButtonsLayout->addWidget(showPPIButton);

        showControlsButton = new QPushButton(centralWidget);
        showControlsButton->setObjectName(QString::fromUtf8("showControlsButton"));

        windowButtonsLayout->addWidget(showControlsButton);


        verticalLayout->addLayout(windowButtonsLayout);

        arrangementButtonsLayout = new QHBoxLayout();
        arrangementButtonsLayout->setSpacing(8);
        arrangementButtonsLayout->setObjectName(QString::fromUtf8("arrangementButtonsLayout"));
        arrangeDualButton = new QPushButton(centralWidget);
        arrangeDualButton->setObjectName(QString::fromUtf8("arrangeDualButton"));

        arrangementButtonsLayout->addWidget(arrangeDualButton);

        fullscreenButton = new QPushButton(centralWidget);
        fullscreenButton->setObjectName(QString::fromUtf8("fullscreenButton"));

        arrangementButtonsLayout->addWidget(fullscreenButton);


        verticalLayout->addLayout(arrangementButtonsLayout);

        helpLabel = new QLabel(centralWidget);
        helpLabel->setObjectName(QString::fromUtf8("helpLabel"));
        helpLabel->setAlignment(Qt::AlignCenter);
        helpLabel->setStyleSheet(QString::fromUtf8("QLabel { color: #64748b; font-size: 11px; }"));

        verticalLayout->addWidget(helpLabel);

        CMapMainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CMapMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setStyleSheet(QString::fromUtf8("QStatusBar {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f8fafc, stop:1 #e2e8f0);\n"
"    color: #334155;\n"
"    border-top: 2px solid #3b82f6;\n"
"    font-size: 11px;\n"
"    font-weight: 500;\n"
"    padding: 4px;\n"
"}"));
        CMapMainWindow->setStatusBar(statusBar);

        retranslateUi(CMapMainWindow);

        QMetaObject::connectSlotsByName(CMapMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMapMainWindow)
    {
        CMapMainWindow->setWindowTitle(QCoreApplication::translate("CMapMainWindow", "\360\237\216\257 Radar Display - Window Manager", nullptr));
        titleLabel->setText(QCoreApplication::translate("CMapMainWindow", "\360\237\216\257 Dual Monitor Radar Display", nullptr));
        showPPIButton->setText(QCoreApplication::translate("CMapMainWindow", "\360\237\226\245\357\270\217 Show PPI", nullptr));
#if QT_CONFIG(tooltip)
        showPPIButton->setToolTip(QCoreApplication::translate("CMapMainWindow", "Show PPI Window (F1)", nullptr));
#endif // QT_CONFIG(tooltip)
        showControlsButton->setText(QCoreApplication::translate("CMapMainWindow", "\360\237\216\233\357\270\217 Show Controls", nullptr));
#if QT_CONFIG(tooltip)
        showControlsButton->setToolTip(QCoreApplication::translate("CMapMainWindow", "Show Controls Window (F2)", nullptr));
#endif // QT_CONFIG(tooltip)
        arrangeDualButton->setText(QCoreApplication::translate("CMapMainWindow", "\360\237\223\220 Dual Monitor", nullptr));
#if QT_CONFIG(tooltip)
        arrangeDualButton->setToolTip(QCoreApplication::translate("CMapMainWindow", "Arrange for Dual Monitor (F3)", nullptr));
#endif // QT_CONFIG(tooltip)
        fullscreenButton->setText(QCoreApplication::translate("CMapMainWindow", "\360\237\224\215 Fullscreen", nullptr));
#if QT_CONFIG(tooltip)
        fullscreenButton->setToolTip(QCoreApplication::translate("CMapMainWindow", "Toggle Fullscreen (F4)", nullptr));
#endif // QT_CONFIG(tooltip)
        helpLabel->setText(QCoreApplication::translate("CMapMainWindow", "\360\237\222\241 Use F1-F4 keys for quick access", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMapMainWindow: public Ui_CMapMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAPMAINWINDOW_H

#include "cmapmainwindow.h"
#include "MapDisplay/cgismapcontroller.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QDir>
#include "qgsapplication.h"
#include "MapDisplay/cgismapcontroller.h"
#include "globalmacros.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QgsApplication::initQgis();

    qDebug()<<"RADAR DISPLAY";
    qDebug()<<"APP VERSION :"<<APP_VERSION;
    qDebug()<<"APP BUILT DATE :"<<APP_BUILD_DATE;

     CMapMainWindow w;
     
     // Set window flags to ensure maximize/minimize buttons are available
     w.setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
     
     // Show maximized to utilize full screen space
     w.showMaximized();

    return app.exec();
}

#include <QtGui>
#include <QtWebKit>
#include <QApplication>
#include <QWebView>

#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName(QString("TikBew"));
    app.setApplicationVersion(QString(VERSION_STRING));
    MainWindow* mainWindow = new MainWindow();
    mainWindow->setWindowFlags(Qt::Window);
    mainWindow->show();
    return app.exec();
}

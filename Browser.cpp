#include <QtGui>
#include <QtWebKit>
#include <QApplication>
#include <QWebView>

#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    //QWebView view;
    //view.show();
    //view.setUrl(QUrl("http://tikbew.com"));
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    return app.exec();
}

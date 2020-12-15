#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QWebView>
#include <QTabWidget>
#include <QSettings>
#include <QCloseEvent>
#include <QComboBox>
#include "URLBar.h"

#define VERSION_STRING "2.0"
#define HOME_URL "https://wbsrch.com"

class MainWindow: public QDialog
{
    Q_OBJECT
public:
    MainWindow( );
    ~MainWindow( );
    void LoadSettings();
    void SaveSettings();
public slots:
    void OnButtonLargerClick();
    void OnButtonSmallerClick();
    void OnButtonStopClick();
    void OnButtonForwardClick();
    void OnButtonReloadClick();
    void OnButtonBackClick();
    void OnButtonGoClick();
    void OnButtonHomeClick();
    void UpdateUrl();
    void UpdateTitle();
    void OnAbout();
    void OnAddTab();
    void OnAddBookmark();
    void TabChanged(int index);
    void CloseTab(int index);
    void CloseCurrentTab();
    void LoadStarted();
    void LoadFinished(bool);
    void closeEvent(QCloseEvent *);
    void OnQuit();
private:
    QPushButton* _btnLarger;
    QPushButton* _btnStop;
    QPushButton* _btnForward;
    QPushButton* _btnSmaller;
    QPushButton* _btnAbout;
    QPushButton* _btnReload;
    QPushButton* _btnBack;
    QPushButton* _btnHome;
    QPushButton* _btnGo;
    QPushButton* _btnStar;
    QPushButton* _btnAddTab;
    URLBar* _txtURL;
    QTabWidget* _tabs;
    QSettings* _settings;
};

#endif

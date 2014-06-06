#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QWebView>
#include <QTabWidget>
#include <QSettings>
#include <QCloseEvent>

#define VERSION_STRING "1.0"
#define HOME_URL "http://tikbew.com/search/?v=1.0"

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
    void TabChanged(int index);
    void CloseTab(int index);
    void CloseCurrentTab();
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
    QPushButton* _btnAddTab;
    QLineEdit* _txtURL;
    QTabWidget* _tabs;
    QSettings* _settings;
};

#endif

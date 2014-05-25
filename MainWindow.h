#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QWebView>

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
    void OnButtonSearchClick();
    void OnButtonHomeClick();
    void UpdateUrl();
    void UpdateTitle();
    void OnAbout();
private:
    QPushButton* _btnLarger;
    QPushButton* _btnStop;
    QPushButton* _btnForward;
    QPushButton* _btnSmaller;
    QPushButton* _btnAbout;
    QPushButton* _btnSearch;
    QPushButton* _btnReload;
    QPushButton* _btnBack;
    QPushButton* _btnHome;
    QPushButton* _btnGo;
    QLineEdit* _txtURL;
    QLineEdit* _txtSearch;
    QWebView* _browser;
};

#endif

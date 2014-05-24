#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class MainWindow: public QDialog
{
    Q_OBJECT
public:
    MainWindow( );
    ~MainWindow( );
    void LoadSettings();
    void SaveSettings();
public slots:
    void OnButtonBrowseClick();
    void OnButtonStopClick();
    void OnButtonForwardClick();
    void OnButtonReverseClick();
    void OnButtonPauseClick();
    void OnAbout();
private:
    QPushButton* _btnBrowse;
    QPushButton* _btnStop;
    QPushButton* _btnForward;
    QPushButton* _btnReverse;
    QPushButton* _btnAbout;
    QLineEdit* _txtURL;
    QLineEdit* _txtSearch;
};

#endif

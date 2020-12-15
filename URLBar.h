#ifndef _URLBar_H_
#define _URLBar_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QWebView>
#include <QTabWidget>
#include <QSettings>
#include <QCloseEvent>
#include <QComboBox>
#include <QFocusEvent>

class URLBar: public QComboBox
{
public:
    URLBar( QDialog* window );
    //~URLBar( );
    void focusInEvent( QFocusEvent* event );
};

#endif

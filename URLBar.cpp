#include "URLBar.h"

#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QBitmap>
#include <QSettings>
#include <QStringList>
#include <QMetaMethod>
#include <QCloseEvent>
#include <QDebug>
#include <QMimeData>
#include <QShortcut>
#include "TikWebView.h"

#include "stop.xpm"
#include "add.xpm"
#include "question.xpm"
#include "play.xpm"
#include "home.xpm"
#include "back.xpm"
#include "reload.xpm"
#include "smaller.xpm"
#include "larger.xpm"
#include "go.xpm"
#include "star.xpm"
#include "TikBew32.xpm"

URLBar::URLBar(QDialog* window) : QComboBox(window)
{
}

//URLBar::~URLBar()
//{
//}

void URLBar::focusInEvent( QFocusEvent* event )
{
    QComboBox::focusInEvent(event);
    if( !(this->lineEdit()->hasSelectedText()) )
    {
        this->lineEdit()->selectAll();
    }
}

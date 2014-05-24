#include "MainWindow.h"

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
#include <QWebView>

#include "stop.xpm"
#include "add.xpm"
#include "reverse.xpm"
#include "forward.xpm"
#include "question.xpm"

MainWindow::~MainWindow()
{
}

/*!
 * MainWindow creator
 */
MainWindow::MainWindow( )
{
    _btnBrowse = NULL;
	_btnStop = NULL;
	_btnForward = NULL;
	_btnReverse = NULL;
	_btnAbout = NULL;

    qDebug() << "CreateControls.";
    setAcceptDrops(true);

    QVBoxLayout* rootLayout = new QVBoxLayout();
    setLayout(rootLayout);

    QHBoxLayout* topRowLayout = new QHBoxLayout();
    rootLayout->addLayout(topRowLayout);

    _txtURL = new QLineEdit( this );
    topRowLayout->addWidget(_txtURL);

    _txtSearch = new QLineEdit( this );
    topRowLayout->addWidget(_txtSearch);

    QHBoxLayout* firstRowLayout = new QHBoxLayout();
    rootLayout->addLayout(firstRowLayout);

    firstRowLayout->setContentsMargins(QMargins(0,0,0,0));
    firstRowLayout->setSpacing(2);

	_btnBrowse = new QPushButton( this );
    _btnBrowse->setIcon(QPixmap(add_xpm));
	_btnBrowse->setToolTip("Add file to playlist.");
    connect(_btnBrowse, SIGNAL(released()), this, SLOT(OnButtonBrowseClick()));
    firstRowLayout->addWidget(_btnBrowse);

	_btnReverse = new QPushButton( this );
    _btnReverse->setIcon(QPixmap(reverse_xpm));
	_btnReverse->setToolTip("Previous track.");
    connect(_btnReverse, SIGNAL(released()), this, SLOT(OnButtonReverseClick()));
    firstRowLayout->addWidget(_btnReverse);

	_btnStop = new QPushButton( this );
    _btnStop->setIcon(QPixmap(stop_xpm));
	_btnStop->setToolTip("Stop.");
    connect(_btnStop, SIGNAL(released()), this, SLOT(OnButtonStopClick()));
    firstRowLayout->addWidget(_btnStop);

    _btnForward = new QPushButton( this );
    _btnForward->setIcon(QPixmap(forward_xpm));
	_btnForward->setToolTip("Next track.");
    connect(_btnForward, SIGNAL(released()), this, SLOT(OnButtonForwardClick()));
    firstRowLayout->addWidget(_btnForward);

	_btnAbout = new QPushButton( this );
    _btnAbout->setIcon(QPixmap(question_xpm));
	_btnAbout->setToolTip("About Vorbital Player.");
    connect(_btnAbout, SIGNAL(released()), this, SLOT(OnAbout()));
    firstRowLayout->addWidget(_btnAbout);

    QHBoxLayout* secondRowLayout = new QHBoxLayout();
    rootLayout->addLayout(secondRowLayout);

    QWebView* view = new QWebView(this);
    view->setUrl(QUrl("http://tikbew.com"));
    secondRowLayout->addWidget(view);

	LoadSettings();
}

void MainWindow::LoadSettings()
{
}

void MainWindow::SaveSettings()
{
}

void MainWindow::OnButtonBrowseClick()
{
}

void MainWindow::OnButtonStopClick()
{
}

void MainWindow::OnButtonReverseClick()
{
}

void MainWindow::OnButtonForwardClick()
{
}

void MainWindow::OnButtonPauseClick()
{
}

/**
* Quit handler.
*/
/*void MainWindow::OnQuit()
{
	SaveSettings();
	_done = true;
#ifdef WIN32
	Sleep(50);
#else
    usleep(50);
#endif
    qDebug() << "Closing OpenAL context and device.";
    alcMakeContextCurrent(NULL);
    alcDestroyContext(_context);
    alcCloseDevice(_device);
}*/

/**
* Shows the about box.
*/
void MainWindow::OnAbout()
{
#ifdef WIN32
    QMessageBox::about(this, "Vorbital Player 4.0", "Vorbital Player 4.0\nCopyright 2006-2013 Zeta Centauri.\nDeveloped by Jason Champion.\nThe Vorbital Player is free software and may be distributed freely.\nhttp://vorbitalplayer.com\nVorbital uses the libogg 1.3.0, libvorbis 1.3.3, wavpack 4.60.1, mpg123 1.14.2, and libsndfile 1.0.25 libraries.");
#else
    QMessageBox::about(this, "Vorbital Player 4.0", "Vorbital Player 4.0\nCopyright 2006-2013 Zeta Centauri.\nDeveloped by Jason Champion.\nThe Vorbital Player is free software and may be distributed freely.\nhttp://vorbitalplayer.com\nVorbital uses the libogg, libvorbis, wavpack, mpg123, and libsndfile libraries.");
#endif
}

/**
* Drag and drop receiver.
*/
/*
void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();
    QString filenames = mimeData->text();
    if( mimeData->hasUrls() )
    {
        qDebug() << "MIME data has URLs from drop action.";
        QList<QUrl> urlList = mimeData->urls();
        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
            QFileInfo info(urlList[i].toLocalFile());
            QListWidgetItem* item = new QListWidgetItem(info.baseName());
            item->setData(Qt::UserRole, QVariant(info.absoluteFilePath()));
            qDebug() << "Adding to playlist: " << urlList[i];
        }
    }
    qDebug() << "Files dropped: " << filenames;
    event->acceptProposedAction();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
    {
        event->acceptProposedAction();
    }
}

void MainWindow::LoadFile( QString& filename )
{
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    OnQuit();
    event->accept();
}
*/

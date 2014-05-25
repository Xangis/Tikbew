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

#include "stop.xpm"
#include "add.xpm"
#include "reverse.xpm"
#include "question.xpm"
#include "remove.xpm"
#include "play.xpm"
#include "TikBew32.xpm"

MainWindow::~MainWindow()
{
}

/*!
 * MainWindow creator
 */
MainWindow::MainWindow( )
{
    _btnLarger = NULL;
	_btnStop = NULL;
	_btnForward = NULL;
    _btnSmaller = NULL;
	_btnAbout = NULL;
    _btnGo = NULL;
    _btnSearch = NULL;
    _btnHome = NULL;
    _btnBack = NULL;
    _btnReload = NULL;

    setAcceptDrops(true);

    QVBoxLayout* rootLayout = new QVBoxLayout();
    setLayout(rootLayout);

    QHBoxLayout* topRowLayout = new QHBoxLayout();
    rootLayout->addLayout(topRowLayout);

    _txtURL = new QLineEdit( this );
    topRowLayout->addWidget(_txtURL);

    _btnGo = new QPushButton( this );
    _btnGo->setIcon(QPixmap(play_xpm));
    _btnGo->setToolTip("Go.");
    connect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonGoClick()));
    topRowLayout->addWidget(_btnGo);

    _txtSearch = new QLineEdit( this );
    topRowLayout->addWidget(_txtSearch);

    _btnSearch = new QPushButton( this );
    _btnSearch->setIcon(QPixmap(play_xpm));
    _btnSearch->setToolTip("Search.");
    connect(_btnSearch, SIGNAL(released()), this, SLOT(OnButtonSearchClick()));
    topRowLayout->addWidget(_btnSearch);

    QHBoxLayout* firstRowLayout = new QHBoxLayout();
    rootLayout->addLayout(firstRowLayout);

    firstRowLayout->setContentsMargins(QMargins(0,0,0,0));
    firstRowLayout->setSpacing(2);

    _btnLarger = new QPushButton( this );
    _btnLarger->setIcon(QPixmap(add_xpm));
    _btnLarger->setToolTip("Larger page");
    connect(_btnLarger, SIGNAL(released()), this, SLOT(OnButtonLargerClick()));
    firstRowLayout->addWidget(_btnLarger);

    _btnSmaller = new QPushButton( this );
    _btnSmaller->setIcon(QPixmap(remove_xpm));
    _btnSmaller->setToolTip("Smaller page.");
    connect(_btnSmaller, SIGNAL(released()), this, SLOT(OnButtonSmallerClick()));
    firstRowLayout->addWidget(_btnSmaller);

    _btnHome = new QPushButton( this );
    _btnHome->setIcon(QPixmap(stop_xpm));
    _btnHome->setToolTip("Home.");
    connect(_btnHome, SIGNAL(released()), this, SLOT(OnButtonHomeClick()));
    firstRowLayout->addWidget(_btnHome);

    _btnBack = new QPushButton( this );
    _btnBack->setIcon(QPixmap(reverse_xpm));
    _btnBack->setToolTip("Previous page.");
    connect(_btnBack, SIGNAL(released()), this, SLOT(OnButtonBackClick()));
    firstRowLayout->addWidget(_btnBack);

    _btnReload = new QPushButton( this );
    _btnReload->setIcon(QPixmap(reverse_xpm));
    _btnReload->setToolTip("Reload page.");
    connect(_btnReload, SIGNAL(released()), this, SLOT(OnButtonReloadClick()));
    firstRowLayout->addWidget(_btnReload);

	_btnStop = new QPushButton( this );
    _btnStop->setIcon(QPixmap(stop_xpm));
	_btnStop->setToolTip("Stop.");
    connect(_btnStop, SIGNAL(released()), this, SLOT(OnButtonStopClick()));
    firstRowLayout->addWidget(_btnStop);

    _btnForward = new QPushButton( this );
    _btnForward->setIcon(QPixmap(play_xpm));
    _btnForward->setToolTip("Forward.");
    connect(_btnForward, SIGNAL(released()), this, SLOT(OnButtonForwardClick()));
    firstRowLayout->addWidget(_btnForward);

	_btnAbout = new QPushButton( this );
    _btnAbout->setIcon(QPixmap(question_xpm));
	_btnAbout->setToolTip("About Tikbew.");
    connect(_btnAbout, SIGNAL(released()), this, SLOT(OnAbout()));
    firstRowLayout->addWidget(_btnAbout);

    QHBoxLayout* secondRowLayout = new QHBoxLayout();
    rootLayout->addLayout(secondRowLayout);

    _browser = new QWebView(this);
    _browser->setUrl(QUrl(HOME_URL));
    secondRowLayout->addWidget(_browser);

    connect(_browser, SIGNAL(urlChanged(QUrl)), this, SLOT(UpdateUrl()));
    connect(_browser, SIGNAL(titleChanged(QString)), this, SLOT(UpdateTitle()));
    connect(_txtURL, SIGNAL(returnPressed()), _btnGo, SIGNAL(clicked()));
    connect(_txtSearch, SIGNAL(returnPressed()), _btnSearch, SIGNAL(clicked()));

    QIcon icon = QIcon(QPixmap(TikBew32_xpm));
    setWindowIcon(icon);
    resize(QSize(1024, 768));
	LoadSettings();
}

void MainWindow::UpdateUrl()
{
    _txtURL->setText(_browser->url().toString());
}

void MainWindow::UpdateTitle()
{
    setWindowTitle(_browser->title() + QString("- TikBew"));
}

void MainWindow::LoadSettings()
{
}

void MainWindow::SaveSettings()
{
}

void MainWindow::OnButtonLargerClick()
{
    _browser->setZoomFactor(_browser->zoomFactor() + 0.1);
}

void MainWindow::OnButtonSmallerClick()
{
    _browser->setZoomFactor(_browser->zoomFactor() - 0.1);
}

void MainWindow::OnButtonStopClick()
{
    _browser->triggerPageAction(QWebPage::Stop);
}

void MainWindow::OnButtonForwardClick()
{
    _browser->triggerPageAction(QWebPage::Forward);
}

void MainWindow::OnButtonReloadClick()
{
    _browser->triggerPageAction(QWebPage::Reload);
}

void MainWindow::OnButtonBackClick()
{
    _browser->triggerPageAction(QWebPage::Back);
}

void MainWindow::OnButtonGoClick()
{
    QString url = _txtURL->text();
    if( !url.startsWith(QString("http")))
    {
        url = QString("http://") + url;
    }
    _browser->setUrl(QUrl(url));
}

void MainWindow::OnButtonSearchClick()
{
    QString searchTerm = _txtSearch->text();
    QString url = QString("http://wbsrch.com/search/?s=tikbew&q=") + searchTerm;
    _browser->setUrl(QUrl(url));
}

void MainWindow::OnButtonHomeClick()
{
    _browser->setUrl(QUrl(HOME_URL));
}

/**
* Shows the about box.
*/
void MainWindow::OnAbout()
{
#ifdef WIN32
    QMessageBox::about(this, QString("TikBew ") + QString(VERSION_STRING),
                       QString("TikBew ") + QString(VERSION_STRING) + QString("\nCopyright 2014 Zeta Centauri.\nDeveloped by Jason Champion.\nTikBew is free software and may be distributed freely.\nhttp://tikbew.com\nTikBew uses the Qt libraries."));
#else
    QMessageBox::about(this, QString("TikBew ") + QString(VERSION_STRING),
                       QString("TikBew ") + QString(VERSION_STRING) + QString("\nCopyright 2014 Zeta Centauri.\nDeveloped by Jason Champion.\nTikBew is free software and may be distributed freely.\nhttp://tikbew.com\nTikBew uses the Qt libraries."));
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

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
#include <QShortcut>

#include "stop.xpm"
#include "add.xpm"
#include "question.xpm"
#include "remove.xpm"
#include "play.xpm"
#include "home.xpm"
#include "back.xpm"
#include "reload.xpm"
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

    _btnBack = new QPushButton( this );
    _btnBack->setIcon(QPixmap(back_xpm));
    _btnBack->setToolTip("Previous page (Alt+Left)");
    connect(_btnBack, SIGNAL(released()), this, SLOT(OnButtonBackClick()));
    QShortcut* shortcutAltLeft = new QShortcut(QKeySequence("Alt+Left"), this);
    connect(shortcutAltLeft, SIGNAL(activated()), this, SLOT(OnButtonBackClick()));
    topRowLayout->addWidget(_btnBack);

    _btnStop = new QPushButton( this );
    _btnStop->setIcon(QPixmap(stop_xpm));
    _btnStop->setToolTip("Stop.");
    connect(_btnStop, SIGNAL(released()), this, SLOT(OnButtonStopClick()));
    topRowLayout->addWidget(_btnStop);

    _btnForward = new QPushButton( this );
    _btnForward->setIcon(QPixmap(play_xpm));
    _btnForward->setToolTip("Forward (Alt+Right)");
    connect(_btnForward, SIGNAL(released()), this, SLOT(OnButtonForwardClick()));
    QShortcut* shortcutAltRight = new QShortcut(QKeySequence("Alt+Right"), this);
    connect(shortcutAltRight, SIGNAL(activated()), this, SLOT(OnButtonForwardClick()));
    topRowLayout->addWidget(_btnForward);

    _txtURL = new QLineEdit( this );
    connect(_txtURL, SIGNAL(returnPressed()), this, SLOT(OnButtonGoClick()));
    QShortcut* shortcutAltD = new QShortcut(QKeySequence("Alt+D"), this);
    connect(shortcutAltD, SIGNAL(activated()), _txtURL, SLOT(setFocus()));
    topRowLayout->addWidget(_txtURL);

    //_btnGo = new QPushButton( this );
    //_btnGo->setIcon(QPixmap(play_xpm));
    //_btnGo->setToolTip("Go.");
    //connect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonGoClick()));
    //topRowLayout->addWidget(_btnGo);

    _txtSearch = new QLineEdit( this );
    _txtSearch->setMaximumWidth(200);
    _txtSearch->setFixedWidth(200);
    connect(_txtSearch, SIGNAL(returnPressed()), this, SLOT(OnButtonSearchClick()));
    topRowLayout->addWidget(_txtSearch);

    //_btnSearch = new QPushButton( this );
    //_btnSearch->setIcon(QPixmap(play_xpm));
    //_btnSearch->setToolTip("Search.");
    //connect(_btnSearch, SIGNAL(released()), this, SLOT(OnButtonSearchClick()));
    //topRowLayout->addWidget(_btnSearch);

    //QHBoxLayout* firstRowLayout = new QHBoxLayout();
    //rootLayout->addLayout(firstRowLayout);

    //firstRowLayout->setContentsMargins(QMargins(0,0,0,0));
    //firstRowLayout->setSpacing(2);

    _btnLarger = new QPushButton( this );
    _btnLarger->setIcon(QPixmap(add_xpm));
    _btnLarger->setToolTip("Larger page (Ctrl++)");
    connect(_btnLarger, SIGNAL(released()), this, SLOT(OnButtonLargerClick()));
    QShortcut* shortcutCtrlPlus = new QShortcut(QKeySequence::ZoomIn, this);
    connect(shortcutCtrlPlus, SIGNAL(activated()), this, SLOT(OnButtonLargerClick()));
    topRowLayout->addWidget(_btnLarger);

    _btnSmaller = new QPushButton( this );
    _btnSmaller->setIcon(QPixmap(remove_xpm));
    _btnSmaller->setToolTip("Smaller page (Ctrl+-)");
    connect(_btnSmaller, SIGNAL(released()), this, SLOT(OnButtonSmallerClick()));
    QShortcut* shortcutCtrlMinus = new QShortcut(QKeySequence::ZoomOut, this);
    connect(shortcutCtrlMinus, SIGNAL(activated()), this, SLOT(OnButtonSmallerClick()));
    topRowLayout->addWidget(_btnSmaller);

    _btnHome = new QPushButton( this );
    _btnHome->setIcon(QPixmap(home_xpm));
    _btnHome->setToolTip("Home.");
    connect(_btnHome, SIGNAL(released()), this, SLOT(OnButtonHomeClick()));
    topRowLayout->addWidget(_btnHome);

    _btnReload = new QPushButton( this );
    _btnReload->setIcon(QPixmap(reload_xpm));
    _btnReload->setToolTip("Reload page (F5)");
    connect(_btnReload, SIGNAL(released()), this, SLOT(OnButtonReloadClick()));
    QShortcut* shortcutF5 = new QShortcut(QKeySequence::Refresh, this);
    connect(shortcutF5, SIGNAL(activated()), this, SLOT(OnButtonReloadClick()));
    topRowLayout->addWidget(_btnReload);

    _btnAbout = new QPushButton( this );
    _btnAbout->setIcon(QPixmap(question_xpm));
    _btnAbout->setToolTip("About Tikbew (F1)");
    connect(_btnAbout, SIGNAL(released()), this, SLOT(OnAbout()));
    QShortcut* shortcutF1 = new QShortcut(QKeySequence::HelpContents, this);
    connect(shortcutF1, SIGNAL(activated()), this, SLOT(OnAbout()));
    topRowLayout->addWidget(_btnAbout);

    QHBoxLayout* secondRowLayout = new QHBoxLayout();
    rootLayout->addLayout(secondRowLayout);

    _tabs = new QTabWidget();
    _tabs->setTabsClosable(true);
    _tabs->setMovable(true);
    _tabs->setUsesScrollButtons(true);
    connect(_tabs, SIGNAL(currentChanged(int)), this, SLOT(TabChanged(int)));
    connect(_tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseTab(int)));
    secondRowLayout->addWidget(_tabs);
    QShortcut* shortcutCtrlT = new QShortcut(QKeySequence::AddTab, this);
    connect(shortcutCtrlT, SIGNAL(activated()), this, SLOT(OnAddTab()));

    QWebView* webView = new QWebView(this);
    webView->setUrl(QUrl(HOME_URL));
    connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(UpdateUrl()));
    connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(UpdateTitle()));
    _tabs->addTab(webView, "Tikbew");

    _btnAddTab = new QPushButton(this);
    _btnAddTab->setIcon(QPixmap(add_xpm));
    _btnAddTab->setToolTip("Add tab (Ctrl+T)");
    connect(_btnAddTab, SIGNAL(released()), this, SLOT(OnAddTab()));
    //_tabs->addTab(_btnAddTab);
    _tabs->setCornerWidget(_btnAddTab);

    QIcon icon = QIcon(QPixmap(TikBew32_xpm));
    setWindowIcon(icon);
    resize(QSize(1024, 768));
    _txtSearch->setFocus();
    QList<QPushButton*> buttonList = findChildren<QPushButton*>();
    foreach(QPushButton* button, buttonList)
    {
        button->setDefault(false);
        button->setAutoDefault(false);
    }

    QShortcut* shortcutCtrlW = new QShortcut(QKeySequence("Ctrl+W"), this);
    connect(shortcutCtrlW, SIGNAL(activated()), this, SLOT(CloseCurrentTab()));

    LoadSettings();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    OnQuit();
    event->accept();
}

void MainWindow::OnQuit()
{
    SaveSettings();
}

void MainWindow::TabChanged(int index)
{
    UpdateUrl();
    UpdateTitle();
}

void MainWindow::CloseCurrentTab()
{
    CloseTab(_tabs->currentIndex());
}

void MainWindow::CloseTab(int index)
{
    if( _tabs->count() == 1)
    {
        SaveSettings();
    }
    QWidget* tab = _tabs->widget(index);
    _tabs->removeTab(index);
    tab->deleteLater();
}

void MainWindow::UpdateUrl()
{
    _txtURL->setText(((QWebView*)_tabs->currentWidget())->url().toString());
}

void MainWindow::UpdateTitle()
{
    setWindowTitle(((QWebView*)_tabs->currentWidget())->title() + QString(" - TikBew"));
    _tabs->setTabText(_tabs->currentIndex(), ((QWebView*)_tabs->currentWidget())->title());
}

void MainWindow::LoadSettings()
{
    _settings = new QSettings();
    QString loadedURLs = _settings->value("loadedURLs").toString();
    QStringList urls = loadedURLs.split(";;");
    for( int i = 0; i < urls.count(); i++)
    {
        QWebView* newTab = new QWebView(this);
        _tabs->addTab(newTab, "TikBew");
        connect(newTab, SIGNAL(urlChanged(QUrl)), this, SLOT(UpdateUrl()));
        connect(newTab, SIGNAL(titleChanged(QString)), this, SLOT(UpdateTitle()));
        newTab->setUrl(QUrl(urls[i]));
    }
}

void MainWindow::SaveSettings()
{
    QStringList urls;
    for( int i = 0; i < _tabs->count(); i++)
    {
        urls.append(((QWebView*)(_tabs->widget(i)))->url().toString());
    }
    QString loadedURLs = urls.join(";;");
    _settings->setValue("loadedURLs", loadedURLs);
    _settings->sync();
}

void MainWindow::OnButtonLargerClick()
{
    ((QWebView*)_tabs->currentWidget())->setZoomFactor(((QWebView*)_tabs->currentWidget())->zoomFactor() + 0.1);
}

void MainWindow::OnButtonSmallerClick()
{
    ((QWebView*)_tabs->currentWidget())->setZoomFactor(((QWebView*)_tabs->currentWidget())->zoomFactor() - 0.1);
}

void MainWindow::OnButtonStopClick()
{
    ((QWebView*)_tabs->currentWidget())->triggerPageAction(QWebPage::Stop);
}

void MainWindow::OnButtonForwardClick()
{
    ((QWebView*)_tabs->currentWidget())->triggerPageAction(QWebPage::Forward);
}

void MainWindow::OnButtonReloadClick()
{
    ((QWebView*)_tabs->currentWidget())->triggerPageAction(QWebPage::Reload);
}

void MainWindow::OnButtonBackClick()
{
    ((QWebView*)_tabs->currentWidget())->triggerPageAction(QWebPage::Back);
}

void MainWindow::OnAddTab()
{
    QWebView* newTab = new QWebView(this);
    connect(newTab, SIGNAL(urlChanged(QUrl)), this, SLOT(UpdateUrl()));
    connect(newTab, SIGNAL(titleChanged(QString)), this, SLOT(UpdateTitle()));
    _tabs->addTab(newTab, "TikBew");
    newTab->setUrl(QUrl(HOME_URL));
    _tabs->setCurrentIndex(_tabs->count() -1);
}

void MainWindow::OnButtonGoClick()
{
    QString url = _txtURL->text();
    if( !url.startsWith(QString("http")))
    {
        url = QString("http://") + url;
    }
    ((QWebView*)_tabs->currentWidget())->setUrl(QUrl(url));
}

void MainWindow::OnButtonSearchClick()
{
    QString searchTerm = _txtSearch->text();
    QString url = QString("http://wbsrch.com/search/?s=tikbew&q=") + searchTerm;
    ((QWebView*)_tabs->currentWidget())->setUrl(QUrl(url));
}

void MainWindow::OnButtonHomeClick()
{
    ((QWebView*)_tabs->currentWidget())->setUrl(QUrl(HOME_URL));
}

/**
* Shows the about box.
*/
void MainWindow::OnAbout()
{
#ifdef WIN32
    QMessageBox::about(this, QString("TikBew ") + QString(VERSION_STRING),
                       QString("TikBew ") + QString(VERSION_STRING) + QString("\nCopyright 2014 Championix, LLC.\nDeveloped by Jason Champion.\nTikBew is free software and may be distributed freely.\nhttp://tikbew.com\nTikBew uses the Qt libraries."));
#else
    QMessageBox::about(this, QString("TikBew ") + QString(VERSION_STRING),
                       QString("TikBew ") + QString(VERSION_STRING) + QString("\nCopyright 2014 Championix, LLC.\nDeveloped by Jason Champion.\nTikBew is free software and may be distributed freely.\nhttp://tikbew.com\nTikBew uses the Qt libraries."));
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

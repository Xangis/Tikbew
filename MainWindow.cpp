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
    _btnHome = NULL;
    _btnBack = NULL;
    _btnReload = NULL;

    setAcceptDrops(true);

    QIcon icon = QIcon(QPixmap(TikBew32_xpm));
    setWindowIcon(icon);

    QVBoxLayout* rootLayout = new QVBoxLayout();
    rootLayout->setSpacing(0);
    rootLayout->setMargin(0);
    rootLayout->setContentsMargins(0,0,0,0);
    setLayout(rootLayout);

    QHBoxLayout* topRowLayout = new QHBoxLayout();
    topRowLayout->setSpacing(4);
    topRowLayout->setMargin(3);
    rootLayout->addLayout(topRowLayout);

    _btnBack = new QPushButton( this );
    _btnBack->setIcon(QPixmap(back_xpm));
    _btnBack->setMaximumWidth(32);
    _btnBack->setToolTip("Previous page (Alt+Left)");
    connect(_btnBack, SIGNAL(released()), this, SLOT(OnButtonBackClick()));
    QShortcut* shortcutAltLeft = new QShortcut(QKeySequence("Alt+Left"), this);
    connect(shortcutAltLeft, SIGNAL(activated()), this, SLOT(OnButtonBackClick()));
    topRowLayout->addWidget(_btnBack);

    _btnForward = new QPushButton( this );
    _btnForward->setIcon(QPixmap(play_xpm));
    _btnForward->setMaximumWidth(32);
    _btnForward->setToolTip("Forward (Alt+Right)");
    connect(_btnForward, SIGNAL(released()), this, SLOT(OnButtonForwardClick()));
    QShortcut* shortcutAltRight = new QShortcut(QKeySequence("Alt+Right"), this);
    connect(shortcutAltRight, SIGNAL(activated()), this, SLOT(OnButtonForwardClick()));
    topRowLayout->addWidget(_btnForward);

    //_txtURL = new QLineEdit( this );
    _txtURL = new URLBar(this);
    _txtURL->setEditable(true);
    _txtURL->setInsertPolicy(QComboBox::InsertAtTop);
#ifdef WIN32
    _txtURL->setMinimumSize(200, 28);
#else
    _txtURL->setMinimumSize(200, 32);
#endif
    connect(_txtURL, SIGNAL(returnPressed()), this, SLOT(OnButtonGoClick()));
    QShortcut* shortcutAltD = new QShortcut(QKeySequence("Alt+D"), this);
    connect(shortcutAltD, SIGNAL(activated()), _txtURL, SLOT(setFocus()));
    topRowLayout->addWidget(_txtURL);
    //connect(_txtURL, SIGNAL(activated()), _txtURL, SLOT(selectAll()));
    //connect(_txtURL->lineEdit(), SIGNAL(returnPressed()), this, SLOT(OnButtonGoClick()));

    _btnGo = new QPushButton( this );
    _btnGo->setIcon(QPixmap(go_xpm));
    _btnGo->setMaximumWidth(32);
    _btnGo->setToolTip("Go.");
    _btnGo->setAutoDefault(true);
    _btnGo->setDefault(true);
    connect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonGoClick()));
    topRowLayout->addWidget(_btnGo);

    _btnStar = new QPushButton( this );
    _btnStar->setIcon(QPixmap(star_xpm));
    _btnStar->setMaximumWidth(32);
    _btnStar->setToolTip("Bookmark this page.");
    connect(_btnStar, SIGNAL(released()), this, SLOT(OnAddBookmark()));
    topRowLayout->addWidget(_btnStar);

    _btnLarger = new QPushButton( this );
    _btnLarger->setIcon(QPixmap(larger_xpm));
    _btnLarger->setMaximumWidth(32);
    _btnLarger->setToolTip("Zoom In (Ctrl++)");
    connect(_btnLarger, SIGNAL(released()), this, SLOT(OnButtonLargerClick()));
    QShortcut* shortcutCtrlPlus = new QShortcut(QKeySequence::ZoomIn, this);
    connect(shortcutCtrlPlus, SIGNAL(activated()), this, SLOT(OnButtonLargerClick()));
    topRowLayout->addWidget(_btnLarger);

    _btnSmaller = new QPushButton( this );
    _btnSmaller->setIcon(QPixmap(smaller_xpm));
    _btnSmaller->setMaximumWidth(32);
    _btnSmaller->setToolTip("Zoom Out (Ctrl+-)");
    connect(_btnSmaller, SIGNAL(released()), this, SLOT(OnButtonSmallerClick()));
    QShortcut* shortcutCtrlMinus = new QShortcut(QKeySequence::ZoomOut, this);
    connect(shortcutCtrlMinus, SIGNAL(activated()), this, SLOT(OnButtonSmallerClick()));
    topRowLayout->addWidget(_btnSmaller);

    _btnHome = new QPushButton( this );
    _btnHome->setIcon(QPixmap(home_xpm));
    _btnHome->setMaximumWidth(32);
    _btnHome->setToolTip("Home.");
    connect(_btnHome, SIGNAL(released()), this, SLOT(OnButtonHomeClick()));
    topRowLayout->addWidget(_btnHome);

    _btnReload = new QPushButton( this );
    _btnReload->setIcon(QPixmap(reload_xpm));
    _btnReload->setMaximumWidth(32);
    _btnReload->setToolTip("Reload page (F5)");
    connect(_btnReload, SIGNAL(released()), this, SLOT(OnButtonReloadClick()));
    QShortcut* shortcutF5 = new QShortcut(QKeySequence::Refresh, this);
    connect(shortcutF5, SIGNAL(activated()), this, SLOT(OnButtonReloadClick()));
    topRowLayout->addWidget(_btnReload);

    _btnAbout = new QPushButton( this );
    _btnAbout->setIcon(QPixmap(question_xpm));
    _btnAbout->setMaximumWidth(32);
    _btnAbout->setToolTip("About TikBew (F1)");
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
    // This sets the size of the widget, not the tab.
    //_tabs->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    _tabs->setStyleSheet(QString("QTabBar::tab { width: 176px; } "));
    connect(_tabs, SIGNAL(currentChanged(int)), this, SLOT(TabChanged(int)));
    connect(_tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseTab(int)));

    LoadSettings();
    // Only add a tab if one didn't load.
    if(_tabs->count() < 1)
    {
        TikWebView* webView = new TikWebView(this);
        webView->setUrl(QUrl(HOME_URL));
        connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(UpdateUrl()));
        connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(UpdateTitle()));
        connect(webView, SIGNAL(loadStarted()), this, SLOT(LoadStarted()));
        connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(LoadFinished(bool)));
        _tabs->addTab(webView, "TikBew");
    }

    _btnAddTab = new QPushButton(this);
    _btnAddTab->setIcon(QPixmap(add_xpm));
    _btnAddTab->setToolTip("Add tab (Ctrl+T)");
    connect(_btnAddTab, SIGNAL(released()), this, SLOT(OnAddTab()));
    _tabs->setCornerWidget(_btnAddTab);

    secondRowLayout->addWidget(_tabs);
    QShortcut* shortcutCtrlT = new QShortcut(QKeySequence::AddTab, this);
    connect(shortcutCtrlT, SIGNAL(activated()), this, SLOT(OnAddTab()));

    _txtURL->setFocus();
    QList<QPushButton*> buttonList = findChildren<QPushButton*>();

    QShortcut* shortcutCtrlW = new QShortcut(QKeySequence("Ctrl+W"), this);
    connect(shortcutCtrlW, SIGNAL(activated()), this, SLOT(CloseCurrentTab()));
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

void MainWindow::TabChanged(int)
{
    UpdateUrl();
    UpdateTitle();
}

void MainWindow::LoadStarted()
{
    _btnGo->setIcon(QPixmap(stop_xpm));
    _btnGo->setToolTip("Stop.");
    disconnect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonGoClick()));
    connect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonStopClick()));
}

void MainWindow::LoadFinished(bool)
{
    _btnGo->setIcon(QPixmap(go_xpm));
    _btnGo->setToolTip("Go.");
    disconnect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonStopClick()));
    connect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonGoClick()));
}

void MainWindow::CloseCurrentTab()
{
    CloseTab(_tabs->currentIndex());
}

void MainWindow::OnAddBookmark()
{
    // TODO: Allow bookmark removal.
    QString currentURL = ((TikWebView*)_tabs->currentWidget())->url().toString();
    if( currentURL == "" || currentURL == "http://" || currentURL == "https://")
    {
        QMessageBox box;
        box.setWindowTitle("Nothing to Bookmark");
        box.setText("You're not on a page.");
        box.setStandardButtons(QMessageBox::Ok);
        box.setDefaultButton(QMessageBox::Ok);
        box.exec();
        return;
    }
    for( int i = 0; i < _txtURL->count(); i++)
    {
        if(_txtURL->itemText(i) == currentURL)
        {
            QMessageBox box;
            box.setWindowTitle("Already Bookmarked");
            box.setText("You've already bookmarked this page.");
            box.setStandardButtons(QMessageBox::Ok);
            box.setDefaultButton(QMessageBox::Ok);
            box.exec();
            return;
        }
    }
    _txtURL->addItem(currentURL);
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
    _txtURL->lineEdit()->setText(((TikWebView*)_tabs->currentWidget())->url().toString());
}

void MainWindow::UpdateTitle()
{
    setWindowTitle(((TikWebView*)_tabs->currentWidget())->title() + QString(" - TikBew"));
    _tabs->setTabText(_tabs->currentIndex(), ((TikWebView*)_tabs->currentWidget())->title());
}

void MainWindow::LoadSettings()
{
    _settings = new QSettings();
    QString loadedURLs = _settings->value("loadedURLs").toString();
    QStringList urls = loadedURLs.split(";;");
    if( urls.count() > 0 )
    {
        for( int i = 0; i < urls.count(); i++)
        {
            TikWebView* newTab = new TikWebView(this);
            _tabs->addTab(newTab, "TikBew");
            connect(newTab, SIGNAL(urlChanged(QUrl)), this, SLOT(UpdateUrl()));
            connect(newTab, SIGNAL(titleChanged(QString)), this, SLOT(UpdateTitle()));
            connect(newTab, SIGNAL(loadStarted()), this, SLOT(LoadStarted()));
            connect(newTab, SIGNAL(loadFinished(bool)), this, SLOT(LoadFinished(bool)));
            newTab->setUrl(QUrl(urls[i]));
        }
    }
    else
    {
        TikWebView* newTab = new TikWebView(this);
        _tabs->addTab(newTab, "TikBew");
        connect(newTab, SIGNAL(urlChanged(QUrl)), this, SLOT(UpdateUrl()));
        connect(newTab, SIGNAL(titleChanged(QString)), this, SLOT(UpdateTitle()));
        connect(newTab, SIGNAL(loadStarted()), this, SLOT(LoadStarted()));
        connect(newTab, SIGNAL(loadFinished(bool)), this, SLOT(LoadFinished(bool)));
        newTab->setUrl(QUrl("https://wbsrch.com"));
    }
    QString bookmarkedURLs = _settings->value("bookmarkedURLs").toString();
    QStringList bookmarks = bookmarkedURLs.split(";;");
    for( int i = 0; i < bookmarks.count(); i++)
    {
        _txtURL->addItem(bookmarks[i]);
    }
    int w = _settings->value("width").toInt();
    int h = _settings->value("height").toInt();
    if( w && h)
    {
        resize(QSize(w, h));
    }
    else
    {
        resize(QSize(1024, 768));
    }
}

void MainWindow::SaveSettings()
{
    QStringList urls;
    for( int i = 0; i < _tabs->count(); i++)
    {
        urls.append(((TikWebView*)(_tabs->widget(i)))->url().toString());
    }
    QString loadedURLs = urls.join(";;");

    QStringList bookmarks;
    for( int i = 0; i < _txtURL->count(); i++)
    {
        bookmarks.append(_txtURL->itemText(i));
    }
    QString loadedBookmarks = bookmarks.join(";;");

    _settings->setValue("loadedURLs", loadedURLs);
    _settings->setValue("bookmarkedURLs", loadedBookmarks);
    _settings->setValue("width", this->width());
    _settings->setValue("height", this->height());
    _settings->sync();
}

void MainWindow::OnButtonLargerClick()
{
    ((TikWebView*)_tabs->currentWidget())->setZoomFactor(((TikWebView*)_tabs->currentWidget())->zoomFactor() + 0.1);
}

void MainWindow::OnButtonSmallerClick()
{
    ((TikWebView*)_tabs->currentWidget())->setZoomFactor(((TikWebView*)_tabs->currentWidget())->zoomFactor() - 0.1);
}

void MainWindow::OnButtonStopClick()
{
    ((TikWebView*)_tabs->currentWidget())->triggerPageAction(QWebPage::Stop);
    _btnGo->setIcon(QPixmap(go_xpm));
    _btnGo->setToolTip("Go.");
    disconnect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonStopClick()));
    connect(_btnGo, SIGNAL(released()), this, SLOT(OnButtonGoClick()));
}

void MainWindow::OnButtonForwardClick()
{
    ((TikWebView*)_tabs->currentWidget())->triggerPageAction(QWebPage::Forward);
}

void MainWindow::OnButtonReloadClick()
{
    ((TikWebView*)_tabs->currentWidget())->triggerPageAction(QWebPage::Reload);
}

void MainWindow::OnButtonBackClick()
{
    ((TikWebView*)_tabs->currentWidget())->triggerPageAction(QWebPage::Back);
}

void MainWindow::OnAddTab()
{
    TikWebView* newTab = new TikWebView(this);
    connect(newTab, SIGNAL(urlChanged(QUrl)), this, SLOT(UpdateUrl()));
    connect(newTab, SIGNAL(titleChanged(QString)), this, SLOT(UpdateTitle()));
    connect(newTab, SIGNAL(loadStarted()), this, SLOT(LoadStarted()));
    connect(newTab, SIGNAL(loadFinished(bool)), this, SLOT(LoadFinished(bool)));
    _tabs->addTab(newTab, "TikBew");
    newTab->setUrl(QUrl(HOME_URL));
    _tabs->setCurrentIndex(_tabs->count() -1);
}

void MainWindow::OnButtonGoClick()
{
    QUrl url = QUrl::fromUserInput(_txtURL->currentText());
    QMessageBox box;
//    box.setWindowTitle("Go clicked.");
//    box.setText(url);
//    box.setStandardButtons(QMessageBox::Ok);
//    box.setDefaultButton(QMessageBox::Ok);
//    box.exec();
    ((TikWebView*)_tabs->currentWidget())->setUrl(QUrl(url));
    //((TikWebView*)_tabs->currentWidget())->setUrl(QUrl(url));
    //((TikWebView*)_tabs->currentWidget())->load(QUrl(url));
}

void MainWindow::OnButtonHomeClick()
{
    ((TikWebView*)_tabs->currentWidget())->setUrl(QUrl(HOME_URL));
}

/**
* Shows the about box.
*/
void MainWindow::OnAbout()
{
    QMessageBox::about(this, QString("TikBew ") + QString(VERSION_STRING),
                       QString("TikBew ") + QString(VERSION_STRING) + QString("\nCopyright 2014-2020 Lambda Centauri.\nDeveloped by Jason Champion.\nTikBew is free software and may be distributed freely.\nhttps://lambdacentauri.com/software_tikbew.htm\nTikBew uses the Qt libraries."));
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

#include "TikWebView.h"
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QMenu>

TikWebView::TikWebView() : QWebView()
{
    //this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showCustomContextMenu(const QPoint&)));
}

TikWebView::TikWebView(QWidget* parent) : QWebView(parent)
{
    // Uncommenting this breaks the context menu entirely.
    //this->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showCustomContextMenu(const QPoint&)));
}

//void TikWebView::showCustomContextMenu(QPoint* point)
//{
//    QMenu* menu = this->page()->createStandardContextMenu();
//    QAction* pActionOpenInNewTab = menu->addAction("Open Link in New Tab");
//    //menu->removeAction();
//    connect(pActionOpenInNewTab, SIGNAL(triggered()), this, SLOT(OpenInNewTab()));
//    menu->exec(mapToGlobal(QPoint(point->x(), point->y())));
//    delete menu;
//}

void TikWebView::slotOpenInNewTab()
{
    QMessageBox box;
    box.setWindowTitle("Open in new tab: selected HTML");
    box.setText(selectedHtml());
    box.setStandardButtons(QMessageBox::Ok);
    box.setDefaultButton(QMessageBox::Ok);
    box.exec();
}

void TikWebView::slotCopyLinkLocation()
{
    QMessageBox box;
    box.setWindowTitle("Copy link locataion clicked");
    box.setText(selectedHtml());
    box.setStandardButtons(QMessageBox::Ok);
    box.setDefaultButton(QMessageBox::Ok);
    box.exec();
}

// This doesn't work either.
/*
void TikWebView::triggerPageAction(QWebPage::WebAction action, bool checked)
{
    if( action == QWebPage::WebAction::OpenLinkInNewWindow)
    {
        OpenInNewTab();
    }
    else
    {
        QWebView::triggerPageAction(action, checked);
    }
}
*/

void TikWebView::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu;
    QAction* actionOpenInNewTab = menu.addAction("Open in New Tab");
    QAction* actionCopyLinkLocation = menu.addAction("Copy Link Location");
    connect(actionOpenInNewTab, SIGNAL(triggered()), this, SLOT(slotOpenInNewTab));
    connect(actionCopyLinkLocation, SIGNAL(triggered()), this, SLOT(slotOpenInNewTab));
}


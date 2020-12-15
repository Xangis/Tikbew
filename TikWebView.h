#ifndef TIKWEBVIEW_H
#define TIKWEBVIEW_H

#include <QWebView>
#include <QWebPage>

/**
 * @brief Derived class overrides QWebView for custom behavior.
 */
class TikWebView: public QWebView
{

public:
    //void showCustomContextMenu(QPoint* point);
    TikWebView();
    TikWebView(QWidget* parent);
    ~TikWebView() {}
    void contextMenuEvent(QContextMenuEvent* event);
    //void triggerPageAction(QWebPage::WebAction action, bool checked=false);
private slots:
    void slotOpenInNewTab();
    void slotCopyLinkLocation();
};

#endif // TIKWEBVIEW_H

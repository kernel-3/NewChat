//
// Created by utopia on 2025/4/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ContactList.h" resolved
#include "contactlist.h"
#include "contactlistitem.h"


ContactList::ContactList(QListWidget *parent) :
    QListWidget (parent) {
    initUI();
}

ContactList::~ContactList() {

}

void ContactList::addContact(const QString &avatar, const QString &name, const QString &lastMsg, const QString &time,
    int unread, bool online) {
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(0, 64));

    ContactListItem *widget = new ContactListItem;
    widget->setData(avatar, name, lastMsg, time, unread, online);

    addItem(item);
    setItemWidget(item, widget);
}

void ContactList::initUI() {
    setFrameShape(QFrame::NoFrame);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(
        "QListWidget {"
        "   background: white;"
        "   border: none;"
        "   outline: 0;"
        "}"
        "QListWidget::item {"
        "   border: none;"
        "   padding: 0;"
        "}"
        "QScrollBar:vertical {"
        "   width: 6px;"
        "   background: transparent;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #D8D8D8;"
        "   min-height: 20px;"
        "   border-radius: 3px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   height: 0;"
        "}"
    );
}


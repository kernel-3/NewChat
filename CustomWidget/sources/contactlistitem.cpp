//
// Created by utopia on 2025/4/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ContactListItem.h" resolved

#include "contactlistitem.h"


ContactListItem::ContactListItem(QWidget *parent) :
    QWidget(parent){
    initUI();
    setFixedHeight(64);
}

ContactListItem::~ContactListItem() {

}

void ContactListItem::setData(const QString &avatar, const QString &name, const QString &lastMsg, const QString &time,
    int unread, bool online) {
    m_avatar->setPixmap(QPixmap(avatar).scaled(40,40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_name->setText(name);
    m_lastMsg->setText(lastMsg);
    m_time->setText(time);

    if(unread > 0) {
        m_unread->setText(QString::number(unread));
        m_unread->setVisible(true);
    } else {
        m_unread->setVisible(false);
    }

    m_onlineIndicator->setVisible(online);
}

void ContactListItem::initUI() {
     QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->setContentsMargins(12, 8, 12, 8);
        mainLayout->setSpacing(12);

        // 头像区域
        QWidget *avatarContainer = new QWidget;
        QVBoxLayout *avatarLayout = new QVBoxLayout(avatarContainer);
        avatarLayout->setContentsMargins(0,0,0,0);

        m_avatar = new QLabel;
        m_avatar->setFixedSize(40,40);
        m_avatar->setStyleSheet("border-radius: 20px;");
        avatarLayout->addWidget(m_avatar);

        // 在线状态指示器
        m_onlineIndicator = new QLabel;
        m_onlineIndicator->setFixedSize(10,10);
        m_onlineIndicator->setStyleSheet(
            "background: #7ED321;"
            "border-radius: 5px;"
            "border: 2px solid white;"
        );
        avatarLayout->addWidget(m_onlineIndicator, 0, Qt::AlignRight | Qt::AlignBottom);

        mainLayout->addWidget(avatarContainer);

        // 文本信息区域
        QWidget *textContainer = new QWidget;
        QVBoxLayout *textLayout = new QVBoxLayout(textContainer);
        textLayout->setContentsMargins(0,0,0,0);
        textLayout->setSpacing(4);

        m_name = new QLabel;
        m_name->setStyleSheet(
            "font-size: 14px;"
            "color: #333333;"
            "font-weight: 500;"
        );

        m_lastMsg = new QLabel;
        m_lastMsg->setStyleSheet(
            "font-size: 12px;"
            "color: #666666;"
        );
        m_lastMsg->setMaximumWidth(160);
        m_lastMsg->setWordWrap(true);

        textLayout->addWidget(m_name);
        textLayout->addWidget(m_lastMsg);
        mainLayout->addWidget(textContainer, 1);

        // 右侧信息区域
        QWidget *rightContainer = new QWidget;
        QVBoxLayout *rightLayout = new QVBoxLayout(rightContainer);
        rightLayout->setContentsMargins(0,0,0,0);
        rightLayout->setSpacing(4);
        rightLayout->setAlignment(Qt::AlignTop);

        m_time = new QLabel;
        m_time->setStyleSheet(
            "font-size: 12px;"
            "color: #999999;"
        );

        m_unread = new QLabel;
        m_unread->setStyleSheet(
            "background: #FA5151;"
            "color: white;"
            "border-radius: 9px;"
            "min-width: 18px;"
            "max-width: 18px;"
            "padding: 0 2px;"
            "font-size: 12px;"
            "qproperty-alignment: AlignCenter;"
        );
        m_unread->setFixedSize(18,18);
        m_unread->setVisible(false);

        rightLayout->addWidget(m_time);
        rightLayout->addWidget(m_unread);
        rightLayout->addStretch();

        mainLayout->addWidget(rightContainer);

        // 整体样式
        setStyleSheet(
            "ContactListItem {"
            "   border-bottom: 1px solid #EBEBEB;"
            "   background: transparent;"
            "}"
            "ContactListItem:hover {"
            "   background: #F5F5F5;"
            "}"
        );
}

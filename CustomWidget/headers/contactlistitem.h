//
// Created by utopia on 2025/4/24.
//

#ifndef CONTACTLISTITEM_H
#define CONTACTLISTITEM_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>

// 自定义联系人列表项控件
class ContactListItem : public QWidget {
Q_OBJECT

public:
    explicit ContactListItem(QWidget *parent = nullptr);
    ~ContactListItem() override;

public:
    void setData(const QString& avatar, const QString& name,
               const QString& lastMsg, const QString& time,
               int unread = 0, bool online = false);

private:
    void initUI();

private:
    QLabel *m_avatar;
    QLabel *m_onlineIndicator;
    QLabel *m_name;
    QLabel *m_lastMsg;
    QLabel *m_time;
    QLabel *m_unread;
};


#endif //CONTACTLISTITEM_H

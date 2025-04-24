//
// Created by utopia on 2025/4/22.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QJsonValue>
#include <QJsonObject>
#include <QSplitter>


#include "../CustomWidget/basewidget.h"
#include "../NetWork/clientsocket.h"
#include "../CustomWidget/animationstackedwidget.h"
#include "chatwindow.h"
#include "../CustomWidget/contactheaderwidget.h"
#include "../CustomWidget/contactlist.h"
#include "../CustomWidget/contactlistitem.h"

class MainWindow : public CustomMoveWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setSocket(ClientSocket *tcpSocket,const QString &ame);

protected:
    void changeEvent(QEvent *) override;
    void closeEvent(QCloseEvent *) override;
    void showEvent(QShowEvent *) override;

private:
    void initUI();
    void initStyle();
    void initConnection();
    // 左侧导航栏
    QWidget* createLeftNav();
    // 中间联系人列表
    QWidget* createMiddleList();
    // 右侧内容区
    QWidget* createRightContent();
    // 创建导航按钮
    QToolButton* createNavButton(const QString &text,const QString &icon);
    // 微信风格组件
    QListWidgetItem* createContactItem(const QString& name, const QString& msg,
                                     const QString& time, bool unread = false);

private slots:
    void sltMainPageChanged(int index);
    void sltOnContactClicked(QListWidgetItem *item);
    void sltChatMessage(const QString &message);

    void sltOnSearchTextChanged(const QString &text);
    void sltOnAddFriendClicked();
    void handleSplitterMoved(int pos, int index);

    // 状态，上线下线状态
    void sltTcpStatus(const quint8 &state);
    // 解析Socket的消息
    void sltTcpReply(const quint8 &type, const QJsonValue &dataVal);

private:
    // 添加好友后回应
    void parseAddFriendReply(const QJsonValue &dataVal);
    // 好友添加请求确认
    void parseAddFriendRequest(const QJsonValue &dataVal);
private:
    // 联系人列表
    ContactList *m_contactList;
    // 聊天窗口
    QStackedWidget *m_rightChatStack;
    QLabel *m_rightTitle;
    QTextEdit *m_chatArea;
    QSplitter  *m_splitter;

    // socket通信类
    ClientSocket    *m_tcpSocket;
    QSystemTrayIcon *systemTrayIcon;

    // 主动退出操作时不进行断线匹配
    bool            m_bQuit;
};
#endif //MAINWINDOW_H

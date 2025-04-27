//
// Created by utopia on 2025/4/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "../headers/mainwindow.h"
#include "../../Utility/headers/global.h"
#include "../../DataBase/headers/databasemgr.h"


MainWindow::MainWindow(QWidget *parent) :
    CustomMoveWidget(parent) {
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowTitle("服务端");
    setMinimumSize(680, 480);
    //setWindowIcon(QIcon(":/images/userHeader.png"));
    qDebug()<< "本机Ip："+myHelper::GetIP();
    initNetWork();
    initStyle();
    initUI();
    initConnection();

    QString name = "admin";
    QString passwd = "123456";
    //
    QJsonObject jsonObje = DataBaseMgr::Instance()->CheckUserLogin(name, passwd);
    int nId = jsonObje.value("id").toInt();
    int identity = jsonObje.value("identity").toInt();

    if (-1 == nId) {
        CMessageBox::Infomation(this, tr("提示"), tr("用户名或密码错误！"));
        return;
    }

    MyApplication::m_nId = nId;
    MyApplication::m_nIdentyfi = identity;
}

MainWindow::~MainWindow() {

}

void MainWindow::initUI() {
}

void MainWindow::initStyle() {
}

void MainWindow::initConnection() {
}

void MainWindow::initNetWork() {
    tcpMsgServer = new TcpMsgServer(this);
    qDebug() << "TCP Server Init";
    bool bOk = tcpMsgServer->StartListen(60100);
    if (bOk)
        qDebug() << "消息服务器监听成功,端口: 60100";
    else
        qDebug() << "消息服务器监听失败";
    connect(tcpMsgServer, &TcpMsgServer::signalUserStatus, this, &MainWindow::sltShowUserStatus);
}

void MainWindow::sltChangePages(int index) {
}

void MainWindow::sltShowUserStatus(const QString &status) {
    qDebug() << status;
}

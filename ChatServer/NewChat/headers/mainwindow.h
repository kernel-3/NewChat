//
// Created by utopia on 2025/4/26.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../CustomWidget/headers/customwidget.h"
#include "../../NetWork/headers/tcpserver.h"



class MainWindow : public CustomMoveWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void initUI();
    void initStyle();
    void initConnection();

    void initNetWork();

private slots:
    void sltChangePages(int index);
    void sltShowUserStatus(const QString &status);

private:
    // 服务配置
    TcpMsgServer *tcpMsgServer;
    TcpFileServer *tcpFileServer;
};


#endif //MAINWINDOW_H

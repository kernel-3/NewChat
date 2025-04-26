//
// Created by utopia on 2025/4/22.
//

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "../../CustomWidget/headers/rotatingstackedwidget.h"
#include "../../NetWork/headers/clientsocket.h"


class LoginDialog : public QWidget {
Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog() override;
signals:
    void signalRotate();
protected:
    void changeEvent(QEvent *) override;
    void paintEvent(QPaintEvent *event) override;
private slots:
    // 登录
    void onBtnLoginClicked();
    // 服务器信息返回处理
    void sltTcpStatus(const quint8 &state);
    void sltAnimationFinished();

private:
    void initUI();
    void initWindowDecorations();
    void initMainContent();
    void initBottomLinks();
    void initConnect();
private:
    bool m_bConnected;
    RotatingStackedWidget *m_rotatingStackedWidget;
    QVBoxLayout *m_mainLayout;
    QLabel *m_headerLabel;       // 圆形头像
    QWidget *m_headerWidget;
    QLineEdit *m_accountInput;   // 账号输入框
    QLineEdit *m_passwordInput;  // 密码输入框
    QPushButton *m_loginBtn;     // 登录按钮
    QCheckBox *m_recordPassword; // 记住密码
    QCheckBox *m_autoLoginCheck; // 自动登录
    QLabel *m_qrCodeLabel;       // 二维码区域
    QPoint m_dragPosition;       // 窗口拖动
    // socket通信
    ClientSocket *m_tcpSocket;
};

#endif //LOGINDIALOG_H

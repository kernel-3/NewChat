//
// Created by utopia on 2025/4/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginDialog.h" resolved

#include "logindialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QFormLayout>
#include <QDir>
#include <QPropertyAnimation>
#include <QJsonObject>
#include <QGraphicsDropShadowEffect>

#include "../Utility/myapp.h"
#include "../Utility/global.h"
#include "../Utility/unit.h"
#include "../CustomWidget/basewidget.h"



LoginDialog::LoginDialog(QWidget *parent) :
    QWidget(parent){
    setWindowTitle("登录界面");
    setWindowIcon(QIcon(":/images/logo.png"));
    setFixedSize(410, 386);
    initUI();
    initConnect();
    // socket通信
    m_tcpSocket = new ClientSocket();
    m_tcpSocket->connectToHost(MyApp::m_strHostAddr, MyApp::m_nMsgPort);
    connect(m_tcpSocket, SIGNAL(signalStatus(quint8)), this, SLOT(sltTcpStatus(quint8)));
}

LoginDialog::~LoginDialog() {

}

void LoginDialog::changeEvent(QEvent *event) {
    QWidget::changeEvent(event);
}

void LoginDialog::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
}

void LoginDialog::onBtnLoginClicked() {
   // m_headerWidget->setVisible(false);
    QPropertyAnimation *animation = new QPropertyAnimation(m_headerLabel, "pos");
    animation->setDuration(200);
    //animation->setStartValue(QPoint(40, 115));
    //animation->setEndValue(QPoint((this->width() - m_headerLabel->width()) / 2 - 20, 100));
    connect(animation, SIGNAL(finished()), this, SLOT(sltAnimationFinished()));
    animation->start();
}

void LoginDialog::sltTcpStatus(const quint8 &state) {
    switch (state) {
        case DisConnectedHost: {
            m_bConnected = false;
            //ui->labelWinTitle->setText(tr("服务器已断开"));
        }
        break;
        case ConnectedHost:{
            m_bConnected = true;
           // ui->labelWinTitle->setText(tr("已连接服务器"));
        }
        break;
        // 登陆验证成功
        case LoginSuccess:{
            disconnect(m_tcpSocket, SIGNAL(signalStatus(quint8)), this, SLOT(sltTcpStatus(quint8)));

            // 登录成功后，保存当前用户
            MyApp::m_strUserName = m_accountInput->text();
            MyApp::m_strPassword = m_passwordInput->text();
            MyApp::SaveConfig();

            // 显示主界面
            MainWindow *mainWindow = new MainWindow();
            if (!QFile::exists(MyApp::m_strHeadFile)) {
                GLobalHelper::Sleep(100);
                QJsonObject jsonObj;
                jsonObj.insert("from", MyApp::m_nId);
                jsonObj.insert("id",  -2);
                jsonObj.insert("msg", GLobalHelper::getFileNameWithExtension(MyApp::m_strHeadFile));
                m_tcpSocket->sltSendMessage(GetFile, jsonObj);
                GLobalHelper::Sleep(100);
            }

            // 居中显示
            GLobalHelper::formInCenter(mainWindow);
            mainWindow->setSocket(m_tcpSocket, MyApp::m_strUserName);
            mainWindow->show();
            this->close();
        }
        break;
        case LoginPasswdError:
            CMessageBox::Infomation(this, "登录失败，请检查用户名和密码！");
            break;
        case LoginRepeat:
            CMessageBox::Infomation(this, "登录失败，该账户已登录！");
            break;
        case RegisterOk:
            CMessageBox::Infomation(this, "该账号注册成功！请点击登录！");
            break;
        case RegisterFailed:
            CMessageBox::Infomation(this, "该账号已经注册！请点击登录！");
            break;
        default:
            break;
    }

    // 还原初始位置，重新登录
    // ui->widgetInput->setVisible(true);
    // ui->labelUserHead->move(40, 115);
}

void LoginDialog::sltAnimationFinished() {
    if (!m_bConnected) {
        m_tcpSocket->connectToHost(MyApp::m_strHostAddr, MyApp::m_nMsgPort);
        CMessageBox::Infomation(this, "未连接服务器，请等待！");
        //m_headerWidget->setVisible(true);
        //m_headerLabel->move(40, 115);
        return;
    }

    // // 构建 Json 对象
    QJsonObject json;
    json.insert("name", m_accountInput->text());
    json.insert("passwd", m_passwordInput->text());
    qDebug()<<json;
    m_tcpSocket->sltSendMessage(Login, json);
}

void LoginDialog::initUI() {
    // 主布局
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(20, 50, 20, 20);
    m_mainLayout->setSpacing(0);

    // 窗口装饰
    initWindowDecorations();
    // 主体内容
    initMainContent();
    // 底部链接
    initBottomLinks();
    // 添加阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 50));
    shadow->setOffset(0, 0);
    this->setGraphicsEffect(shadow);
}

void LoginDialog::initWindowDecorations() {
    // 关闭按钮
    QPushButton *closeBtn = new QPushButton(this);
    closeBtn->setFixedSize(24, 24);
    closeBtn->setIcon(QIcon(":/icons/close_white.svg"));
    closeBtn->setStyleSheet("background: transparent;");
    closeBtn->move(width()-40, 10);
    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);

    // 最小化按钮
    QPushButton *minBtn = new QPushButton(this);
    minBtn->setFixedSize(24, 24);
    minBtn->setIcon(QIcon(":/icons/minimize_white.svg"));
    minBtn->setStyleSheet("background: transparent;");
    minBtn->move(width()-70, 10);
    connect(minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
}

void LoginDialog::initMainContent() {
    QWidget *contentWidget = new QWidget;
    contentWidget->setObjectName("contentWidget");
    contentWidget->setStyleSheet(R"(
        #contentWidget {
            background: black;
            border-radius: 8px;
            padding: 20px;
        }
        QLineEdit {
            border: 1px solid #E0E0E0;
            border-radius: 4px;
            padding: 12px;
            font-size: 14px;
        }
        QLineEdit:focus {
            border-color: #07C160;
        }
        QPushButton#loginBtn {
            background: #07C160;
            color: white;
            border-radius: 4px;
            padding: 12px;
            font-size: 16px;
        }
        QPushButton#loginBtn:hover {
            background: #05AE51;
        }
    )");

    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);


    // 头像
    m_headerLabel = new QLabel;
    m_headerLabel->setFixedSize(80, 80);
    m_headerLabel->setPixmap(QPixmap(":/images/icons/default_avatar.png").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_headerLabel->setAlignment(Qt::AlignCenter);
    m_headerLabel->setStyleSheet("border-radius: 40px; border: 2px solid #E0E0E0;");
    contentLayout->setSpacing(10);
    contentLayout->addWidget(m_headerLabel, 0, Qt::AlignHCenter);

    QWidget *m_headerWidget = new QWidget;
    QVBoxLayout *vLayout = new QVBoxLayout(m_headerWidget);
    // 输入区域
    m_accountInput = new QLineEdit;
    m_accountInput->setPlaceholderText("微信号/手机号/QQ号");
    vLayout->addWidget(m_accountInput);

    m_passwordInput = new QLineEdit;
    m_passwordInput->setPlaceholderText("密码");
    m_passwordInput->setEchoMode(QLineEdit::Password);
    vLayout->addWidget(m_passwordInput);

    // 登录按钮
    m_loginBtn = new QPushButton("登录");
    m_loginBtn->setObjectName("loginBtn");
    vLayout->addWidget(m_loginBtn);

    QHBoxLayout *checkLayout = new QHBoxLayout();
    checkLayout->addStretch();
    // 记住密码
    m_recordPassword = new QCheckBox("记住密码");
    m_recordPassword->setStyleSheet("QCheckBox { color: #666; }");
    checkLayout->addWidget(m_recordPassword);
    //contentLayout->addWidget(recordPassword, 0, Qt::AlignRight);
    // 自动登录
    m_autoLoginCheck = new QCheckBox("自动登录");
    m_autoLoginCheck->setStyleSheet("QCheckBox { color: #666; }");
    checkLayout->addWidget(m_autoLoginCheck);
    vLayout->addLayout(checkLayout);

    contentLayout->addWidget(m_headerWidget);
    m_mainLayout->addWidget(contentWidget);
}

void LoginDialog::initBottomLinks() {
    QWidget *linkWidget = new QWidget;
    QHBoxLayout *linkLayout = new QHBoxLayout(linkWidget);
    linkLayout->setContentsMargins(0, 20, 0, 0);
    linkLayout->setSpacing(15);

    QPushButton *qrBtn = new QPushButton("二维码登录");
    QPushButton *forgetBtn = new QPushButton("找回密码");
    QPushButton *registerBtn = new QPushButton("注册账号");

    // 样式设置
    QString linkStyle = "QPushButton { color: #576B95; background: transparent; border: none; }";
    qrBtn->setStyleSheet(linkStyle);
    forgetBtn->setStyleSheet(linkStyle);
    registerBtn->setStyleSheet(linkStyle);

    linkLayout->addWidget(qrBtn);
    linkLayout->addWidget(forgetBtn);
    linkLayout->addWidget(registerBtn);

    m_mainLayout->addWidget(linkWidget, 0, Qt::AlignHCenter);
}

void LoginDialog::initConnect() {
    connect(m_loginBtn, &QPushButton::clicked, this, &LoginDialog::onBtnLoginClicked);
}

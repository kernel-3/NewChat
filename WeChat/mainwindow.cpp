//
// Created by utopia on 2025/4/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"

#include <QPushButton>
#include <QListWidget>
#include <QToolButton>
#include <QMenu>
#include <QLabel>
#include <QInputDialog>

#include "../Utility/global.h"
#include "../DataBase/databasemgr.h"
#include "../Utility/myapp.h"
#include "../Utility/unit.h"

MainWindow::MainWindow(QWidget *parent) :
    CustomMoveWidget(parent) {
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowTitle("聊天App");
    setMinimumSize(680, 480);
    setWindowIcon(QIcon(":/images/userHeader.png"));

    initStyle();
    initUI();
    initConnection();
    m_bQuit = false;
}

MainWindow::~MainWindow() {

}

void MainWindow::setSocket(ClientSocket *tcpSocket, const QString &ame) {
    if (NULL != tcpSocket) {
        m_tcpSocket = tcpSocket;

        connect(m_tcpSocket, &ClientSocket::signalMessage,this, &MainWindow::sltTcpReply);
        connect(m_tcpSocket, &ClientSocket::signalStatus,this, &MainWindow::sltTcpStatus);

        // 加载头像
        //ui->widgetHead->SetHeadPixmap(MyApp::m_strHeadFile);

        // 上线的时候获取当前好友的状态
        QJsonArray friendArr = DataBaseMgr::Instance()->getMyFriend(MyApp::m_nId);

        // 组织Jsonarror
        m_tcpSocket->sltSendMessage(GetMyFriends, friendArr);

        // 添加我的群组
        //AddMyGroups(DataBaseMagr::Instance()->GetMyGroup(MyApp::m_nId));
    }

    // if (name.isEmpty()) return;
    // ui->labelUser->setText(name);
}

void MainWindow::changeEvent(QEvent *event) {
    CustomMoveWidget::changeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *close_event) {
    CustomMoveWidget::closeEvent(close_event);
}

void MainWindow::showEvent(QShowEvent *show_event) {
    CustomMoveWidget::showEvent(show_event);
}

void MainWindow::initUI() {
    m_splitter = new QSplitter(Qt::Horizontal, this);

    // 左侧导航栏（固定宽度）
    QWidget *leftNav = createLeftNav();
    leftNav->setMinimumWidth(60);    // 最小宽度
    leftNav->setMaximumWidth(60);   // 最大可拉伸宽度
    m_splitter->addWidget(leftNav);

    // 中间联系人列表（弹性宽度）
    QWidget *middleList = createMiddleList();
    middleList->setMinimumWidth(240);
    middleList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_splitter->addWidget(middleList);

    // 右侧内容区（主弹性区域）
    QWidget *rightContent = createRightContent();
    rightContent->setMinimumWidth(480);
    rightContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_splitter->addWidget(rightContent);

    // 配置分割比例（左:中:右 = 1:2:5）
    QList<int> sizes;
    sizes << 60 << 240 << 480;  // 初始宽度分配
    m_splitter->setSizes(sizes);

    // 设置分割条样式
    m_splitter->setHandleWidth(2);
    m_splitter->setStyleSheet(R"(
        QSplitter::handle {
            background: #F0F0F0;
            border: 1px solid #E0E0E0;
        }
        QSplitter::handle:hover {
            background: #D0D0D0;
        }
    )");

    setCentralWidget(m_splitter);
    //resize(1000, 700);
}

void MainWindow::initStyle() {
    setStyleSheet(R"(
        QMainWindow {
            background: black;
        }
        QListWidget {
            border: none;
            background: black;
            outline: 0;
        }
        QListWidget::item {
            height: 64px;
            border-bottom: 1px solid #EBEBEB;
        }
        QListWidget::item:hover {
            background: #F5F5F5;
        }
        QListWidget::item:selected {
            background: #E6E6E6;
        }
        /* 微信标准蓝色 */
        QToolButton[selected="true"] {
            border-left: 3px solid #07C160;
        }
    )");
}

void MainWindow::initConnection() {
    connect(m_contactList, &QListWidget::itemClicked,
        this, &MainWindow::sltOnContactClicked);
    connect(m_splitter, &QSplitter::splitterMoved,
        this, &MainWindow::handleSplitterMoved);
}

QWidget * MainWindow::createLeftNav() {
    QWidget *navWidget = new QWidget;
    navWidget->setFixedWidth(70);
    QVBoxLayout *navLayout = new QVBoxLayout(navWidget);
    navLayout->setContentsMargins(5, 20, 5, 20);
    navLayout->setSpacing(10);      // 减小间距

    // 头像
    QLabel* m_headerLabel = new QLabel;
    m_headerLabel->setFixedSize(60, 60);
    m_headerLabel->setPixmap(QPixmap(":/images/icons/default_avatar.png").scaled(55, 55, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_headerLabel->setAlignment(Qt::AlignCenter);
    //m_headerLabel->setStyleSheet("border-radius: 40px; border: 2px solid #E0E0E0;");
    navLayout->addWidget(m_headerLabel, 0, Qt::AlignHCenter);

    // 统一使用/icons前缀的路径
    QStringList icons = {
           ":/images/icons/default_chat.png",         // 聊天
        ":/images/icons/default_contacts.png",     // 通讯录
        ":/images/icons/default_collect.png",      // 收藏
        ":/images/icons/default_files.png",        // 文件
        ":/images/icons/default_moments.png",      // 朋友圈
        ":/images/icons/default_miniprogram.png",  // 小程序
        ":/images/icons/default_phone.png",        // 手机
        ":/images/icons/default_settings.png"      // 设置
    };

    QStringList texts = {"聊天", "通讯录", "收藏", "文件", "朋友圈", "小程序", "手机", "设置"};

    for(int i=0; i<icons.size(); ++i){
        // 在第5个元素前添加拉伸（小程序前）
        if (i == 5) navLayout->addStretch(30);
        navLayout->addWidget(createNavButton(icons[i], texts[i]),0, Qt::AlignHCenter);
    }

    return navWidget;
}

QWidget * MainWindow::createMiddleList() {
    QWidget *midWidget = new QWidget;
    midWidget->setMinimumWidth(240);
    //midWidget->setStyleSheet("background: #F5F5F5");
    QVBoxLayout *layout = new QVBoxLayout(midWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    ContactHeaderWidget *header = new ContactHeaderWidget;
    connect(header, &ContactHeaderWidget::addButtonClicked, this, &MainWindow::sltOnAddFriendClicked);
    connect(header, &ContactHeaderWidget::searchTextChanged, this, &MainWindow::sltOnSearchTextChanged);
    layout->addWidget(header);

    // 联系人列表
    m_contactList = new ContactList;
    m_contactList->addContact(
        ":/images/icons/default_avatar.png",    // 头像路径
        "张三",                   // 联系人名称
        "晚上一起吃饭吗？",        // 最后一条消息
        "15:30",                 // 时间
        3,                       // 未读消息数
        true                     // 在线状态
    );

    m_contactList->addContact(
        ":/images/icons/default_avatar.png",
        "技术交流群",
        "小王：接口文档已更新",
        "上午10:00",
        0,
        false
    );

    // 设置列表尺寸
    m_contactList->setFixedWidth(240);
    layout->addWidget(m_contactList);
    return midWidget;
}

QWidget * MainWindow::createRightContent() {
    m_rightChatStack = new QStackedWidget;

    // 默认聊天界面
    QWidget *chatPage = new QWidget;
    QVBoxLayout *chatLayout = new QVBoxLayout(chatPage);

    // 标题栏
    m_rightTitle = new QLabel("请选择联系人");
    m_rightTitle->setStyleSheet("font-size: 18px; color: #333; padding: 10px;");

    // 聊天区域
    m_chatArea = new QTextEdit;
    m_chatArea->setStyleSheet(R"(
        QTextEdit {
            border: none;
            background: balck;
            padding: 15px;
            font-size: 14px;
        }
    )");

    // 输入框
    QLineEdit *inputBox = new QLineEdit;
    inputBox->setPlaceholderText("输入消息...");
    inputBox->setStyleSheet(R"(
        QLineEdit {
            border: 1px solid #E0E0E0;
            border-radius: 18px;
            padding: 8px 15px;
            margin: 10px;
        }
    )");

    chatLayout->addWidget(m_rightTitle);
    chatLayout->addWidget(m_chatArea, 1);
    chatLayout->addWidget(inputBox);

    m_rightChatStack->addWidget(chatPage);
    return m_rightChatStack;
}

QToolButton * MainWindow::createNavButton(const QString &iconPath, const QString &text) {
    QToolButton *btn = new QToolButton;

    // 加载并验证图标
    QIcon icon(iconPath);
    if(icon.isNull()) {
        qWarning() << "图标加载失败：" << iconPath;
        btn->setText(text + "(!)"); // 显示加载失败提示
    } else {
        btn->setIcon(icon);
    }

    // 尺寸设置优化
    btn->setIconSize(QSize(32, 32));
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setText(text);

    // 按钮尺寸策略
    btn->setFixedSize(20, 20);        // 固定按钮尺寸
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 样式优化
    btn->setStyleSheet(R"(
        QToolButton {
            border: none;
            padding: 0px 0;
            color: #666;
            font-size: 12px;
            qproperty-iconSize: 20px;
        }
        QToolButton:hover {
            background: #F0F0F0;
            border-radius: 8px;
        }
        QToolButton:pressed {
            background: #E0E0E0;
        }
    )");

    return btn;
}

QListWidgetItem * MainWindow::createContactItem(const QString &name, const QString &msg, const QString &time,
    bool unread) {
    QWidget *itemWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(itemWidget);

    // 头像
    QLabel *avatar = new QLabel;
    avatar->setPixmap(QPixmap(":/icons/default_avatar.png").scaled(48, 48));
    avatar->setStyleSheet("border-radius: 24px;");
    layout->addWidget(avatar);

    // 文本区域
    QWidget *textArea = new QWidget;
    QVBoxLayout *textLayout = new QVBoxLayout(textArea);

    QLabel *nameLabel = new QLabel(name);
    nameLabel->setStyleSheet("font-weight: 500; color: #333;");

    QLabel *msgLabel = new QLabel(msg);
    msgLabel->setStyleSheet("color: #666; font-size: 13px;");

    textLayout->addWidget(nameLabel);
    textLayout->addWidget(msgLabel);
    layout->addWidget(textArea);

    // 右侧区域
    QWidget *rightArea = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightArea);

    QLabel *timeLabel = new QLabel(time);
    timeLabel->setStyleSheet("color: #999; font-size: 12px;");
    rightLayout->addWidget(timeLabel);

    if(unread) {
        QLabel *unreadLabel = new QLabel("3");
        unreadLabel->setStyleSheet(R"(
            background: #FA5151;
            color: white;
            border-radius: 9px;
            min-width: 18px;
            max-width: 18px;
            padding: 0 2px;
            font-size: 12px;
        )");
        rightLayout->addWidget(unreadLabel);
    }
    layout->addWidget(rightArea);

    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(240, 64));
    m_contactList->addItem(item);
    m_contactList->setItemWidget(item, itemWidget);

    return item;
}

void MainWindow::sltMainPageChanged(int index) {
    // static int s_nIndex = 0;
    // if (index == s_nIndex) return;
    //
    // m_mainStackedWidget->setLength(m_mainStackedWidget->width(),
    //                                index > s_nIndex
    //                                ? AnimationStackedWidget::LeftToRight
    //                                : AnimationStackedWidget::RightToLeft);
    //
    // m_mainStackedWidget->start(index);
    // s_nIndex = index;
}

void MainWindow::sltChatMessage(const QString &message) {
}

void MainWindow::sltOnContactClicked(QListWidgetItem *item) {
    QString contactName = item->text();
    m_rightTitle->setText(contactName);
    m_chatArea->setText(QString("与 %1 的聊天记录：\n").arg(contactName));

    // 示例聊天记录
    m_chatArea->append("2023-08-01 10:00:00 你好！");
    m_chatArea->append("2023-08-01 10:01:00 今天有空吗？");
}

void MainWindow::sltOnSearchTextChanged(const QString &text) {

}

void MainWindow::sltOnAddFriendClicked() {
    QString text = CInputDialog::GetInputText(this, "zhangsan");
    if (!text.isEmpty()) {
        // 首先判断该用户是否已经是我的好友了
        if (DataBaseMgr::Instance()->isMyFriend(MyApp::m_nId, text)) {
            CMessageBox::Infomation(this, "该用户已经是你的好友了！");
            return;
        }

        // 构建 Json 对象
        QJsonObject json;
        json.insert("id", m_tcpSocket->getUserId());
        json.insert("name", text);
        m_tcpSocket->sltSendMessage(AddFriend, json);
    }
}

void MainWindow::handleSplitterMoved(int pos, int index) {
    QList<int> currentSizes = m_splitter->sizes();

    // 限制左面板宽度范围
    if(index == 0) {
        if(currentSizes[0] < 80) m_splitter->setSizes(QList<int>{80, currentSizes[1], currentSizes[2]});
        if(currentSizes[0] > 120) m_splitter->setSizes(QList<int>{120, currentSizes[1], currentSizes[2]});
    }

    // 限制中间列表最小宽度
    if(index == 1 && currentSizes[1] < 240) {
        m_splitter->setSizes(QList<int>{currentSizes[0], 240, currentSizes[2]});
    }
}

void MainWindow::sltTcpStatus(const quint8 &state) {
    switch (state)
    {
        case DisConnectedHost:
        {
            if (m_bQuit) return;
            QPixmap pixmap  = QPixmap(":/resource/background/app.png");
            //pixmap = GLobalHelper::changeGrayPixmap(pixmap.toImage());
            systemTrayIcon->setIcon(QIcon(pixmap));
            pixmap = QPixmap(MyApp::m_strHeadFile);
            //ui->widgetHead->SetHeadPixmap(myHelper::changeGrayPixmap(pixmap.toImage()));
            if (!this->isVisible()) this->show();
            CMessageBox::Infomation(this, tr("与服务器断开连接"));
        }
        break;
        case ConnectedHost:
        {
            QJsonObject json;
            json.insert("name", MyApp::m_strUserName);
            json.insert("passwd", MyApp::m_strPassword);

            m_tcpSocket->sltSendMessage(Login, json);
        }
        break;
        case LoginSuccess:
        {
            systemTrayIcon->setIcon(QIcon(":/resource/background/app.png"));
            //ui->widgetHead->SetHeadPixmap(QPixmap(MyApp::m_strHeadFile));
            if (!this->isVisible()) this->show();
            CMessageBox::Infomation(this, tr("重连成功！"));
        }
        break;
        default:
            break;
    }
}

void MainWindow::sltTcpReply(const quint8 &type, const QJsonValue &dataVal) {
    switch (type) {
        case UserOnLine:
            //UpdateFriendStatus(OnLine, dataVal);
            break;
        case UserOffLine:
            //UpdateFriendStatus(OffLine, dataVal);
            break;
        case UpdateHeadPic:
            // 你的好友更新了头像
           // ParseUpFriendHead(dataVal);
            break;
        case AddFriend:
            parseAddFriendReply(dataVal);
            break;
        case AddGroup:
            //ParseAddGroupReply(dataVal);
            break;
        case AddFriendRequist:
            parseAddFriendRequest(dataVal);
            break;
        case AddGroupRequist:
            //ParseAddGroupRequest(dataVal);
             break;
        case CreateGroup:
            //ParseCreateGroupReply(dataVal);
            break;
        case GetMyFriends:
            //ParseGetFriendsReply(dataVal);
            break;
        case GetMyGroups:
            //ParseGetGroupFriendsReply(dataVal);
            break;
        case RefreshFriends:
            //ParseRefreshFriendsReply(dataVal);
            break;
        case RefreshGroups:
            //ParseRefreshGroupFriendsReply(dataVal);
            break;
        case SendMsg:
            //ParseFriendMessageReply(dataVal);
            break;
        case SendGroupMsg:
            //ParseGroupMessageReply(dataVal);
            break;
        case SendFile:
            //ParseFriendMessageReply(dataVal);
            break;
        case SendPicture:
            //ParseFriendMessageReply(dataVal);
            break;
        default:
            break;
    }
}

void MainWindow::parseAddFriendReply(const QJsonValue &dataVal) {
    if (dataVal.isObject()) {
        QJsonObject dataObj = dataVal.toObject();

        int nStatus = dataObj.value("status").toInt();

        int nId = dataObj.value("id").toInt();
        // 未查询到该用户
        if (-1 == nId) {
            CMessageBox::Infomation(this, "未找到该用户!");
            return;
        }

        QString strHead = dataObj.value("head").toString();
        // 头像判断，如果不在就申请
        if (!QFile::exists(MyApp::m_strHeadPath + strHead)){
            QJsonObject jsonObj;
            jsonObj.insert("from", MyApp::m_nId);
            jsonObj.insert("id",  -2);
            jsonObj.insert("msg", strHead);
            m_tcpSocket->sltSendMessage(GetFile, jsonObj);

            GLobalHelper::Sleep(100);
        }

        // QQCell *cell = new QQCell;
        // cell->groupName = QString(tr("我的好友"));
        // cell->iconPath  = GetHeadPixmap(strHead);
        // cell->type      = QQCellType_Child;
        // cell->name      = dataObj.value("name").toString();
        // cell->subTitle  = QString("当前用户状态：%1 ").arg(OnLine == nStatus ? tr("在线") : tr("离线"));
        // cell->id        = nId;
        // cell->status    = nStatus;
        QString name = dataObj.value("name").toString();
        if(!name.isEmpty()) m_contactList->addItem(name);

        //ui->frindListWidget->insertQQCell(cell);

        // 更新至数据库
        //DataBaseMgr::Instance()->addFriend(cell->id, MyApp::m_nId, cell->name);
    }
}

void MainWindow::parseAddFriendRequest(const QJsonValue &dataVal) {
    if(dataVal.isObject()) {
        QJsonObject jsonObj = dataVal.toObject();
        int nId = jsonObj.value("id").toInt();
        QString name = jsonObj.value("name").toString();
        QString strMsg = jsonObj.value("msg").toString();

         //判断我是否已经添加该好友
         if (!DataBaseMgr::Instance()->isMyFriend(MyApp::m_nId, name)) {
             // QQCell *cell = new QQCell;
             // cell->groupName = QString(tr("我的好友"));
             // cell->iconPath  = MyApp::m_strHeadPath + jsonObj.value("head").toString();
             // cell->type      = QQCellType_Child;
             // cell->name     = name;
             // cell->subTitle  = QString("当前用户状态：在线 ");
             // cell->id        = nId;
             // cell->status    = OnLine;

             //ui->frindListWidget->insertQQCell(cell);
             // 更新至数据库
             //DataBaseMgr::Instance()->addFriend(cell->id, MyApp::m_nId, cell->name);
         }
        //播放系统提示音
        //GLobalHelper::PlaySound("system");
        // 询问
        CMessageBox::Question(this, tr("[%1] 请求加你为好友，是否接受？\n %2").arg(name).arg(strMsg));
    }
}

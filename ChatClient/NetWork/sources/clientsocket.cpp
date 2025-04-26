//
// Created by utopia on 2025/4/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ClientSocket.h" resolved

#include "clientsocket.h"

//#include <qicon.h>

#include "../../Utility/headers/myapp.h"
#include "../../Utility/headers/unit.h"
#include <QNetworkProxy>


ClientSocket::ClientSocket(QObject *parent) :
    QObject(parent) {

    m_nId = -1;

    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ClientSocket::sltReadyRead);
    connect(m_tcpSocket, &QTcpSocket::connected, this, &ClientSocket::sltConnected);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &ClientSocket::sltDisconnected);
    m_tcpSocket->setProxy(QNetworkProxy::NoProxy);
}

ClientSocket::~ClientSocket() {
    sltSendOffline();
}

int ClientSocket::getUserId() const {
    return m_nId;
}

void ClientSocket::setUserId(const int &id) {
    m_nId = id;
}

void ClientSocket::checkConnected() {
    if (m_tcpSocket->state() != QTcpSocket::ConnectedState) {
        m_tcpSocket->connectToHost(MyApp::m_strHostAddr,MyApp::m_nMsgPort);
    }
}

void ClientSocket::colseConnected() {
    if (m_tcpSocket->isOpen()) {
        m_tcpSocket->abort();
    }
}

void ClientSocket::connectToHost(const QString &host, const int &port) {
    if (m_tcpSocket->isOpen()) {
        m_tcpSocket->abort();
    }
    m_tcpSocket->connectToHost(host,port);
    qDebug() << "ip:"<<host<<"port:"<<port;
    // 测试
    if (m_tcpSocket->waitForConnected(3000)) {
        qDebug() << "connected";
    }else {
        qDebug() << "connect failed！"<<m_tcpSocket->errorString();
    }
}

void ClientSocket::sltSendMessage(const quint8 &type, const QJsonValue &dataVal) {
    // 连接服务器
    if (!m_tcpSocket->isOpen()) {
        m_tcpSocket->connectToHost(MyApp::m_strHostAddr,MyApp::m_nMsgPort);
        m_tcpSocket->waitForConnected(1000);
    }
    // 超时1s后还是连接不上，直接返回
    if (!m_tcpSocket->isOpen()) {return;}

    // 构建Json对象
    QJsonObject json = dataVal.toObject();
    json.insert("type", type);
    json.insert("from", m_nId);
    json.insert("data", dataVal);

    // 构建Json文档
    QJsonDocument jsonDoc = QJsonDocument(json);
    m_tcpSocket->write(jsonDoc.toJson(QJsonDocument::Compact));
}

void ClientSocket::sltSendOnline() {
}

void ClientSocket::sltSendOffline() {
}

void ClientSocket::sltDisconnected() {
    qDebug() << "has disconnected";
    m_tcpSocket->abort();
    emit signalStatus(DisConnectedHost);
}

void ClientSocket::sltConnected() {
    qDebug() << "has connected";
    emit signalStatus(ConnectedHost);
}

void ClientSocket::sltReadyRead() {
    // 读取socket数据
    QByteArray byRead = m_tcpSocket->readAll();
    QJsonParseError jsonError;
    // 转化为Json文档
    QJsonDocument document = QJsonDocument::fromJson(byRead, &jsonError);
    // 解析
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        // 转化Json文档为对象
        if (document.isObject()) {
            QJsonObject obj = document.object();
            QJsonValue value = obj.value("data");

            int nType = obj.value("type").toInt();
            // 根据消息类型解析服务器消息
            switch (nType) {
                case Register:
                    parseReister(value);
                    break;
                case Login:
                    parseLogin(value);
                    break;
                case UserOnLine:
                    emit signalMessage(UserOnLine,value);
                    break;
                case UserOffLine:
                    emit signalMessage(UserOffLine,value);
                    break;
                case Logout:
                    m_tcpSocket->abort();
                    break;
                case UpdateHeadPic:
                    emit signalMessage(UpdateHeadPic,value);
                    break;
                case AddFriend:
                    emit signalMessage(AddFriend,value);
                    break;
                case AddGroup:
                    emit signalMessage(AddGroup,value);
                    break;
                case AddFriendRequist:
                    Q_EMIT signalMessage(AddFriendRequist, value);
                    break;
                case AddGroupRequist:
                    Q_EMIT signalMessage(AddGroupRequist, value);
                    break;
                case CreateGroup:
                    Q_EMIT signalMessage(CreateGroup, value);
                    break;
                case GetMyFriends:
                    Q_EMIT signalMessage(GetMyFriends, value);
                    break;
                case GetMyGroups:
                    Q_EMIT signalMessage(GetMyGroups, value);
                    break;
                case RefreshFriends:
                    Q_EMIT signalMessage(RefreshFriends, value);
                    break;
                case RefreshGroups:
                    Q_EMIT signalMessage(RefreshGroups, value);
                    break;
                case SendMsg:
                    Q_EMIT signalMessage(SendMsg, value);
                    break;
                case SendGroupMsg:
                    Q_EMIT signalMessage(SendGroupMsg, value);
                    break;
                case SendFile:
                    Q_EMIT signalMessage(SendFile, value);
                    break;
                case SendPicture:
                    Q_EMIT signalMessage(SendPicture, value);
                    break;
                default:
                    break;
            }
        }
    }
}

void ClientSocket::parseLogin(const QJsonValue &dataVal) {
    if (dataVal.isObject()) {
        QJsonObject obj = dataVal.toObject();
        int code = obj.value("code").toInt();
        QString msg = obj.value("msg").toString();
        QString head = obj.value("head").toString();

        if (0 == code && msg == "ok") {
            m_nId = obj.value("id").toInt();
            // 保存头像
            MyApp::m_strHeadFile = MyApp::m_strHeadFile + head;
            MyApp::m_nId = m_nId;
            emit signalStatus(LoginSuccess);
        }else if (-1 == code) {
            emit signalStatus(LoginPasswdError);
        }else if (-2 == code) {
            emit signalStatus(LoginRepeat);
        }
    }
}

void ClientSocket::parseReister(const QJsonValue &dataVal) {
    if (dataVal.isObject()) {
        QJsonObject obj = dataVal.toObject();
        m_nId = obj.value("id").toInt();
        if (-1 != m_nId) {
            emit signalStatus(RegisterOk);
        }else {
            emit signalStatus(RegisterFailed);
        }
    }
}

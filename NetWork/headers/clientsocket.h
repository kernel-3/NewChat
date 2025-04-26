//
// Created by utopia on 2025/4/22.
//

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>


class ClientSocket : public QObject {
Q_OBJECT

public:
    explicit ClientSocket(QObject *parent = nullptr);
    ~ClientSocket() override;
    // 获取当前用户的ID
    int getUserId() const;
    void setUserId(const int &id);

    void checkConnected();
    void colseConnected();

    // 连接服务器
    void connectToHost(const QString &host, const int &port);
    void connectToHost(const QHostAddress &host, const int &port);
signals:
    void signalMessage(const quint8 &type, const QJsonValue &dataVal);
    void signalStatus(const quint8 &state);
public slots:
    // socket消息发送封装
    void sltSendMessage(const quint8 &type, const QJsonValue &dataVal);
    // 发送上线通知
    void sltSendOnline();
    // 发送下线通知
    void sltSendOffline();
private:
    // tcpsocket
    QTcpSocket *m_tcpSocket;
    int m_nId;
private slots:
    // 与服务器断开链接
    void sltDisconnected();
    // 链接上服务器
    void sltConnected();
    // tcp消息处理
    void sltReadyRead();

private:
    // 解析登陆返回信息
    void parseLogin(const QJsonValue &dataVal);
    // 解析注册返回信息
    void parseReister(const QJsonValue &dataVal);
};


#endif //CLIENTSOCKET_H

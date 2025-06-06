//
// Created by utopia on 2025/4/26.
//

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QVector>

#include "clientsocket.h"


// 服务器管理类
class TcpServer : public QObject {
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    ~TcpServer();

    bool StartListen(int port = 6666);
    void CloseListen();

signals:
    void signalUserStatus(const QString &text);

protected slots:
    // 继承虚函数
    virtual void SltNewConnection() = 0;
    virtual void SltConnected() = 0;
    virtual void SltDisConnected() = 0;

protected:
    QTcpServer *m_tcpServer;
};

// 消息服务器
class TcpMsgServer : public TcpServer
{
    Q_OBJECT
public:
    explicit TcpMsgServer(QObject *parent = 0);
    ~TcpMsgServer();

signals:
    void signalDownloadFile(const QJsonValue &json);

public slots:
    void SltTransFileToClient(const int &userId, const QJsonValue &json);

private slots:
    void SltNewConnection();
    void SltConnected();
    void SltDisConnected();
    void SltMsgToClient(const quint8 &type, const int &id, const QJsonValue &json);

private:
    // 客户端管理
    QVector < ClientSocket * > m_clients;
};


// 文件服务器
class TcpFileServer : public TcpServer {
    Q_OBJECT
public :
    explicit TcpFileServer(QObject *parent = 0);
    ~TcpFileServer();
signals:

    void signalRecvFinished(int id, const QJsonValue &json);

private slots:
    void SltNewConnection();
    void SltConnected();
    void SltDisConnected();
    void SltClientDownloadFile(const QJsonValue &json);
private:
    // 客户端管理
    QVector < ClientFileSocket * > m_clients;
};

#endif //TCPSERVER_H

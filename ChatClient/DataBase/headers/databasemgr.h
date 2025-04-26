//
// Created by utopia on 2025/4/24.
//

#ifndef DATABASEMGR_H
#define DATABASEMGR_H

#include <QObject>
#include <QVector>
#include <QJsonArray>
#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>

class ItemInfo;

class DataBaseMgr : public QObject {
Q_OBJECT

public:
    static DataBaseMgr * Instance() {
        if (m_instance == nullptr) {
            if (m_instance == nullptr) {
                m_instance = new DataBaseMgr();
            }
        }
        return m_instance;
    }
    // 打开用户数据库
    bool openUserDb(const QString &dataName);
    // 打开消息记录数据库
    bool openMessageDb(const QString &dataName);
    // 添加历史聊天记录
    void addHistoryMsg(const int &userId, ItemInfo *itemInfo);
    // 添加好友，保存至数据库
    void addFriend(const int &id, const int &userId, const QString &name);
    // 添加群组
    void addGroup(const int &id, const int &userId, const QString &name);
    // 删除好友
    bool deleteMyFriend(const int &id, const int &userId);
    // 获取我的好友
    QJsonArray getMyFriend(const int &userId) const;
    // 获取我的群组
    QJsonArray getMyGroup(const int &userId) const;
    // 判断改好友是否已经是我的好友了
    bool isMyFriend(const int &userId, const QString &name);
    // 判断是否已经加入该群组了
    bool isInGroup(const QString &name);
    // 获取历史聊天记录
    QVector<ItemInfo *> queryHistory(const int &id, const int &count = 0);

    // 测试使用，打印数据库中的所有信息
    void queryAll();

private:
    explicit DataBaseMgr(QObject *parent = nullptr);
    ~DataBaseMgr() override;

private:
    static DataBaseMgr *m_instance;

    // 数据库管理
    QSqlDatabase userdb;
    QSqlDatabase msgdb;
};


#endif //DATABASEMGR_H

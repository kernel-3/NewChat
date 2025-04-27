//
// Created by utopia on 2025/4/26.
//

#ifndef DATABASEMGR_H
#define DATABASEMGR_H

#include <QObject>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>

class DataBaseMgr : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseMgr(QObject *parent = 0);
    ~DataBaseMgr();

    bool OpenDb(const QString &dataName);
    void CloseDb();

    static DataBaseMgr *Instance(){
        static QMutex mutex;
        if (NULL == self) {
            QMutexLocker locker(&mutex);
            if (!self) {
                self = new DataBaseMgr();
            }
        }
        return self;
    }

    // 更新用户状态/上下线
    void UpdateUserStatus(const int &id, const quint8 &status);
    void UpdateUserHead(const int &id, const QString &strHead);

    void TestHeadPic(const int &id, const QString &name, const QString &strHead);

    // 获取用户状态
    QJsonArray GetAllUsers();
    QJsonObject GetUserStatus(const int &id) const;
    int GetUserLineStatus(const int &id) const;

    // 用户校验
    QJsonObject CheckUserLogin(const QString &name, const QString &passwd);
    // 注册用户
    int RegisterUser(const QString &name, const QString &passwd);

    // 添加好友
    QJsonObject AddFriend(const QString &name);

    // 添加群组
    QJsonObject AddGroup(const int &userId, const QString &name);
    // 创建群组
    QJsonObject CreateGroup(const int &userId, const QString &name);
    // 查询当前群组下面的好友
    QJsonArray  GetGroupUsers(const int &groupId);

    // 服务器启动的时候更新下所以人员的状态，可以不要
    void ChangeAllUserStatus();

    // 查询当前id的名字
    QString GetUserName(const int &id) const;
    QString GetUserHead(const int &id) const;
    QJsonObject GetUserInfo(const int &id) const;
private:
    void QueryAll();

 private:
    static DataBaseMgr *self;
    QSqlDatabase userdb;
};

#endif //DATABASEMGR_H

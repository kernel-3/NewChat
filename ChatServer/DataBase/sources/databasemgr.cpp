//
// Created by utopia on 2025/4/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DataBase.h" resolved

#include "../headers/databasemgr.h"
#include "../../Utility/headers/unit.h"

#include <QDebug>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#define DATE_TME_FORMAT     QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")

DataBaseMgr *DataBaseMgr::self = NULL;

DataBaseMgr::DataBaseMgr(QObject *parent) :
    QObject(parent){

}

DataBaseMgr::~DataBaseMgr(){
    if (userdb.isOpen()) {
        userdb.close();
    }
}

/**
 * @brief DataBaseMgr::OpenDb
 * 打开数据库
 */
bool DataBaseMgr::OpenDb(const QString &dataName){
    userdb = QSqlDatabase::addDatabase("QSQLITE");
    userdb.setDatabaseName(dataName);
    if (!userdb.open()) {
        qDebug() << "Open sql failed";
        return false;
    }

    // 添加数据表
    QSqlQuery query;
    query.exec("CREATE TABLE USERINFO (id INT PRIMARY KEY, name varchar(20), "
               "passwd varchar(20), head varchar(20), status INT, groupId INT, lasttime DATETIME);");

    query.exec("CREATE TABLE GROUPINFO (id INT PRIMARY KEY, groupId INT, name varchar(20), head varchar(20), "
               "userId INT, identity INT)");

    query.exec("CREATE TABLE USERHEAD (id INT PRIMARY KEY, name varchar(20), data varchar(20))");

    query.exec("INSERT INTO USERINFO VALUES(1, 'admin', '123456', '2.bmp', 0, 1, '');");

    // 更新状态,避免有些客户端异常退出没有更新下线状态
    ChangeAllUserStatus();
    QueryAll();
    return true;
}

/**
 * @brief DataBaseMgr::CloseDb
 * 关闭数据库
 */
void DataBaseMgr::CloseDb(){
    userdb.close();
}

/**
 * @brief DataBaseMgr::UpdateUserStatus
 * 更新当前id的用户状态
 * @param id
 * @param status
 * @return
 */
void DataBaseMgr::UpdateUserStatus(const int &id, const quint8 &status){
    // 组织sql语句
    QString strSql = "UPDATE USERINFO SET status=";
    strSql += QString::number(status);
    strSql += QString(",lasttime='");
    strSql += DATE_TME_FORMAT;
    strSql += QString("' WHERE id=");
    strSql += QString::number(id);

    // 执行数据库操作
    QSqlQuery query(strSql);
    query.exec();
}

/**
 * @brief DataBaseMgr::UpdateUserHead
 * 更新头像文件
 * @param id
 * @param strHead
 */
void DataBaseMgr::UpdateUserHead(const int &id, const QString &strHead){
    // 组织sql语句
    QString strSql = "UPDATE USERINFO SET head='";
    strSql += strHead;
    strSql += QString("' WHERE id=");
    strSql += QString::number(id);

    // 执行数据库操作
    QSqlQuery query(strSql);
    bool bOk = query.exec();
    qDebug() << "update head" << bOk << id;
}

/**
 * @brief DataBaseMgr::TestHeadPic
 * @param id
 * @param strHead
 */
void DataBaseMgr::TestHeadPic(const int &id, const QString &name, const QString &strHead){
    // 根据新ID重新创建用户
    QSqlQuery query;
    query.prepare("INSERT INTO USERHEAD (id, name, data) VALUES (?, ?, ?);");
    query.bindValue(0, id);
    query.bindValue(1, name);
    query.bindValue(2, strHead);

    bool bOk = query.exec();
    qDebug() << "ok" << bOk;
    QueryAll();
}

/**
 * @brief DataBaseMgr::GetAllUsers
 * @return
 */
QJsonArray DataBaseMgr::GetAllUsers(){
    QSqlQuery query("SELECT * FROM USERINFO ORDER BY id;");
    QJsonArray jsonArr;

    while (query.next()) {
        QJsonObject jsonObj;
        jsonObj.insert("id", query.value("id").toInt());
        jsonObj.insert("name", query.value("name").toString());
        jsonObj.insert("passwd", query.value("passwd").toString());
        jsonObj.insert("head", query.value("head").toString());
        jsonObj.insert("status", query.value("status").toInt());
        jsonObj.insert("groupId", query.value("groupId").toInt());
        jsonObj.insert("lasttime", query.value("lasttime").toString());
        jsonArr.append(jsonObj);
    }

    return jsonArr;
}

/**
 * @brief DataBaseMgr::GetUserStatus
 * 获取当前id的用户状态
 * @return
 */
QJsonObject DataBaseMgr::GetUserStatus(const int &id) const{
    QJsonObject jsonObj;
    QString strQuery = "SELECT [name],[status],[head] FROM USERINFO ";
    strQuery.append("WHERE id=");
    strQuery.append(QString::number(id));

    int nStatus = 0;
    QString strName = "";
    QString strHead = "0.bmp";

    QSqlQuery query(strQuery);
    if (query.next()) {
        strName = query.value(0).toString();
        nStatus = query.value(1).toInt();
        strHead = query.value(2).toString();
    }

    // 组合数据
    jsonObj.insert("id", id);
    jsonObj.insert("name", strName);
    jsonObj.insert("head", strHead);
    jsonObj.insert("status", nStatus);

    return jsonObj;
}

/**
 * @brief DataBaseMgr::GetUserLineStatus
 * 获取当前用户的在线状态
 * @param id
 * @return
 */
int DataBaseMgr::GetUserLineStatus(const int &id) const{
    QString strQuery = "SELECT [status] FROM USERINFO ";
    strQuery.append("WHERE id=");
    strQuery.append(QString::number(id));

    QSqlQuery query(strQuery);
    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}

/**
 * @brief DataBaseMgr::CheckUserLogin
 * 登录校验
 * @param name
 * @param passwd
 * @return id
 */
QJsonObject DataBaseMgr::CheckUserLogin(const QString &name, const QString &passwd){
    QString strQuery = "SELECT [id],[head],[status] FROM USERINFO ";
    strQuery.append("WHERE name='");
    strQuery.append(name);
    strQuery.append("' AND passwd='");
    strQuery.append(passwd);
    strQuery.append("';");

    QJsonObject jsonObj;
    int nId = -1;
    int code = -1;
    QString strHead = "0.bmp";

    QSqlQuery query(strQuery);
    if (query.next()) {
        nId = query.value("id").toInt();
        int nStatus = query.value("status").toInt();
        if (OnLine == nStatus)
        {
            nId = -2;
            code = -2;
        }
        else
        {
            // 更新在线信息
            UpdateUserStatus(nId, OnLine);
            code = 0;
        }
        strHead = query.value("head").toString();
    }

    // 组织返回
    jsonObj.insert("id", nId);
    jsonObj.insert("msg", nId < 0 ? "error" : "ok");
    jsonObj.insert("head", strHead);
    jsonObj.insert("code", code);

    return jsonObj;
}

/**
 * @brief DataBaseMgr::RegisterUser
 * 用户注册
 * @param name
 * @param passwd
 * @return
 */
int DataBaseMgr::RegisterUser(const QString &name, const QString &passwd){
    QString strQuery = "SELECT [id] FROM USERINFO ";
    strQuery.append("WHERE name='");
    strQuery.append(name);
    strQuery.append("';");

    QSqlQuery query(strQuery);
    if (query.next()) {
        // 查询到有该用户，提示注册失败，并返回id号
        return -1;
    }

    // 查询数据库
    query = QSqlQuery("SELECT [id] FROM USERINFO ORDER BY id DESC;");
    int nId = 1;
    // 查询最高ID
    if (query.next()) {
        nId = query.value("id").toInt();
    }

    // 根据新ID重新创建用户
    query.prepare("INSERT INTO USERINFO (id, name, passwd, head, status, groupId, lasttime) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?);");
    query.bindValue(0, nId + 1);
    query.bindValue(1, name);
    query.bindValue(2, passwd);
    query.bindValue(3, "0.bmp");
    query.bindValue(4, 0);
    query.bindValue(5, 0);
    query.bindValue(6, DATE_TME_FORMAT);

    query.exec();

    return nId + 1;
}

/**
 * @brief DataBaseMgr::AddFriend
 * 添加好友
 * @param name
 * @return
 */
QJsonObject DataBaseMgr::AddFriend(const QString &name){
    QString strQuery = "SELECT [id],[status],[head] FROM USERINFO ";
    strQuery.append("WHERE name='");
    strQuery.append(name);
    strQuery.append("';");

    int nId = -1;
    int nStatus = -1;
    QString strHead = "0.bmp";
    QSqlQuery query(strQuery);
    // 查询到有该用户
    if (query.next()) {
        nId     = query.value("id").toInt();
        nStatus = query.value("status").toInt();
        strHead = query.value("head").toString();
    }

    // 构建 Json 对象
    QJsonObject json;
    json.insert("id",  nId);
    json.insert("name", name);
    json.insert("head", strHead);
    json.insert("status", nStatus);

    return json;
}

/**
 * @brief DataBaseMgr::AddGroup
 * 加入群
 * @param id
 * @param name
 * @return
 */
QJsonObject DataBaseMgr::AddGroup(const int &userId, const QString &name){
#if 0
    QString strQuery = "SELECT [groupId] FROM GROUPINFO ";
    strQuery.append("WHERE name='");
    strQuery.append(name);
    strQuery.append("' AND userId=");
    strQuery.append(QString::number(userId));

    int nGroupId = -1;
    QString strHead = "1.bmp";

    QSqlQuery query(strQuery);

    // 查询到有该用户组
    if (query.next()) {
        nGroupId = query.value(0).toInt();
        strHead  = query.value(1).toString();
    }
    else {
        // 查询数据库
        query = QSqlQuery("SELECT [id] FROM GROUPINFO ORDER BY id DESC;");
        int nIndex = 0;
        // 查询最高ID
        if (query.next()) {
            nIndex = query.value(0).toInt();
        }

        nIndex   += 1;

        // 查询当前组是否存在
        strQuery = QString("SELECT [groupId] FROM GROUPINFO WHERE name='");
        strQuery.append(name);
        strQuery.append("'");

        query = QSqlQuery(strQuery);
        // 查询最高ID
        if (query.next()) {
            nGroupId = query.value(0).toInt();
            // 根据新ID重新创建用户
            query.prepare("INSERT INTO GROUPINFO (id, groupId, name, userId, identity) "
                          "VALUES (?, ?, ?, ?, ?);");
            query.bindValue(0, nIndex);
            query.bindValue(1, nGroupId);
            query.bindValue(2, name);
            query.bindValue(3, userId);
            query.bindValue(4, 1);
            // 执行插入
            query.exec();
        }
    }
#else
    // 先查询是否有该群组
    QString strQuery = "SELECT [groupId] FROM GROUPINFO ";
    strQuery.append("WHERE name='");
    strQuery.append(name);
    strQuery.append("';");

    int nGroupId = -1;
    int nCode    = -1;
    QString strHead = "5.bmp";

    QSqlQuery query(strQuery);

    // 查询到有该用户组
    if (query.next()){
        // 查询到有该群组，再判断该用户是否已经加入该群组
        nGroupId = query.value(0).toInt();
        strQuery = QString("SELECT [userId] FROM GROUPINFO WHERE groupId=");
        strQuery.append(QString::number(nGroupId));
        strQuery.append("");

        query = QSqlQuery(strQuery);
        // 查询到已经添加到该群组
        if (query.next()) {
            nCode = -2;
        }
        else{
            // 查询数据库
            query = QSqlQuery("SELECT [id] FROM GROUPINFO ORDER BY id DESC;");
            int nIndex = 0;
            // 查询最高ID
            if (query.next()) {
                nIndex = query.value(0).toInt();
            }

            nIndex   += 1;

            // 根据新ID重新创建用户
            query.prepare("INSERT INTO GROUPINFO (id, groupId, name, userId, identity) "
                          "VALUES (?, ?, ?, ?, ?);");
            query.bindValue(0, nIndex);
            query.bindValue(1, nGroupId);
            query.bindValue(2, name);
            query.bindValue(3, userId);
            query.bindValue(4, 3);
            // 执行插入
            query.exec();
        }
    }
#endif
    // 构建 Json 对象
    QJsonObject json;
    json.insert("id",  nGroupId);
    json.insert("name", name);
    json.insert("head", strHead);
    json.insert("code", nCode);

    QueryAll();

    return json;
}

/**
 * @brief DataBaseMgr::CreateGroup
 * 创建群
 * @param id
 * @param name
 * @return
 */
QJsonObject DataBaseMgr::CreateGroup(const int &userId, const QString &name){
    //查询群组是否存在
    QString strQuery = "SELECT [id],[groupId],[head] FROM GROUPINFO ";
    strQuery.append("WHERE name='");
    strQuery.append(name);
    strQuery.append("' AND userId=");
    strQuery.append(QString::number(userId));

    int nIndex = -1;
    int nGroupId = -1;
    QString strHead = "1.bmp";

    QSqlQuery query(strQuery);
    // 查询用户是否在群组中
    if (query.next()) {
        nIndex   = query.value("id").toInt();
        nGroupId = query.value("groupId").toInt();
        strHead  = query.value("head").toString();
    }
    else {
        //GROUPINFO
        //1.
        //2.
        // 查询数据库
        query = QSqlQuery("SELECT [id] FROM GROUPINFO ORDER BY id DESC;");
        nIndex = 0;
        // 查询最高ID
        if (query.next()) {
            nIndex = query.value("id").toInt();
        }

        // 再查询该ID下面的群组
        nGroupId = 0;
        strQuery = QString("SELECT [groupId] FROM GROUPINFO WHERE userId=");
        strQuery.append(QString::number(userId));
        strQuery.append(" ORDER BY groupId DESC");
        query = QSqlQuery(strQuery);
        // 查询最高ID
        if (query.next()) {
            nGroupId = query.value("groupId").toInt();
        }

        nIndex   += 1;
        nGroupId += 1;

        // 根据新ID重新创建用户
        query.prepare("INSERT INTO GROUPINFO (id, groupId, name, head, userId, identity) "
                      "VALUES (?, ?, ?, ?, ?, ?);");
        query.bindValue(0, nIndex);
        query.bindValue(1, nGroupId);
        query.bindValue(2, name);
        query.bindValue(3, "1.bmp");
        query.bindValue(4, userId);
        query.bindValue(5, 1);

        query.exec();
    }

    // 构建 Json 对象
    QJsonObject json;
    json.insert("id",  nGroupId);
    json.insert("name", name);
    json.insert("head", strHead);

    return json;
}

/**
 * @brief DataBaseMgr::GetGroupUsers
 * 获取该群组下面的所所有用户
 * @param groupId
 * @return
 */
QJsonArray DataBaseMgr::GetGroupUsers(const int &groupId){
    QString strQuery = ("SELECT [id],[name] FROM USERINFO WHERE ");
    strQuery.append(" id=(SELECT [id] FROM GROUPINFO WHERE groupId=");
    strQuery.append(QString::number(groupId));
    strQuery.append(") AND status=");
    strQuery.append(QString::number(OffLine));

    strQuery = "SELECT [userId] FROM GROUPINFO WHERE groupId=";
    strQuery.append(QString::number(groupId));

    QJsonArray jsonArr;
    QSqlQuery query(strQuery);
    jsonArr.append(groupId);
    // 查询
    while (query.next()) {
        int nId = query.value(0).toInt();
        strQuery = "SELECT [name],[head],[status] FROM USERINFO WHERE id=";
        strQuery.append(QString::number(nId));

        QSqlQuery queryUser(strQuery);
        if (queryUser.next()) {
            QJsonObject jsonObj;
            jsonObj.insert("id", nId);
            jsonObj.insert("name", queryUser.value(0).toString());
            jsonObj.insert("head", queryUser.value(1).toString());
            jsonObj.insert("status", queryUser.value(2).toInt());
            jsonArr.append(jsonObj);
        }
    }

    return jsonArr;
}

/**
 * @brief DataBaseMgr::ChangeAllUserStatus
 */
void DataBaseMgr::ChangeAllUserStatus(){
    QSqlQuery query("SELECT * FROM USERINFO ORDER BY id;");
    while (query.next()) {
        // 更新为下线状态
        UpdateUserStatus(query.value(0).toInt(), OffLine);
    }
}

/**
 * @brief DataBaseMgr::GetUserName
 * 根据id获取用户名
 * @param id
 * @return
 */
QString DataBaseMgr::GetUserName(const int &id) const{
    QString strQuery = "SELECT [name] FROM USERINFO ";
    strQuery.append("WHERE id=");
    strQuery.append(QString::number(id));

    QSqlQuery query(strQuery);
    if (query.next()) {
        return query.value(0).toString();
    }

    return "";
}

/**
 * @brief DataBaseMgr::GetUserHead
 * 获取用户头像
 * @param id
 * @return
 */
QString DataBaseMgr::GetUserHead(const int &id) const{
    QString strQuery = "SELECT [head] FROM USERINFO ";
    strQuery.append("WHERE id=");
    strQuery.append(QString::number(id));

    QSqlQuery query(strQuery);
    if (query.next()) {
        return query.value(0).toString();
    }

    return "1.bmp";
}

/**
 * @brief DataBaseMgr::GetUserInfo
 * 查询用户的信息
 * @param id
 * @return
 */
QJsonObject DataBaseMgr::GetUserInfo(const int &id) const{
    QString strQuery = "SELECT * FROM USERINFO ";
    strQuery.append("WHERE id=");
    strQuery.append(QString::number(id));

    QJsonObject jsonObj;
    int nCode = -1;
    // 查询数据库
    QSqlQuery query(strQuery);
    // 构建用户的所有信息,不包括密码
    if (query.next()) {
        jsonObj.insert("id", query.value("id").toInt());
        jsonObj.insert("name", query.value("name").toString());
        jsonObj.insert("head", query.value("head").toString());
        jsonObj.insert("status", query.value("status").toInt());
        jsonObj.insert("groupId", query.value("status").toInt());
        jsonObj.insert("lasttime", query.value("lasttime").toString());
        // 结果代码
        nCode = 0;
    }

    jsonObj.insert("code", nCode);

    return jsonObj;
}

void DataBaseMgr::QueryAll(){
    QSqlQuery query("SELECT * FROM USERINFO ORDER BY id;");
    qDebug() << "query users";
    while (query.next()) {
        qDebug() << query.value(0).toInt() << query.value(1).toString()
                 << query.value(2).toString() << query.value(3).toString()
                 << query.value(4).toString() << query.value(5).toString();
    }
    qDebug() << "query group";
    query = QSqlQuery("SELECT * FROM GROUPINFO ORDER BY id;");
    while (query.next()) {
        qDebug() << query.value(0).toInt() << query.value(1).toInt()
                 << query.value(2).toString() << query.value(3).toString()
                 << query.value(4).toInt() << query.value(5).toInt();
    }

    query = QSqlQuery("SELECT * FROM USERHEAD ORDER BY id;");
    while (query.next()) {
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString() << query.value(2).toString().length()
                 << query.value(2).toString().length();
    }

}

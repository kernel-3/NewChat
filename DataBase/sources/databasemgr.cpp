//
// Created by utopia on 2025/4/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DataBaseMgr.h" resolved

#include "databasemgr.h"
#include <QDebug>

DataBaseMgr *DataBaseMgr::m_instance = nullptr;

bool DataBaseMgr::openUserDb(const QString &dataName) {
    userdb = QSqlDatabase::addDatabase("QSQLITE", "connectionUser");
    userdb.setDatabaseName(dataName);
    if (!userdb.open()) {
        qDebug() << "Open sql failed";
        return false;
    }

    // 添加数据表
    QSqlQuery query(userdb);

    // 创建我的好友表 id为好友id，userid为当前用户id
    query.exec("CREATE TABLE FRIEND (id INT, userId INT, name varchar(50))");

    // 创建群组表 id为群组id，userid为当前用户id
    query.exec("CREATE TABLE MYGROUP (id INT, userId INT, name varchar(50))");

    // 用户数据保存
    query.exec("CREATE TABLE USERINFO (id INT, name varchar(50), passwd varchar(50))");

    return true;
}

bool DataBaseMgr::openMessageDb(const QString &dataName) {
    msgdb = QSqlDatabase::addDatabase("QSQLITE", "connectionMsg");
    msgdb.setDatabaseName(dataName);
    if (!msgdb.open()) {
        qDebug() << "Open sql failed";
        return false;
    }

    // 添加数据表
    QSqlQuery query(msgdb);
    // 创建历史聊天表
    query.exec("CREATE TABLE MSGINFO (id INT PRIMARY KEY, userId INT, name varchar(20),"
               "head varchar(50), datetime varchar(20), filesize varchar(30),"
               "content varchar(500), type INT, direction INT)");

    return true;
}

void DataBaseMgr::addHistoryMsg(const int &userId, ItemInfo *itemInfo) {
    // 查询数据库
    QSqlQuery query("SELECT [id] FROM MSGINFO ORDER BY id DESC;", msgdb);
    int nId = 0;
    // 查询最高ID
    if (query.next()) {
        nId = query.value(0).toInt();
    }

    // 根据新ID重新创建用户
    query.prepare("INSERT INTO MSGINFO (id, userId, name, head, datetime, filesize, content, type, direction) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);");

    query.bindValue(0, nId + 1);
    query.bindValue(1, userId);
    // query.bindValue(2, itemInfo->GetName());
    // query.bindValue(3, itemInfo->GetStrPixmap());
    // query.bindValue(4, itemInfo->GetDatetime());
    // query.bindValue(5, itemInfo->GetText());
    // query.bindValue(6, itemInfo->GetFileSizeString());
    // query.bindValue(7, itemInfo->GetOrientation());
    // query.bindValue(8, itemInfo->GetMsgType());

    query.exec();
}

void DataBaseMgr::addFriend(const int &id, const int &userId, const QString &name) {
    QString strQuery = "SELECT [id] FROM FRIEND ";
    strQuery.append("WHERE id=");
    strQuery.append(QString::number(id));
    strQuery.append(" AND userId=");
    strQuery.append(QString::number(userId));

    QSqlQuery query(strQuery, userdb);
    if (query.next()) {
        // 查询到有该用户，不添加
        qDebug() << "yes" << query.value(0).toString();
        return;
    }

    // 根据新ID重新创建用户
    query.prepare("INSERT INTO FRIEND (id, userid, name) "
                  "VALUES (?, ?, ?);");
    query.bindValue(0, id);
    query.bindValue(1, userId);
    query.bindValue(2, name);

    query.exec();
}

void DataBaseMgr::addGroup(const int &id, const int &userId, const QString &name) {
}

bool DataBaseMgr::deleteMyFriend(const int &id, const int &userId) {
}

QJsonArray DataBaseMgr::getMyFriend(const int &userId) const {
    QJsonArray  myFriends;

    QString strQuery = "SELECT [id] FROM FRIEND ";
    strQuery.append("WHERE userId=");
    strQuery.append(QString::number(userId));

    QSqlQuery query(strQuery, userdb);
    while (query.next()) {
        myFriends.append(query.value("id").toInt());
    }

    return myFriends;
}

QJsonArray DataBaseMgr::getMyGroup(const int &userId) const {
}

bool DataBaseMgr::isMyFriend(const int &userId, const QString &name) {
    QString strQuery = "SELECT [id] FROM FRIEND ";
    strQuery.append("WHERE name='");
    strQuery.append(name);
    strQuery.append("' AND userId='");
    strQuery.append(QString::number(userId));
    strQuery.append("';");

    QSqlQuery query(strQuery, userdb);
    return query.next();
}

bool DataBaseMgr::isInGroup(const QString &name) {
}

QVector<ItemInfo *> DataBaseMgr::queryHistory(const int &id, const int &count) {
}

void DataBaseMgr::queryAll() {
}

DataBaseMgr::DataBaseMgr(QObject *parent) :
    QObject(parent) {

}

DataBaseMgr::~DataBaseMgr() {
    if (userdb.isOpen())
        userdb.close();

    if (msgdb.isOpen())
        msgdb.close();
}

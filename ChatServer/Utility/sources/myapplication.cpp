//
// Created by utopia on 2025/4/26.
//

#include "../headers/MyApplication.h"
#include <QSettings>
#include <QDir>

// 应用程序路径
QString MyApplication::m_strAppPath         = "./";
// 数据保存路径
QString MyApplication::m_strDataPath        = "";
// 数据库目录
QString MyApplication::m_strDatabasePath    = "";
// 配置目录
QString MyApplication::m_strConfPath        = "";
QString MyApplication::m_strBackupPath      = "";
QString MyApplication::m_strRecvPath        = "";
QString MyApplication::m_strHeadPath        = "";

// 配置文件
QString MyApplication::m_strIniFile         = "config.ini";

QString MyApplication::m_strUserName        = "admin";
QString MyApplication::m_strPassword        = "123456";

int     MyApplication::m_nId                = -1;
int     MyApplication::m_nIdentyfi          = -1;

// 初始化
void MyApplication::InitApp(const QString &appPath){
    m_strAppPath        = appPath + "/";
    m_strDataPath       = m_strAppPath  + "Data/";
    m_strDatabasePath   = m_strDataPath + "Database/";
    m_strConfPath       = m_strDataPath + "Conf/";
    m_strBackupPath     = m_strDataPath + "Backup/";
    m_strRecvPath       = m_strDataPath + "RecvFiles/";
    m_strHeadPath       = m_strDataPath + "UserHeads/";
    m_strIniFile        = m_strConfPath + "config.ini";

    // 检查目录
    CheckDirs();
    // 创建配置文件
    CreatorSettingFile();
    // 加载系统配置
    ReadSettingFile();
}

/**
 * @brief MyApplication::creatorSettingFile 创建配置文件
 */
void MyApplication::CreatorSettingFile() {
    // 写入配置文件
    QSettings settings(m_strIniFile, QSettings::IniFormat);
    QString strGroups = settings.childGroups().join("");
    if (!QFile::exists(m_strIniFile) || (strGroups.isEmpty())){

        /*系统设置*/
        settings.beginGroup("UserCfg");
        settings.setValue("User",   m_strUserName);
        settings.setValue("Passwd", m_strPassword);
        settings.endGroup();
        settings.sync();

    }
#ifdef Q_WS_QWS
    QProcess::execute("sync");
#endif
}

/**
 * @brief MyApplication::ReadSettingFile
 * 读取系统配置信息
 */
void MyApplication::ReadSettingFile(){
    QSettings settings(m_strIniFile, QSettings::IniFormat);
    settings.beginGroup("UserCfg");
    m_strUserName = settings.value("User", "milo").toString();
    m_strPassword = settings.value("Passwd", "123456")  .toString();
    settings.endGroup();
}

/**
 * @brief MyApplication::setSettingFile 写入配置文件
 * @param group                 组
 * @param key                   key
 * @param value                 值
 */
void MyApplication::SetSettingFile(const QString &group, const QString &key, const QVariant &value)
{
    QSettings settings(m_strIniFile, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.sync();
}

/**
 * @brief MyApplication::getSettingKeyValue 读取配置参数
 * @param group
 * @param key
 * @return
 */
QVariant MyApplication::GetSettingKeyValue(const QString &group, const QString &key, const QVariant &value){
    QSettings settings(m_strIniFile, QSettings::IniFormat);
    settings.beginGroup(group);
    return settings.value(key, value);
}

/**
 * @brief MyApplication::checkDataDir 检查数据存储目录
 */
void MyApplication::CheckDirs(){
    // 数据文件夹
    QDir dir(m_strDataPath);
    if (!dir.exists()) {
        dir.mkdir(m_strDataPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 数据库目录
    dir.setPath(m_strDatabasePath);
    if (!dir.exists()) {
        dir.mkdir(m_strDatabasePath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 配置文件目录
    dir.setPath(m_strBackupPath);
    if (!dir.exists()) {
        dir.mkdir(m_strBackupPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 配置文件目录
    dir.setPath(m_strRecvPath);
    if (!dir.exists()) {
        dir.mkdir(m_strRecvPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 配置文件目录
    dir.setPath(m_strHeadPath);
    if (!dir.exists()) {
        dir.mkdir(m_strHeadPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }
}

// 保存配置
void MyApplication::SaveConfig(){
    QSettings settings(m_strIniFile, QSettings::IniFormat);

    /*系统设置*/
    settings.beginGroup("UserCfg");
    settings.setValue("User",   m_strUserName);
    settings.setValue("Passwd", m_strPassword);
    settings.endGroup();
    settings.sync();
}

#include <QApplication>
#include <QApplication>
#include "./WeChat/logindialog.h"
#include "./Utility/global.h"
#include "./DataBase/databasemgr.h"
#include "./Utility/myapp.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    MyApp::InitApp(a.applicationDirPath());
    // 加载数据库
    DataBaseMgr::Instance()->openUserDb(MyApp::m_strDatabasePath + "user.db");
    DataBaseMgr::Instance()->openMessageDb(MyApp::m_strDatabasePath + "msg.db");

    LoginDialog w;
    GLobalHelper::formInCenter(&w);
    w.show();
    return QApplication::exec();
}
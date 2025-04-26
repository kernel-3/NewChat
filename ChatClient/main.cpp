// #ifdef __linux__
// #pragma message ("当前头文件搜索路径: " __FILE__)
// #else
// #pragma message ("当前头文件搜索路径: " __FILE__)
// #endif


#include <QApplication>
#include <QSqlDatabase>
#include "./NewChat//headers/logindialog.h"
#include "Utility/headers/global.h"
#include "./DataBase//headers/databasemgr.h"
#include "Utility/headers/myapp.h"

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
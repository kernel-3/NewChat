#include <QApplication>
#include <QPushButton>
#include <QFile>

#include "./Utility/headers/myapplication.h"
#include "./DataBase/headers/databasemgr.h"
#include "./NewChat/headers/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MyApplication::InitApp(a.applicationDirPath());
    DataBaseMgr::Instance()->OpenDb(MyApplication::m_strDatabasePath + "info.db");
    MainWindow w;
    w.show();
    return QApplication::exec();
}
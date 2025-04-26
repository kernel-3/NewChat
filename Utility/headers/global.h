//
// Created by utopia on 2025/4/22.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QApplication>
//#include <QDesktopWidget> Qt6已丢弃
#include <QScreen>
#include <QDebug>
#include <QFileInfo>

class GLobalHelper : public QObject {

public:
    // 设置为开机启动

    // 窗体居中显示
    static void formInCenter(QWidget *widget) {
        // 获取主屏幕的可用区域（不包含系统任务栏）
        QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
        // 计算尺寸
        int screenX = availableGeometry.width();
        int screenY = availableGeometry.height() - 60;  // 根据需求调整高度
        // int screenX = qApp->desktop()->availableGeometry().width();
        // int screenY = qApp->desktop()->availableGeometry().height()-60;
        qDebug() << "Screen Available Size (WxH):" << screenX << "x" << screenY;
        int wndX = widget->width();
        int wndY = widget->height();
        QPoint movePoint((screenX-wndX)/2,(screenY-wndY)/2);
        widget->move(movePoint);
    }

    //获取文件名，含拓展名
    static QString getFileNameWithExtension(QString strFilePath){
        qDebug()<<"获取文件名"<<strFilePath;
        QFileInfo fileInfo(strFilePath);
        return fileInfo.fileName();
    }

    //延时
    static void Sleep(int sec){
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

};


#endif //GLOBAL_H

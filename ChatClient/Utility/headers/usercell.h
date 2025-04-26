//
// Created by utopia on 2025/4/24.
//

#ifndef USERCELL_H
#define USERCELL_H
#include <QString>
#include <QList>

typedef enum tagCellType_e{
    CellType_Group = 0,
    CellType_Child = 1,
    CellType_GroupEx = 2,
} CellType_e;

class UserCell {
public:
     UserCell();
    ~UserCell() ;
    void setSubtitle(const QString &text);
    void setIconPath(const QString &path);
    void setStatus(const quint8 &val);
public:
    QString iconPath;
    QString name;
    QString subTitle;

    QString ipaddr;
    QString groupName;      //组名
    int     id;
    int     status;

    CellType_e type;
    //下面几项都是用于组(QQCellType_Group)状态, 对于子(QQCellType_Child)状态无用
    //是否是打开状态
    bool isOpen;
    //子项
    QList<UserCell *> childs;
};


#endif //USERCELL_H

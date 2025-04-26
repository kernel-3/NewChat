/********************************************************************************
** Form generated from reading UI file 'rotatingstackedwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROTATINGSTACKEDWIDGET_H
#define UI_ROTATINGSTACKEDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStackedWidget>

QT_BEGIN_NAMESPACE

class Ui_RotatingStackedWidget
{
public:

    void setupUi(QStackedWidget *RotatingStackedWidget)
    {
        if (RotatingStackedWidget->objectName().isEmpty())
            RotatingStackedWidget->setObjectName("RotatingStackedWidget");
        RotatingStackedWidget->resize(400, 300);

        retranslateUi(RotatingStackedWidget);

        QMetaObject::connectSlotsByName(RotatingStackedWidget);
    } // setupUi

    void retranslateUi(QStackedWidget *RotatingStackedWidget)
    {
        RotatingStackedWidget->setWindowTitle(QCoreApplication::translate("RotatingStackedWidget", "RotatingStackedWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RotatingStackedWidget: public Ui_RotatingStackedWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROTATINGSTACKEDWIDGET_H

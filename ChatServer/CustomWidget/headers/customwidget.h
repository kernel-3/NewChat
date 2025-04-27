//
// Created by utopia on 2025/4/26.
//

#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H
#include <QWidget>
#include <QDialog>
#include <QMutex>
#include <QTimer>

#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
QT_END_NAMESPACE

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
};

// 可移动窗口
class CustomMoveWidget : public CustomWidget {
    Q_OBJECT
public:
    explicit CustomMoveWidget(QWidget *parent = 0);
    ~CustomMoveWidget();

protected:
    QPoint mousePoint;
    bool m_mousePressed;

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
};

class CustomDialog : public QDialog {
    Q_OBJECT
public:
    explicit CustomDialog(QWidget *parent = 0);
    ~CustomDialog();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

protected:
    QPoint mousePoint;
    bool m_mousePressed;
};

class CBaseDialog : public CustomDialog {
    Q_OBJECT
public:
    explicit CBaseDialog(QWidget *parent = 0);
    ~CBaseDialog();

    void SetWinIcon(QPixmap pixmap);
    void SetWinTitle(const QString &text);

protected:
    QWidget         *widgetBody;

private:
    QWidget         *widgetWinTitle;
    QLabel          *labelWinIcon;
    QLabel          *labelWinTitle;
    QPushButton     *btnWinMin;
    QPushButton     *btnWinClose;
};

class CMessageBox : public CBaseDialog
{
    Q_OBJECT
public:
    typedef enum {
        Information =  0x01,
        Warnings,
        Questions,
        Error,
    } E_MSGTYPE;

public:
    explicit CMessageBox(QWidget *parent = 0);
    ~CMessageBox();

    // 显示消息
    void ShowMessage(const QString &content, const quint8 &msgType = CMessageBox::Information, const QString &title = "");

    void StartTimer();

    static int Infomation(QWidget *parent, const QString &content, const QString &title = "提示");
    static int Question(QWidget *parent, const QString &content, const QString &title = "询问");
    static int Warning(QWidget *parent, const QString &content, const QString &title = "告警");
public slots:
    void SltTimerOut();

private:
    QLabel      *labelIcon;
    QLabel      *labelMsgContent;

    QPushButton *btnOk;
    QPushButton *btnCancel;

    QTimer      *m_timer;
    int         m_nTimerCnt;
};


class CInputDialog : public CBaseDialog
{
    Q_OBJECT
public:
    explicit CInputDialog(QWidget *parent = 0);
    ~CInputDialog();

    static QString GetInputText(QWidget *parent,
                                const QString &text = "",
                                const QString &title = "输入",
                                QLineEdit::EchoMode mode = QLineEdit::Normal);

    QString GetText() const;
    void SetInputText(const QString &text);

    void SetEchoMode(QLineEdit::EchoMode mode);
private:
    static CInputDialog *self;

    QLabel    *labelText;
    QLineEdit *lineEditInput;

    QPushButton *btnOk;
    QPushButton *btnCancel;
};


#endif //CUSTOMWIDGET_H

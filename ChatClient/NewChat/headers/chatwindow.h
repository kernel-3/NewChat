//
// Created by utopia on 2025/4/23.
//

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>


class ChatWindow : public QWidget {
Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow() override;


};


#endif //CHATWINDOW_H

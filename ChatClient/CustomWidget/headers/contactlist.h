//
// Created by utopia on 2025/4/24.
//

#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QListWidget>
#include <QString>


class ContactList : public QListWidget  {
Q_OBJECT

public:
    explicit ContactList(QListWidget  *parent = nullptr);
    ~ContactList() override;
public:
    void addContact(const QString& avatar, const QString& name,
                   const QString& lastMsg, const QString& time,
                   int unread = 0, bool online = false);
private:
    void initUI();

};


#endif //CONTACTLIST_H

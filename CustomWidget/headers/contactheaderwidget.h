//
// Created by utopia on 2025/4/24.
//

#ifndef CONTACTHEADERWIDGET_H
#define CONTACTHEADERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class ContactHeaderWidget : public QWidget {
Q_OBJECT

public:
    explicit ContactHeaderWidget(QWidget *parent = nullptr);
    ~ContactHeaderWidget() override;

    QLineEdit* searchEdit() const { return m_searchEdit; }
    QPushButton* addButton() const { return m_btnAdd; }

signals:
    void searchTextChanged(const QString &text);
    void addButtonClicked();
private:
    void initUI();
    void initStyle();

private:
    QLineEdit *m_searchEdit;
    QPushButton *m_btnAdd;
};


#endif //CONTACTHEADERWIDGET_H

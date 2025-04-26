//
// Created by utopia on 2025/4/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ContactHeaderWidget.h" resolved

#include "contactheaderwidget.h"
#include <QFile>

ContactHeaderWidget::ContactHeaderWidget(QWidget *parent) :
    QWidget(parent) {
    setObjectName("ContactHeaderWidget");
    initUI();
    initStyle();
    setFixedHeight(48);
}

ContactHeaderWidget::~ContactHeaderWidget() {

}

void ContactHeaderWidget::initUI() {
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(12, 8, 12, 8);
    hLayout->setSpacing(6);

    // 搜索框
    m_searchEdit = new QLineEdit;
    m_searchEdit->setPlaceholderText("搜索");
    m_searchEdit->setClearButtonEnabled(true);
    m_searchEdit->addAction(QIcon(":/images/icons/search.png"), QLineEdit::LeadingPosition);
    m_searchEdit->setObjectName("search-edit");

    qDebug() << "Add icon exists:"
             << QFile(":/images/icons/add.png").exists();     // 应该输出true
    // 加号按钮
    m_btnAdd = new QPushButton;
    m_btnAdd->setFixedSize(32, 32);
    m_btnAdd->setObjectName("add-button");
    m_btnAdd->setStyleSheet(R"(
        QPushButton {
            border: none;
            background: transparent url(:/images/icons/add.png) no-repeat center;
            background-size: 20px 20px;
            min-width: 32px;
            min-height: 32px;
        }
        QPushButton:hover {
            background-color: #F0F0F0;
        }
    )");
    hLayout->addWidget(m_searchEdit);
    hLayout->addWidget(m_btnAdd);

    connect(m_searchEdit, &QLineEdit::textChanged, this, &ContactHeaderWidget::searchTextChanged);
    connect(m_btnAdd, &QPushButton::clicked, this, &ContactHeaderWidget::addButtonClicked);
}

void ContactHeaderWidget::initStyle() {
    QPixmap testPixmap(":/images/icons/add.png");
    if(testPixmap.isNull()) {
        qWarning() << "Failed to load search icon!";
    }
    // 增加!important强制样式生效
    setStyleSheet(R"(
        ContactHeaderWidget {
            background: #F0F0F0;  !important;
            border-bottom: 1px solid #E5E5E5;
        }

        QLineEdit#search-edit {
            border: 1px solid #E5E5E5;
            border-radius: 16px;
            padding: 6px 12px 6px 28px;  // 增加左侧padding给图标留空间
            font-size: 14px;
            min-height: 32px;
            background: white;
        }
        QLineEdit#search-edit:hover {
            border-color: #1AAD19;
        }
        QLineEdit#search-edit:focus {
            border-color: #1AAD19;
        }

        QPushButton#add-button {
            border: none;
            border-radius: 4px;
            background: transparent;
            qproperty-icon: url(:/images/icons/add.png);
            qproperty-iconSize: 20px;
        }
        QPushButton#add-button:hover {
             background-color: rgba(240, 240, 240, 0.9);  // 半透明悬浮效果
        }
        QPushButton#add-button:pressed {
            background: #E5E5E5;
        }
    )");
}

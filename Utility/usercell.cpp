//
// Created by utopia on 2025/4/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserCell.h" resolved

#include "usercell.h"

UserCell::UserCell() {
    isOpen = false;
}

UserCell::~UserCell() {
}

void UserCell::setSubtitle(const QString &text) {
    if (text.isEmpty()) return;
    subTitle = text;
}

void UserCell::setIconPath(const QString &path) {
    if (path.isEmpty()) return;
    iconPath = path;
}

void UserCell::setStatus(const quint8 &val) {
    status = val;
}

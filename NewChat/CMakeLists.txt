cmake_minimum_required(VERSION 3.20)
project(WeChat)

# 定义源文件和头文件路径
set(WECHAT_SOURCES
        sources/mainwindow.cpp
        sources/logindialog.cpp
        sources/chatwindow.cpp
)

set(WECHAT_HEADERS
        headers/mainwindow.h
        headers/logindialog.h
        headers/chatwindow.h
)

# 创建静态库
add_library(wechat_lib STATIC
        ${WECHAT_SOURCES}
        ${WECHAT_HEADERS}
)

# 设置头文件路径
target_include_directories(wechat_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# 链接依赖的 Qt 模块和子库
target_link_libraries(wechat_lib
        Qt6::Widgets
        Qt6::Gui
        Qt6::Network
        database_lib      # 依赖 DataBase 模块
        customwidget_lib  # 依赖 CustomWidget 模块
        utility_lib       # 依赖 Utility 模块
        network_lib       # 依赖 Network 模块
)
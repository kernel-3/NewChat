# CustomWidget/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

# 定义源文件和头文件
set(CUSTOM_WIDGET_SOURCES
        sources/customwidget.cpp
)

set(CUSTOM_WIDGET_HEADERS
        headers/customwidget.h
)


# 创建静态库
add_library(customwidget_lib STATIC
        ${CUSTOM_WIDGET_SOURCES}
        ${CUSTOM_WIDGET_HEADERS}
)

# 关键配置：添加 headers/ 目录到编译器搜索路径
target_include_directories(customwidget_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers  # 核心配置：允许直接引用头文件名
)

# 链接依赖项（根据实际使用添加）
target_link_libraries(customwidget_lib
        Qt6::Widgets  # 假设使用了 Qt Widgets 组件
        Qt6::Core
        # 其他依赖...
)
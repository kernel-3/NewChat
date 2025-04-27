# Utility/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

# 定义源文件和头文件
set(UTILITY_SOURCES
        sources/myapplication.cpp
)

set(UTILITY_HEADERS
        headers/myapplication.h
        headers/unit.h
        headers/global.h
)

# 创建静态库
add_library(utility_lib STATIC
        ${UTILITY_SOURCES}
        ${UTILITY_HEADERS}
)

target_include_directories(utility_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers  # 指向 Utility/headers 目录
)

# 链接Qt依赖
target_link_libraries(utility_lib
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
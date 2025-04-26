# DataBase/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(DataBase)

# 定义源文件和头文件路径
set(DATABASE_SOURCES
        sources/databasemgr.cpp
)

set(DATABASE_HEADERS
        headers/databasemgr.h
)


# 创建静态库
add_library(database_lib STATIC
        ${DATABASE_SOURCES}
        ${DATABASE_HEADERS}
)

# 设置头文件路径（PUBLIC 确保依赖此库的模块能继承路径）
target_include_directories(database_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# 链接依赖的 Qt 模块
target_link_libraries(database_lib
        Qt6::Core
        Qt6::Sql
)
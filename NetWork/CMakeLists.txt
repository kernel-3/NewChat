cmake_minimum_required(VERSION 3.20)
project(Network)

# 定义源文件和头文件路径
set(NETWORK_SOURCES
        sources/clientsocket.cpp
)

set(NETWORK_HEADERS
        headers/clientsocket.h
)

# 创建静态库
add_library(network_lib STATIC
        ${NETWORK_SOURCES}
        ${NETWORK_HEADERS}
)

# 设置头文件路径
target_include_directories(network_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# 链接依赖的 Qt 模块
target_link_libraries(network_lib
        Qt6::Network
        Qt6::Core
)
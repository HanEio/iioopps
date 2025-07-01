# 指定cmake的最低版本，确保兼容性
    cmake_minimum_required(VERSION 3.20)

    # Project name and version
    project(shudu VERSION 1.0.0)

    add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)

    # color.h 已被 src/scene.cpp 引用，无需单独添加
    # add an executable 
    add_executable(shudu src/main.cpp src/scene.cpp src/block.cpp src/input.cpp src/i18n.cpp)
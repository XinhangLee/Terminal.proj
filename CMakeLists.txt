cmake_minimum_required(VERSION 3.30)
project(browserinterminal C)

set(CMAKE_C_STANDARD 11)

# 使用target_include_directories代替include_directories
add_executable(browserinterminal
    Terminal-Tools/Terminal.c
    test.c
)

# 为可执行文件指定包含目录
target_include_directories(browserinterminal PRIVATE Terminal-Tools)
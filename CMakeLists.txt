cmake_minimum_required(VERSION 3.30)
project(browserinterminal C)

set(CMAKE_C_STANDARD 11)

include_directories(Terminal-Tools)

add_executable(browserinterminal
    Terminal-Tools/Terminal.c
    test.c)

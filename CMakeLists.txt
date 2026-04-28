cmake_minimum_required(VERSION 3.5)

project(clox VERSION 1.0.0 LANGUAGES C)

add_executable(clox
    src/main.c
)

target_include_directories(clox PRIVATE include)

cmake_minimum_required(VERSION 3.5)

project(clox VERSION 1.0.0 LANGUAGES C)

add_executable(clox
    src/main.c
    src/chunk.c
    src/memory.c
    src/debug.c
    src/value.c
)

target_include_directories(clox PRIVATE include)

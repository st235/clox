cmake_minimum_required(VERSION 3.10)

project(clox VERSION 1.0.0 LANGUAGES C)

add_library(clox-core
    src/chunk.c
    src/memory.c
    src/debug.c
    src/value.c
    src/vm.c
    src/compiler.c
    src/scanner.c
    src/object.c
    src/table.c
)

target_include_directories(clox-core PUBLIC
    include
)

add_executable(clox
    src/main.c
)

target_link_libraries(clox PRIVATE clox-core)

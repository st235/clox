cmake_minimum_required(VERSION 3.10)

project(clox VERSION 1.0.0 LANGUAGES C CXX)

option(ENABLE_DEBUG "Enables debug logging." OFF)
option(ENABLE_NAN_TAGGING "Enables NaN tagging optimisation." ON)

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

if(ENABLE_DEBUG)
    target_compile_definitions(clox-core PRIVATE _CLOX_DEBUG)
    target_compile_definitions(clox-core PRIVATE _CLOX_NAN_TAGGING)
endif()

add_executable(clox
    src/main.c
)

target_link_libraries(clox PRIVATE clox-core)

add_dependencies(clox
    clox-core
)

add_subdirectory(tests)

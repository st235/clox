message(STATUS "Compiling tests...")

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(clox-tests
    clox_tests.cpp
)

target_link_libraries(clox-tests PRIVATE clox-core)

target_link_libraries(clox-tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(clox-tests)

# Test files and their produced outputs.
set(LOX_FILES
    res/expressions.lox
    res/expressions.out
    res/variables.lox
    res/variables.out
    res/scopes.lox
    res/scopes.out
    res/if.lox
    res/if.out
    res/while.lox
    res/while.out
    res/logical.lox
    res/logical.out
    res/for.lox
    res/for.out
    res/fraction.lox
    res/fraction.out
    res/functions.lox
    res/functions.out
    res/closures.lox
    res/closures.out
    res/classes.lox
    res/classes.out
    res/inheritance.lox
    res/inheritance.out
)

foreach(file_path ${LOX_FILES})
    file(COPY ${file_path} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach(file_path)

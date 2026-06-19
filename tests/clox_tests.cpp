#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <fstream>
#include <string>
#include <strstream>
#include <vector>

extern "C" {
#include "chunk.h"
#include "value.h"
#include "vm.h"
}

namespace {

std::string ReadFile(const char* path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return std::string();
    }

    std::ostringstream out;
    out << file.rdbuf();
    return out.str();
}

extern "C" Value nativeFloor(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        return NIL_VAL;
    }
    return NUMBER_VAL(std::floor(AS_NUMBER(args[0])));
}

extern "C" Value nativeMod(int argCount, Value* args) {
    if (argCount != 2) {
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0]) || !IS_NUMBER(args[1])) {
        return NIL_VAL;
    }

    double arg0 = std::floor(AS_NUMBER(args[0]));
    double arg1 = std::floor(AS_NUMBER(args[1]));

    return NUMBER_VAL(static_cast<double>(static_cast<int64_t>(arg0) % static_cast<int64_t>(arg1)));
}

}  // namespace

using TestPayload = std::pair<std::string, std::string>;
class CLoxIntegratedTestsFixture: public ::testing::TestWithParam<TestPayload> {
    void SetUp() {
        initVM();
        defineNative("floor", nativeFloor);
        defineNative("mod", nativeMod);
    }

    void TearDown() {
        freeVM();
    }
};

INSTANTIATE_TEST_SUITE_P(
        CLoxTests,
        CLoxIntegratedTestsFixture,
        ::testing::Values(
            std::make_pair("expressions.lox", "expressions.out"),
            std::make_pair("variables.lox", "variables.out"),
            std::make_pair("scopes.lox", "scopes.out"),
            std::make_pair("if.lox", "if.out"),
            std::make_pair("while.lox", "while.out"),
            std::make_pair("logical.lox", "logical.out"),
            std::make_pair("for.lox", "for.out"),
            std::make_pair("fraction.lox", "fraction.out"),
            std::make_pair("functions.lox", "functions.out"),
            std::make_pair("closures.lox", "closures.out"),
            std::make_pair("classes.lox", "classes.out"),
            std::make_pair("inheritance.lox", "inheritance.out")
        )
);

TEST_P(CLoxIntegratedTestsFixture, CLoxCorrectlyInterpretsTheProgram) {
    const auto& pair = GetParam();

    const auto& file_path = pair.first;
    const auto& expected_output_path = pair.second;

    const auto file_content = ReadFile(file_path.c_str());

    ASSERT_GT(file_content.size(), 0);

    int saved = dup(STDOUT_FILENO);

    // A hack to redirect printf into a file.
    FILE* file = fopen("output.txt", "w");
    dup2(fileno(file), STDOUT_FILENO);

    interpret(file_content.c_str());

    fflush(stdout);

    dup2(saved, STDOUT_FILENO);

    close(saved);
    fclose(file);

    const auto expected_output = ReadFile(expected_output_path.c_str());
    ASSERT_GT(expected_output.size(), 0);

    const auto actual_output = ReadFile("output.txt");
    ASSERT_GT(actual_output.size(), 0);

    ASSERT_EQ(expected_output, actual_output);
}

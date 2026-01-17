#include "tests.h"
#include "logic.h"
#include <iostream>
#include <cassert>

bool RunAllTests() {
    bool all_passed = true;

    // Test 1
    {
        const std::string text = "Hello world test";
        const int max_len = 4;
        const int expected = 1;
        const int result = CountShortWords(text, max_len);
        if (result != expected) {
            std::cerr << "Тест 1 провален: ожидалось " << expected << ", получено " << result << std::endl;
            all_passed = false;
        }
    }

    // Test 2
    {
        const std::string text = "a bb ccc dddd";
        const int max_len = 3;
        const int expected = 3;
        const int result = CountShortWords(text, max_len);
        if (result != expected) {
            std::cerr << "Тест 2 провален: ожидалось " << expected << ", получено " << result << std::endl;
            all_passed = false;
        }
    }

    // Test 3
    {
        const std::string text = "C++ is great!";
        const int max_len = 4;
        const int expected = 2;
        const int result = CountShortWords(text, max_len);
        if (result != expected) {
            std::cerr << "Тест 3 провален: ожидалось " << expected << ", получено " << result << std::endl;
            all_passed = false;
        }
    }

    // Test 4
    {
        const std::string text = "";
        const int max_len = 5;
        const int expected = 0;
        const int result = CountShortWords(text, max_len);
        if (result != expected) {
            std::cerr << "Тест 4 провален: ожидалось " << expected << ", получено " << result << std::endl;
            all_passed = false;
        }
    }

    // Test 5
    {
        const std::string text = "L.I.P.O.A.I.S";
        const int max_len = 7;
        const int expected = 1;
        const int result = CountShortWords(text, max_len);
        if (result != expected) {
            std::cerr << "Тест 5 провален: ожидалось " << expected << ", получено " << result << std::endl;
            all_passed = false;
        }
    }

    return all_passed;
}
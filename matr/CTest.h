#pragma once

#include <functional>


class CTest
{
protected:
    static void Test(std::function<bool()> test_func);

protected:
    static size_t _test_count;

};
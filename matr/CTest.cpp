#include <iomanip>
#include <iostream>

#include "CTest.h"

size_t CTest::_test_count = 0;

void CTest::Test(std::function<bool()> test_func)
{
    std::cout << "Test " << std::setw(5) << _test_count << ": " << std::boolalpha << (test_func()) << std::endl;
}

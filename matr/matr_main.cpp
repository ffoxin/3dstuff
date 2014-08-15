#include <iomanip>
#include <iostream>

#include "CVector.h"
#include "CMatrix.h"

#include "CVectorTest.h"


int wmain(int argc, wchar_t* argv[])
{
    //std::cout << std::left;

    //CVectorTest::RunAll<4>();

    double m1[] = { 
        1, 0, 0,
        0, 2, 0,
        0, 0, 3, 
    };
    double m2[] = {
        1, 0, 0,
        0, 0.5, 0,
        0, 0, 0.333333,
    };

    double m3[] = {
        1, 0, 0, 1, 0, 0,
        0, 2, 0, 0, 1, 0,
        0, 0, 3, 0, 0, 1,
    };
    
    CMatrix<double, 3, 3> mx1(m1);
    CMatrix<double, 3, 3> mx2(m2);
    CMatrix<double, 3, 6> mx3(m3);
    std::cout << mx3 << std::endl;
    auto mx4 = AppendHorz(mx1, mx2);
    std::cout << mx4 << std::endl;
    mx3.RowReduce();
    std::cout << mx3 << std::endl;
    std::cout << mx1 * mx2 << std::endl;


    return 0;
}

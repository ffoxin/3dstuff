#pragma once

#include "CTest.h"
#include "CVector.h"


class CVectorTest : public CTest
{
public:
    template<size_t to>
    static void RunAll();

private:

    template<>
    static void RunAll<1>();

    template<size_t to>
    static void RunAllInt();

    template<size_t to>
    static void RunAllDouble();

    template<typename T, size_t size>
    static bool TestInit();

    template<size_t size>
    static bool TestConstructInt();

    template<size_t size>
    static bool TestAssignInt();

    template<size_t size>
    static bool TestAddInt();

    template<size_t size>
    static bool TestSubstructInt();

    template<size_t size>
    static bool TestMultValInt();

    template<size_t size>
    static bool TestMultInt();

};

template<size_t to>
void CVectorTest::RunAllDouble()
{
    Test(TestInit<double, to>);
}

template<size_t size>
bool CVectorTest::TestMultInt()
{
    _test_count++;
    bool result = true;

    int m1[size], m2[size];
    for (int i = 0; i < size; ++i)
    {
        m1[i] = i;
        m2[i] = i + 5;
    }

    CVector<int, size> vi1(m1);
    CVector<int, size> vi2(m2);

    int mult = 0;
    for (size_t i = 0; i < size; ++i)
    {
        mult += m1[i] * m2[i];
    }

    result &= vi1 * vi2 == mult;

    return result;
}

template<size_t size>
bool CVectorTest::TestMultValInt()
{
    _test_count++;
    bool result = true;

    int m[size];
    for (int i = 0; i < size; ++i)
    {
        m[i] = i;
    }

    CVector<int, size> vi(m);
    vi *= 5;

    for (size_t i = 0; i < size; ++i)
    {
        result &= vi[i] == m[i] * 5;
    }

    return result;
}

template<size_t size>
bool CVectorTest::TestSubstructInt()
{
    _test_count++;
    bool result = true;

    int m1[size], m2[size];
    for (int i = 0; i < size; ++i)
    {
        m1[i] = i;
        m2[i] = i + 5;
    }

    CVector<int, size> vi1(m1);
    CVector<int, size> vi2(m2);

    vi1 -= vi2;

    for (size_t i = 0; i < size; ++i)
    {
        result &= vi1[i] == -5;
    }

    return result;
}

template<size_t size>
bool CVectorTest::TestAddInt()
{
    _test_count++;
    bool result = true;

    int m1[size], m2[size];
    for (int i = 0; i < size; ++i)
    {
        m1[i] = i;
        m2[i] = i + 5;
    }

    CVector<int, size> vi1(m1);
    CVector<int, size> vi2(m2);

    vi1 += vi2;

    for (size_t i = 0; i < size; ++i)
    {
        result &= vi1[i] == m1[i] + m2[i];
    }

    return result;
}

template<size_t size>
bool CVectorTest::TestAssignInt()
{
    _test_count++;
    bool result = true;

    int m[size];
    for (int i = 0; i < size; ++i)
    {
        m[i] = i;
    }

    CVector<int, size> vi1(m);
    CVector<int, size> vi2 = vi1;

    for (size_t i = 0; i < size; ++i)
    {
        result &= vi2[i] == m[i];
    }

    return result;
}

template<size_t size>
bool CVectorTest::TestConstructInt()
{
    _test_count++;
    bool result = true;

    int m[size];
    for (int i = 0; i < size; ++i)
    {
        m[i] = i;
    }

    CVector<int, size> vi(m);
    for (size_t i = 0; i < size; ++i)
    {
        result &= vi[i] == m[i];
    }

    return result;
}

template<typename T, size_t size>
bool CVectorTest::TestInit()
{
    _test_count++;
    bool result = true;

    CVector<T, size> v;
    for (size_t i = 0; i < size; ++i)
    {
        result &= v[i] == T();
    }

    return result;
}

template<size_t to>
void CVectorTest::RunAll()
{
    RunAll<to - 1>();

    RunAllInt<to>();
    RunAllDouble<to>();
}

template<>
void CVectorTest::RunAll<1>()
{
    RunAllInt<1>();
    RunAllDouble<1>();
}

template<size_t to>
void CVectorTest::RunAllInt()
{
    Test(TestInit<int, to>);
    Test(TestConstructInt<to>);
    Test(TestAssignInt<to>);
    Test(TestAddInt<to>);
    Test(TestSubstructInt<to>);
    Test(TestMultValInt<to>);
    Test(TestMultInt<to>);
}

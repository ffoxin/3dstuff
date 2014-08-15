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

/*
#include <stdio.h>
#define SIZE_NUMBER 20
//скачено с http://algorithmlib.org/
int read_file_TO_matrix(char *name, int &str, int &stb, double **&mass)//чтение матрицы из файла
{
    char buffer;
    double number;
    double ttt = 10;
    int i, j;
    bool flag = false;
    mass = 0;
    str = stb = i = j = 0;
    unsigned int code = 0;
    FILE *fo;
    fo = fopen(name, "r");
    if (!fo)
        return 0;
    while (!feof(fo))
    {
        if (!fread(&buffer, sizeof(char), 1, fo))
            break;
        if (buffer >= '0' && buffer <= '9')
        {
            if (!(code > 0 && code <= SIZE_NUMBER))
                code = 1;
            else code++;
            if (ttt == 10)
                number = number*ttt + (buffer - '0');
            else
            {
                number = number + (buffer - '0')*ttt;
                ttt /= 10;
            }
            continue;
        }
        else if (buffer == '-')
        {
            flag = true;
            continue;
        }
        else if (buffer == '.')
        {
            if (ttt == 10)
            {
                ttt = 0.1;
                continue;
            }
            else
            {
                for (int k = 0; k < i; k++)
                    delete[]mass[k];
                if (mass != 0)delete[]mass;
                return 0;
            }
        }
        else if (code>0 && code <= SIZE_NUMBER)
        {
            if (flag)
                number = -number;
            if (str == 0)
                str = number;
            else if (stb == 0)
                stb = number;
            else if (str > 0 && stb > 0)
            {
                if (i == 0 && j == 0)
                {
                    mass = new double *[str];
                    mass[i] = new double[stb];
                }
                else if (j >= stb)
                {
                    if (++i >= str)
                    {
                        j = -1; break;
                    }
                    mass[i] = new double[stb];
                    j = 0;
                }
                if (j < stb)
                    mass[i][j++] = number;
            }
        }
        ttt = 10;
        flag = false;
        number = 0;
        code = 0;
    }
    if (str - 1 == i && stb == j)
        return 1;

    for (j = i; j >= 0; j--)
        delete[]mass[j];
    delete[]mass;

    return 0;
}

void print_matrix(int str, int stb, double **mass)//вывод матрицы в консоль
{
    for (int i = 0; i < str; i++)
    {
        for (int j = 0; j < stb; j++)
            printf("a[%d][%d]=%f \t", i, j, mass[i][j]);
        printf("\n");
    }
    printf("\n");
}


int gaus_obr(int cnt_str, double **mass, double **&M_obr)
{
    int i, j, k;
    //создание единичной матрицы 
    M_obr = new double*[cnt_str];
    for (i = 0; i < cnt_str; i++)
    {
        M_obr[i] = new double[cnt_str];
        for (j = 0; j < cnt_str; j++)M_obr[i][j] = 0;
        M_obr[i][i] = 1;
    }
    //пр€мой ход методом √аусса
    double a, b;
    for (i = 0; i < cnt_str; i++)
    {
        a = mass[i][i];
        for (j = i + 1; j < cnt_str; j++)
        {
            b = mass[j][i];
            for (k = 0; k < cnt_str; k++)
            {
                mass[j][k] = mass[i][k] * b - mass[j][k] * a;
                M_obr[j][k] = M_obr[i][k] * b - M_obr[j][k] * a;
            }
        }
    }
    //обратный ход нахождени€ элементов обратной матрицы
    double sum;
    for (i = 0; i < cnt_str; i++)
    {
        for (j = cnt_str - 1; j >= 0; j--)
        {
            sum = 0;
            for (k = cnt_str - 1; k > j; k--)
                sum += mass[j][k] * M_obr[k][i];
            if (mass[j][j] == 0)
            {
                for (i = 0; i < cnt_str; i++)
                    delete[]M_obr[i];
                delete[]M_obr;
                return 0;
            }
            M_obr[j][i] = (M_obr[j][i] - sum) / mass[j][j];
        }
    }
    return 1;
}

int main(int args, char *argv[])
{
    int str, stb;
    str = stb = 0;
    double **mass;
    double **M_obr;
    if (read_file_TO_matrix(argv[1], str, stb, mass) == 1 && str == stb)//чтение матрицы из файла
    {
        if (gaus_obr(str, mass, M_obr) == 1)//вычисление обратной матрицы метод √аусса
        {
            print_matrix(str, str, M_obr);
            for (int i = 0; i < str; i++)
                delete[]M_obr[i];
            delete[]M_obr;
        }
        else
        {
            printf("Error obr matrix\n");
        }

        for (int i = 0; i < str; i++)
            delete[]mass[i];
        delete[]mass;

    }
    else
    {
        printf("Error read matrix\n");
    }

    return 0;
}
//скачено с http://algorithmlib.org/
*/
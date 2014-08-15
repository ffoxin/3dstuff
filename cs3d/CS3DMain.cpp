#include <windows.h>

#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    const int WIDTH = 160;
    const int HEIGHT = 20;

    int short y = 7;
    cout << (int) (y * 0.125) * 84 << endl;
    cout << (y * 0.125) * 84 << endl;
    return 0;

    COORD coord;
    coord.X = WIDTH;
    coord.Y = HEIGHT;
    
    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = WIDTH - 1;
    rect.Bottom = HEIGHT - 1;

    HANDLE hstd = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hstd == INVALID_HANDLE_VALUE)
    {
        printf("GetStdHandle: %d\n", GetLastError());
        return 1;
    }
    
    CONSOLE_FONT_INFOEX cfie;
    if (GetCurrentConsoleFontEx(hstd, true, &cfie) == 0)
    {
        printf("GetCurrentConsoleFontEx failed: %d\n", GetLastError());
        return 1;
    }
    wprintf(L"%ls\n", cfie.FaceName);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hstd, &csbi);
    coord = GetLargestConsoleWindowSize(hstd);
    printf("%dx%d\n", csbi.dwSize.X, csbi.dwSize.Y);
    printf("%dx%d\n", csbi.dwMaximumWindowSize.X, csbi.dwMaximumWindowSize.Y);
    printf("%dx%d\n", coord.X, coord.Y);
    BOOL ret = SetConsoleWindowInfo(hstd, true, &rect);
    if (ret == 0)
    {
        printf("SetConsoleWindowInfo failed: %d\n", GetLastError());
        return 1;
    }



    return 0;
}

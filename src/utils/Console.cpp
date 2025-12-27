#include "Console.h"
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void setCursor(int row, int col)
{
#ifdef _WIN32
    COORD coord;
    coord.X = col;
    coord.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    std::cout << "\033[" << (row + 1) << ";" << (col + 1) << "H";
    std::cout.flush();
#endif
}

void hideCursor()
{
#ifdef _WIN32
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
#else
    std::cout << "\033[?25l";
    std::cout.flush();
#endif
}

void showCursor()
{
#ifdef _WIN32
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
#else
    std::cout << "\033[?25h";
    std::cout.flush();
#endif
}
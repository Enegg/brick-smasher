#include "../headers/Common.h"
#include "windows.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void move_cursor(Window *window, int16_t x, int16_t y)
{
    COORD coord = {(SHORT)(x + window->x), (SHORT)(y + window->y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void get_console_size(Window *window)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    window->width = x > 60 ? x : 60;
    window->height = y > 30 ? y : 30;
}

void print_centered(Window *window, const char *line, uint8_t y)
{
    move_cursor(window, (window->width - strlen(line)) / 2, y);
    fputs(line, stdout);
}

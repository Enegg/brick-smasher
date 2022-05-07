#pragma once
#include <stdint.h>

enum Keys
{
    TAB = '\t',
    ENTER = 13,
    ESC = 27,
    SPACE = ' ',
    W = 'w',
    A = 'a',
    S = 's',
    D = 'd',
    P = 'p',
    R = 'R',
    R_ARROW = 'M',
    L_ARROW = 'K',
    UP_ARROW = 'H',
    DOWN_ARROW = 'P'
};

typedef struct Window
{
    uint16_t left;  // relative to console
    uint16_t right; // relative to console
    uint16_t above; // relative to console
    uint16_t below; // relative to console
    uint16_t width;
    uint16_t height;
    uint16_t x; // offset of the window
    uint16_t y; // offset of the window
} Window;

typedef struct Settings
{
    uint8_t board_width;
    uint8_t board_speed;
    uint8_t ball_speed;
    const char *board_symbol;
} Settings;

void move_cursor(uint16_t x, uint16_t y);
void move_cursor(Window *window, int16_t x, int16_t y);

void get_console_size(Window *window);

void print_centered(Window *window, const char *line, uint8_t y);

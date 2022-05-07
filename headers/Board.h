#pragma once
#include "Common.h"
#include <stdint.h>

typedef struct Board
{
    uint16_t x;
    int8_t speed;
    uint16_t width;
    const char *symbol;
} Board;

int8_t move_by(Window *window, Board *board);
void animate_board(Window *window, Board *board, int8_t dist);

#include "../headers/Board.h"
#include "../headers/Common.h"
#include <stdint.h>
#include <stdio.h>

int8_t move_by(Window *window, Board *board)
{
    if (!board->speed)
        return 0;

    const uint16_t edge = window->width - window->right - board->width;

    if (-board->speed >= board->x - window->left) // would set x_pos to <= 0
    {
        return window->left - board->x;
    }
    else if (board->x + board->speed >= edge) // would set x_pos to >= edge
    {
        return edge - board->x;
    }
    else
    {
        return board->speed;
    }
}

void animate_board(Window *window, Board *board, int8_t dist)
{
    move_cursor(window, board->x, window->height - window->below);
    for (uint8_t n = 0; n < board->width; n++)
        fputs(" ", stdout);
    move_cursor(window, board->x += dist, window->height - window->below);
    for (uint8_t i = 0; i < board->width; i++)
        fputs(board->symbol, stdout);
}

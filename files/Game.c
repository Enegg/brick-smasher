#include "../headers/Game.h"
#include "../headers/Board.h"
#include "../headers/Ball.h"
#include "../headers/Common.h"
#include "../headers/Menu.h"
#include "../headers/Vector.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

void print_blocks(Window *window, bool *blocks, uint16_t width, uint16_t height)
{
    for (uint16_t i = 0; i < height; i++)
    {
        move_cursor(window, window->width / 2 - width / 2, window->above + i);
        for (uint16_t j = 0; j < width; j++)
            fputs(*(blocks + i * width + j) ? "#" : " ", stdout);
    }
}

void game(Window *window, Vector *scores, Settings *settings)
{
    Window game_window = {3, 3, 3, 3, 66, 30, (uint16_t)((window->width - 66) / 2), (uint16_t)((window->height - 30) / 2)};
    Board board = {(uint16_t)((game_window.width - settings->board_width) / 2), 0, settings->board_width, settings->board_symbol};
    Ball ball = {(uint16_t)(game_window.width / 2), 2, 0, 0};
    bool blocks[60 * 6];

    for (uint16_t i = 0; i < 60 * 6; i++)
        blocks[i] = true;

    uint16_t score = 0;
    uint8_t health = 3;

    print_frame(&game_window, 1, 0);
    animate_board(&game_window, &board, 0);
    print_blocks(&game_window, blocks, 60, 6);

    bool running = true;
    clock_t counter, diff;
    uint8_t board_speed = settings->board_speed;
    uint8_t ball_speed = settings->ball_speed;

    while (running)
    {
        counter = clock();
        board.speed = 0;

        if (_kbhit())
        {
            switch (_getch())
            {
            case A:
            case L_ARROW:
                board.speed = -board_speed;
                break;

            case D:
            case R_ARROW:
                board.speed = board_speed;
                break;

            case W:
            case UP_ARROW:
                board_speed++;
                break;

            case S:
            case DOWN_ARROW:
                if (board_speed > 1)
                    board_speed--;
                break;

            case P:
            case ESC:
                Sleep(50);
                // pause?
                if (_getch() == ESC)
                {
                    running = false;
                };
                break;
            }
            int8_t dist = move_by(&game_window, &board);
            if (dist)
                animate_board(&game_window, &board, dist);
        }

        move_cursor(&game_window, -5, game_window.above);
        printf("%d", counter);
        diff = clock() - counter;

        if (16 - diff > 0)
            Sleep(16 - diff);
    }
    insort(scores, counter);
}

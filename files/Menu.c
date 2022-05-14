#include "../headers/Menu.h"
#include "../headers/Common.h"
#include "../headers/Vector.h"
#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

void wrap_line(Window *window, const char *line, uint8_t y, bool add)
{
    const uint8_t len = strlen(line);
    const uint16_t pos = (window->width - len) / 2;
    move_cursor(window, pos - 2, y);
    fputs(add ? "[" : " ", stdout);
    move_cursor(window, pos + len + 1, y);
    fputs(add ? "]" : " ", stdout);
}

void main_menu(Window *window, uint8_t *choice)
{
    const char lines[][50] = {
        "------------------ B L O C K Z ------------------",
        " ",
        "New game",
        "Highscores",
        "Settings",
        "Adjust the window",
        "Exit"};

    const uint8_t text_height = sizeof(lines) / sizeof(lines[0]);
    const uint8_t y_pos = (window->height - text_height) / 2;

    for (uint8_t i = 0; i < text_height; i++)
        print_centered(window, lines[i], y_pos + i);

    uint8_t curr_pos = 0;
    uint8_t prev = 1;

    while (*choice == 0)
    {
        if (curr_pos != prev)
        {
            wrap_line(window, lines[prev + 2], y_pos + prev + 2, false);
            wrap_line(window, lines[curr_pos + 2], y_pos + curr_pos + 2, true);
        }

        int key = _getch();

        switch (key)
        {
        case ESC:
            *choice = 5;
            break;

        case W:
        case UP_ARROW:
            if ((prev = curr_pos) != 0)
                curr_pos--;
            break;

        case S:
        case DOWN_ARROW:
            if ((prev = curr_pos) != text_height - 3)
                curr_pos++;
            break;

        case ENTER:
        case SPACE:
            *choice = curr_pos + 1;
            break;

        default:
            move_cursor(window, window->width / 2, 3);
            printf("        ");
            move_cursor(window, window->width / 2, 3);
            printf("%c %d", (unsigned char)key, key);
        }
    }
}

void print_frame(Window *window, uint8_t size, uint16_t duration)
{
    // top
    move_cursor(window, size, size);
    printf("%c", 218U); // ┌
    for (uint16_t x = size + 1; x < window->width - size - 1; x++)
        printf("%c", 196U); // ─
    printf("%c", 191U);     // ┐

    // sides
    const uint16_t delay = duration / window->height; // ms

    for (int y = size + 1; y < window->height - size - 1; y++)
    {
        move_cursor(window, size, y);
        printf("%c", 179U); // │
        move_cursor(window, window->width - size - 1, y);
        printf("%c", 179U); // │

        if (delay > 0)
            Sleep(delay);
    }

    // bottom
    move_cursor(window, size, window->height - size - 1);
    printf("%c", 192U); // └
    // top
    for (uint16_t x = size + 1; x < window->width - size - 1; x++)
        printf("%c", 196U); // ─
    printf("%c", 217U);     // ┘
}

void score_menu(Window *window, Vector *scores)
{
    const uint8_t num = scores->elem;
    const uint8_t x_pos = window->width / 3;
    const uint8_t y_pos = (window->height - 10) / 2;
    uint8_t page = 0;

    move_cursor(window, x_pos, y_pos + 13);
    fputs("Press ESC to go back", stdout);

    move_cursor(window, x_pos, y_pos + 12);
    fputs("Use \"A\" and \"D\" to change page", stdout);
    bool refresh = true;

    while (true)
    {
        if (refresh)
        {
            const uint8_t pos = page * 10;

            for (int i = 0; i < 10; i++)
            {
                move_cursor(window, x_pos, y_pos + i);
                fputs("          ", stdout);
                move_cursor(window, x_pos, y_pos + i);
                if (pos + i < num)
                {
                    printf("%d. %d", pos + i + 1, scores->ptr[pos + i]);
                }
                else
                {
                    printf("%d.", pos + i + 1);
                }
            }

            refresh = false;
        }

        switch (_getch())
        {
        case A:
        case L_ARROW:
            if (page != 0)
            {
                page--;
                refresh = true;
            }
            break;

        case D:
        case R_ARROW:
            if ((page + 1) * 10 + 1 <= num)
            {
                page++;
                refresh = true;
            }
            break;

        case ESC:
            return;
        }
    }
}

void settings_menu(Window *window, Settings *settings)
{
    const char text[][35] = {
        "------ Settings ------",
        "Board width: ",
        "Board speed: ",
        "Ball speed: "
    };

    const uint8_t height = sizeof(text) / sizeof(text[0]);
    const uint8_t y_offset = (window->height - height) / 2;
    const uint8_t x_offset = (window->width - 35) / 2;

    for (uint8_t i = 0; i < height; i++)
    {
        move_cursor(window, x_offset, y_offset + i);
        fputs(text[i], stdout);
    }

    move_cursor(window, x_offset + strlen(text[2]), y_offset + 2);
    fprintf(stdout, "%d", settings->board_speed);
    move_cursor(window, x_offset + strlen(text[3]), y_offset + 3);
    fprintf(stdout, "%d", settings->ball_speed);
    move_cursor(window, x_offset + strlen(text[1]), y_offset + 1);
    for (uint8_t i = 0; i < settings->board_width; i++)
        fputs(settings->board_symbol, stdout);

    uint8_t option = 0;

    while (true)
    {
        int8_t inc = 0;
        switch (_getch())
        {
            case W:
            case UP_ARROW:
                if (option != 0)
                    option--;
                break;

            case S:
            case DOWN_ARROW:
                if (option != 2)
                    option++;
                break;

            case A:
            case L_ARROW:
                inc = -1;
                break;

            case D:
            case R_ARROW:
                inc = 1;
                break;

            case ESC:
                return;
        }

        switch (option)
        {
            case 0:
                if (2 <= settings->board_width + inc && settings->board_width + inc <= 16)
                    settings->board_width += inc;
                move_cursor(window, x_offset + strlen(text[1]) + settings->board_width, y_offset + 1);
                fputs(" ", stdout);
                move_cursor(window, x_offset + strlen(text[1]), y_offset + 1);
                for (uint8_t i = 0; i < settings->board_width; i++)
                    fputs(settings->board_symbol, stdout);
                break;

            case 1:
                if (1 <= settings->board_speed + inc)
                    settings->board_speed += inc;
                move_cursor(window, x_offset + strlen(text[2]), y_offset + 2);
                fputs("  ", stdout);
                move_cursor(window, x_offset + strlen(text[2]), y_offset + 2);
                fprintf(stdout, "%d", settings->board_speed);
                break;

            case 2:
                if (1 <= settings->ball_speed + inc)
                    settings->ball_speed += inc;
                move_cursor(window, x_offset + strlen(text[3]), y_offset + 3);
                fputs("  ", stdout);
                move_cursor(window, x_offset + strlen(text[3]), y_offset + 3);
                fprintf(stdout, "%d", settings->ball_speed);
        }
    }
}
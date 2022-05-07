#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "headers/Menu.h"
#include "headers/Game.h"
#include "headers/Common.h"
#include "headers/Vector.h"
#include <stdint.h>
#include <stdbool.h>

int main()
{
    Window window = {3, 3, 3, 3};
    Settings settings = {8, 1, 1, "="};
    fputs("Adjust console size and then press a key...", stdout);
    _getch();
    move_cursor(&window, 0, 0);
    for (uint8_t i = 0; i < 44; i++)
        fputs(" ", stdout);
    get_console_size(&window);

    Vector scores;
    init(&scores, 10);

    while (true)
    {
        uint8_t choice = 0;
        system("cls");
        print_frame(&window, 1, 250);
        main_menu(&window, &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            print_frame(&window, 1, 250);
            game(&window, &scores, &settings);
            break;

        case 2:
            system("cls");
            print_frame(&window, 1, 250);
            score_menu(&window, &scores);
            break;

        case 3:
            system("cls");
            print_frame(&window, 1, 250);
            settings_menu(&window, &settings);
            break;

        case 4:
            // resize console
            get_console_size(&window);
            break;

        case 5:
            return 0;
        }
    }
}

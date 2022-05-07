#pragma once
#include "windows.h"
#include "Common.h"
#include "Vector.h"
#include <stdint.h>

void main_menu(Window *window, uint8_t *choice);

void print_frame(Window *window, uint16_t size, uint16_t duration);

void score_menu(Window *window, Vector *scores);

void settings_menu(Window *window, Settings *settings);

#pragma once
#include "Common.h"
#include <stdint.h>

typedef struct Ball
{
    uint16_t x_pos;
    uint16_t y_pos;
    int8_t x_speed;
    int8_t y_speed;

} Ball;

void move_ball_by(Ball *, Window *, int16_t *, int16_t *);

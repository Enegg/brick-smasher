#pragma once
#include <stdint.h>

typedef struct Vector
{
    uint16_t *ptr;
    uint8_t size;
    uint8_t elem;
} Vector;

errno_t init(Vector *vector, uint8_t size);
errno_t append(Vector *vector, uint16_t value);
void sort(Vector *vector);
errno_t insort(Vector *vector, uint16_t value);

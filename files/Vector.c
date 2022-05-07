#include "../headers/Vector.h"
#include <stdint.h>
#include <stdlib.h>

// initialize vector
errno_t init(Vector *vector, uint8_t size)
{
    vector->ptr = (uint16_t *)calloc(size, sizeof(uint16_t));

    if (vector->ptr == NULL)
    {
        return -1;
    }

    vector->size = size;
    vector->elem = 0;
    return 0;
}

// appends a value to the vector, extending it if necessary
errno_t append(Vector *vector, uint16_t value)
{
    if (vector->elem == vector->size)
    {
        uint16_t *ptr = (uint16_t *)realloc(vector->ptr, sizeof(uint16_t) * (vector->size + 10));

        if (ptr == NULL)
        {
            return -1;
        }

        vector->ptr = ptr;
        vector->size += 10;
    }
    vector->ptr[vector->elem++] = value;
    return 0;
}

// sorts a vector
void sort(Vector *vector)
{
    uint8_t temp = vector->ptr[0];

    for (uint8_t i = 1; i < vector->elem; i++)
    {
        for (uint8_t j = i; j < vector->elem; j++)
            if (vector->ptr[j] > temp)
            {
                vector->ptr[i-1] = vector->ptr[j];
                vector->ptr[j] = temp;
                break;
            }
        temp = vector->ptr[i];
    }
}

// helper for insort
uint8_t binary_find_near_index(uint16_t *container, uint16_t *value, uint8_t start, uint8_t end)
{
    uint8_t index = (start + end) / 2;

    if (end - start <= 1)
        return index;

    if (container[index] < *value)
        return binary_find_near_index(container, value, start, index);

    if (container[index] > *value)
        return binary_find_near_index(container, value, index, end);

    return index;
}

// inserts a value, keeping the vector sorted
errno_t insort(Vector *vector, uint16_t value)
{
    uint8_t place = binary_find_near_index(vector->ptr, &value, 0, vector->elem);

    if (vector->elem == vector->size)
    // need to reallocate
    {
        uint16_t *ptr = (uint16_t *)realloc(vector->ptr, sizeof(uint16_t) * (vector->size + 10));

        if (ptr == NULL)
        {
            return -1;
        }

        vector->ptr = ptr;
        vector->size += 10;
    }

    for (uint8_t i = vector->elem; i > place; i--)
        vector->ptr[i] = vector->ptr[i-1];

    vector->ptr[place] = value;
    vector->elem++;
    return 0;
}

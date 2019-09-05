#include "my_swap.h"
#include "my_const.h"

void quick_sort(int *array, int length)
{
    int *pivot = array + length - 1;
    int *cursor = array;
    int *highest = array;
    int size;

    if (array == NULL || length <= 1)
    {
        return;
    }

    while (cursor < array + length - 1)
    {
        if (*pivot >= *cursor)
        {
            my_swap(highest, cursor);
            highest++;
        }
        ++cursor;
    }
    my_swap(highest, pivot);
    
    size = highest - array;
    quick_sort(array, size);
    quick_sort(highest + 1, length - size - 1);
}


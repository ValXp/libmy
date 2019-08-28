#include <stdlib.h>
#include "my_heap.h"
#include "my_swap.h"
#include "my_printf.h"

t_my_heap* init_heap(int size)
{
    t_my_heap* heap;

    heap = (t_my_heap*)malloc(sizeof(*heap));
    heap->array = (int*)malloc(sizeof(int) * size);
    heap->length = size;
    heap->end = -1;
    return heap;
}

void bubble_down(t_my_heap* heap, int position)
{
    int child;
    int smallest_child;
    int i;

    child = position * 2;
    if (child > heap->end)
    {
        return;
    }
    smallest_child = position;
    for (i = 0; i <= 1; ++i)
    {
        if (heap->array[smallest_child] > heap->array[child + i])
        {
            smallest_child = child + i;
        }
    }

    if (position != smallest_child)
    {
        my_swap(heap->array + position, heap->array + smallest_child);
        bubble_down(heap, smallest_child);
    }
}

void bubble_up(t_my_heap* heap, int position)
{
    int parent;

    parent = position / 2;
    if (parent >= 0)
    {
        if (heap->array[parent] > heap->array[position])
        {
            my_swap(heap->array + parent, heap->array + position);
            bubble_up(heap, parent);
        }
    }
}

void insert_item(t_my_heap* heap, int item)
{
    heap->array[++heap->end] = item;
    bubble_up(heap, heap->end);
}


int pop_minimum(t_my_heap* heap)
{
    int minimum;

    if (heap->end > -1)
    {
        minimum = heap->array[0];
        heap->array[0] = heap->array[heap->end];
        heap->end--;
        bubble_down(heap, 0);
        return minimum;
    }
    return -1;
}

int check_valid_internal(t_my_heap* heap, int position)
{
    int left, right, parent;

    left = position * 2;
    right = left + 1;
    parent = position / 2;

    if (position > heap->end)
    {
        return 1;
    }

    if (heap->array[parent] > heap->array[position])
    {
        return 0;
    }
    return check_valid_internal(heap, left) && check_valid_internal(heap, right);
}

int check_valid(t_my_heap* heap)
{
    return check_valid_internal(heap, 1) && check_valid_internal(heap, 2);
}

void print_heap(t_my_heap* heap)
{
    int i = 0;

    my_printf("Heap max length is %d.\nIt contains %d elements. \nThe heap is %s.\n",
        heap->length, heap->end + 1, check_valid(heap) == 1 ? "valid" : "invalid");

    if (heap->end > -1)
    {
        my_printf("{");
        for (i = 0; i < heap->end; ++i)
        {
            my_printf("%d, ", heap->array[i]);
        }
        my_printf("%d}\n", heap->array[heap->end]);
    }
}

void heap_sort(int *array, int length)
{
    t_my_heap* heap;
    int i;

    heap = init_heap(length);
    for (i = 0; i < length; ++i)
    {
        insert_item(heap, array[i]);
    }
    for (i = 0; i < length; ++i)
    {
        array[i] = pop_minimum(heap);
    }

}


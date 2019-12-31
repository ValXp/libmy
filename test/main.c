#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "my_puts.h"
#include "my_put_number.h"
#include "my_printf.h"
#include "my_read_int.h"
#include "my_strcmp.h"
#include "my_read_line.h"
#include "term_tools.h"
#include "my_qsort.h"
#include "my_heap.h"

void printArray(int *array, int size)
{
    int i;

    my_printf("{");
    for (i = 0; i < size - 1; ++i)
    {
        my_printf("%d, ", array[i]);
    }
    if (size > 0)
    {
        my_printf("%d}\n", array[size - 1]);
    }
    else
    {
        my_printf("}\n");
    }
}


int *getRandomArray(int size, int min, int max)
{
    int *array;
    int i;

    array = (int*)malloc(sizeof(*array) * size);
    for (i = 0; i < size; ++i)
    {
        array[i] = random() % (max - min) + min;
    }
    return array;
}

int is_sorted(int *array, int length)
{
    int i;

    for (i = 0; i < length - 1; ++i)
    {
        if (array[i] > array[i + 1])
        {
            return 0;
        }
    }
    return 1;
}


void bubble_sort(int *array, int length)
{
    int i, j;
    int swapped = 1;

    while (swapped)
    {
        swapped = 0;
        for (i = 0; i < length - 1; ++i)
        {
            if (array[i] > array[i + 1])
            {
                my_swap(array + i, array + i + 1);
                swapped = 1;
            }
        }
    }
}

void test_heapsort(int testCount, int testSize)
{
    int **test_table;
    int i;
    clock_t start, end;

    my_printf("Allocating %d MB of memory\n", (testCount * testSize * sizeof(int)) / (1024 * 1024));
    test_table = (int**)malloc(sizeof(*test_table) * testCount);
    for (i = 0; i < testCount; ++i)
    {
        test_table[i] = getRandomArray(testSize, -1000000, 1000000);
    }

    my_printf("Starting test now\n");
    start = clock();

    for (i = 0; i < testCount; ++i)
    {
        heap_sort(test_table[i], testSize);
        if (!is_sorted(test_table[i], testSize))
        {
            printf("Sort failed!\n");
            return;
        }
    }

    end = clock();

    printf("Test took %f seconds for %d runs of heap sort on %d sized arrays.\n", (double)(end - start) / CLOCKS_PER_SEC, testCount, testSize);

    for (i = 0; i < testCount; ++i)
    {
        free(test_table[i]);
    }
    free(test_table);
}

void test_quicksort(int testCount, int testSize)
{
    int **test_table;
    int i;
    clock_t start, end;

    my_printf("Allocating %d MB of memory\n", (testCount * testSize * sizeof(int)) / (1024 * 1024));
    test_table = (int**)malloc(sizeof(*test_table) * testCount);
    for (i = 0; i < testCount; ++i)
    {
        test_table[i] = getRandomArray(testSize, -1000000, 1000000);
    }

    my_printf("Starting test now\n");
    start = clock();

    for (i = 0; i < testCount; ++i)
    {
        quick_sort(test_table[i], testSize);
        if (!is_sorted(test_table[i], testSize))
        {
            printf("Sort failed!\n");
            return;
        }
    }

    end = clock();

    printf("Test took %f seconds for %d runs of quick sort on %d sized arrays.\n", (double)(end - start) / CLOCKS_PER_SEC, testCount, testSize);

    for (i = 0; i < testCount; ++i)
    {
        free(test_table[i]);
    }
    free(test_table);
}

void test_bubblesort(int testCount, int testSize)
{
    int **test_table;
    int i;
    clock_t start, end;

    my_printf("Allocating %d MB of memory\n", (testCount * testSize * sizeof(int)) / (1024 * 1024));
    test_table = (int**)malloc(sizeof(*test_table) * testCount);
    for (i = 0; i < testCount; ++i)
    {
        test_table[i] = getRandomArray(testSize, -1000000, 1000000);
    }

    my_printf("Starting test now\n");
    start = clock();

    for (i = 0; i < testCount; ++i)
    {
        bubble_sort(test_table[i], testSize);
        if (!is_sorted(test_table[i], testSize))
        {
            printf("Sort failed!\n");
            return;
        }
    }

    end = clock();

/* TODO: Add %f to my_printf */
    printf("Test took %f seconds for %d runs of bubble sort on %d sized arrays.\n", (double)(end - start) / CLOCKS_PER_SEC, testCount, testSize);

    for (i = 0; i < testCount; ++i)
    {
        free(test_table[i]);
    }
    free(test_table);
}


int AddOne(int a)
{
    int cur = 1;

    while (a & cur)
    {
        a = a & ~cur;
        cur = cur << 1;
    }
    return a | cur;
}
int RemoveOne(int a)
{
    int cur = 1;

    while (!(a & cur))
    {
        a = a | cur;
        cur = cur << 1;
    }
    return a & ~cur;
}

int Add(int a, int b)
{
    while (b)
    {
        a = AddOne(a);
        b = RemoveOne(b);
    }
    return a;
}

int Mult(int a, int b)
{
    int c = 0;
    while (b)
    {
        c = Add(c, a);
        b = RemoveOne(b);
    }
    return c;
}

int revDig(int toRev)
{
    int res = 0;
    while (toRev)
    {
        res *= 10;
        res += toRev % 10;
        toRev /= 10;
    }
    return res;
}

int isPalindrome(int value)
{
    return value == revDig(value);
}

void checkPalindrome(int value)
{
    printf("isPalindrome: %d %s\n", value, isPalindrome(value) ? "true" : "false");
}

int randGen(int binRandom, int min, int max)
{
    static unsigned int accum = 0;
    accum <<= 1;
    accum |= binRandom;
    return (accum % (max - min)) + min;
}

void test(int min, int max)
{
    int rand = (int)random() % 2;
    printf("Bin random to [%d;%d] %d -> %d\n", min, max, rand, randGen(rand, min, max));
}

void qsort2(int *array, int length, int pivot)
{
    int *biggest = array;
    int *cursor = array;
    int *pivo = array + length - 1;
    int val = array[pivot];

    my_swap(array + pivot, pivo);
    while (cursor < array + length - 1)
    {
        printArray(array, length);
        printf("is cursor[%d] <= [%d]\n", *cursor, *pivo);
        if (*cursor <= *pivo)
        {
            my_swap(biggest, cursor);
            ++biggest;
        }
        ++cursor;
    }
    printArray(array, length);
    my_swap(biggest, pivo);
    printArray(array, length);
    pivo = biggest;
    while (*pivo == val && pivo >= array)
    {
        --pivo;
    }
    biggest = pivo - 1;
    while (biggest >= array)
    {
        if (*biggest == val)
        {
            my_swap(biggest, pivo);
            --pivo;
        }
        --biggest;
    }
}

typedef struct
{
    int *data;
    int length;
} array;

void resize(array* arr)
{
    arr->data = realloc(arr->data, arr->length * 2 * sizeof(int));
    arr->length *= 2;
}

array* initArr(int length)
{
    array *arr;

    arr = malloc(sizeof(*arr));
    arr->length = length;
    arr->data = calloc(length, sizeof(int));
    return arr;
}

void reverseArray(array* arr, int end)
{
    int cur = 0;

    while (cur < end)
    {
        my_swap(arr->data + cur, arr->data + end);
        ++cur;
        --end;
    }
}

array* mult(array* a, array*b)
{
    array *c;
    int curA, curB, curC;
    int idxA, idxB;

    c = initArr(a->length + b->length);
    for (curA = 0; curA < a->length; ++curA)
    {
        idxA = a->length - 1 - curA;
        for (curB = 0; curB < b->length; ++curB)
        {
            idxB = b->length - 1 - curB;
            curC = curA + curB;

            c->data[curC] += a->data[idxA] * b->data[idxB];
            if (c->data[curC] > 9)
            {
                if (curC >= c->length)
                {
                    printf("Realloc!\n");
                    resize(c);
                }
                c->data[curC + 1] += c->data[curC] / 10;
                c->data[curC] %= 10;
            }
        }
    }
    reverseArray(c, c->data[curC + 1] ? curC + 1 : curC);
    return c;
}

array *createArrayFromValue(int value)
{
    int digits;
    array *arr;
    int cur;

    digits = (int)log10(value) + 1;
    arr = initArr(digits);
    cur = digits - 1;
    while (value)
    {
        arr->data[cur] = value % 10;
        value /= 10;
        --cur;
    }
    return arr;
}

void printArr(array *arr)
{
    int i;

    printf("Length: %d\n", arr->length);
    for(i = 0; i < arr->length; ++i)
    {
        printf("%d", arr->data[i]);
    }
    printf("\n");
}

void test1()
{
    array *a, *b, *c;

    a = createArrayFromValue(999999);
    b = createArrayFromValue(999999);

    printArr(a);
    printArr(b);

    c = mult(a, b);

    printArr(c);

}

float my_sqrt(float a)
{
    float midpoint = 0;
    int iter = 1;
    /* if a > 1 then root is smaller than a */
    if (a > 1)
    {
        midpoint = 0;
    }
    else if (a == 1)
    {
        return 1;
    }
    /* a < 1 so root is bigger than a */
    else
    {
        midpoint = 0;
    }
    /* we compute the midpoint between 1 and a */
    while (fabs(midpoint * midpoint - a) > 0.00001)
    {
        iter *= 2;
        /* we need to go smaller */
        if (midpoint * midpoint > a)
        {
            midpoint -= a / iter;
        }
        /* we need to go bigger */
        else
        {
            midpoint += a / iter;
        }
    }
    return midpoint;
}

void test_sqrt(float val)
{
    printf("sqrt(%f) == %f == %f\n", val, my_sqrt(val), sqrt(val));
}

void test2()
{
    test_sqrt(25);
    test_sqrt(25);
    test_sqrt(35);
    test_sqrt(26);
    test_sqrt(212316.23434523);
}

int main()
{
    int i;
    int res;
    char *input;
    int* array;
    int arraySize = 20;
    t_my_heap* heap;

    struct termios terminal;

    srandom(time(0));

test2();
return 0;
/*
    heap = init_heap(10);
    insert_item(heap, 42);
    insert_item(heap, 2);
    insert_item(heap, 52);
    insert_item(heap, 3);
    insert_item(heap, 12);
    insert_item(heap, 30);
    insert_item(heap, 1);

    print_heap(heap);

    my_printf("sort result:\n");
    while (heap->end >= 0)
    {
        my_printf("%d,\n ", pop_minimum(heap));
        print_heap(heap);
    }
    delete_heap(heap);
*/
/*    test_quicksort(100, 400000);
    test_heapsort(100, 400000);
    */
    /*test_bubblesort(20, 400);*/

    /*array = getRandomArray(arraySize, 0, 5);
    printf("Before sort [%d]: \n", array[1]);
    printArray(array, arraySize);
    qsort2(array, arraySize, 1);
    printf("After sort:\n");
    printArray(array, arraySize);
*/


    return 0;

    if (save_terminal(&terminal))
    {
        my_printf("Error retrieving terminal info.\n");
        exit(1);
    }

    terminal.c_lflag &= ~ICANON;
    terminal.c_lflag &= ~ECHO;


    if (set_terminal(&terminal))
    {
        my_printf("Error setting terminal info.\n");
        exit(1);
    }


    input = NULL;
    do
    {
        free(input);
        my_printf("Please type anything (exit to quit):\n$>");
        input = my_read_line();
        my_printf("You typed: \"%s\"\n", input == NULL ? "NULL" : input);
    } while (input == NULL || my_strcmp("exit", input));





    if (restore_terminal())
    {
        my_printf("Error resetting terminal info.\nA reset might be necessary\n");
        exit(1);
    }


    my_printf("Done!\n");
    
    return 0;
}


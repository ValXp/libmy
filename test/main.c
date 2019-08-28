#include <unistd.h>
#include <stdlib.h>

#include "my_puts.h"
#include "my_put_number.h"
#include "my_printf.h"
#include "my_read_int.h"
#include "my_strcmp.h"
#include "my_read_line.h"
#include "term_tools.h"
#include "my_qsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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


int test_quicksort(int testCount, int testSize)
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
    }

    end = clock();

    printf("Test took %f seconds for %d runs of quick sort on %d sized arrays.\n", (double)(end - start) / CLOCKS_PER_SEC, testCount, testSize);
}

int test_bubblesort(int testCount, int testSize)
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
    }

    end = clock();

/* TODO: Add %f to my_printf */
    printf("Test took %f seconds for %d runs of bubble sort on %d sized arrays.\n", (double)(end - start) / CLOCKS_PER_SEC, testCount, testSize);
}

void printArray(int *array, int size)
{
    int i;

    my_printf("{");
    for (i = 0; i < size - 1; ++i)
    {
        my_printf("%d, ", array[i]);
    }
    my_printf("%d}\n", array[size - 1]);
}


int main(int ac, char **av)
{
    int i;
    int res;
    char *input;
    int* array;
    int arraySize = 1000;

    struct termios terminal;

    srandom(time(0));

    test_quicksort(1, 40000);
    test_bubblesort(1, 40000);

    /*array = getRandomArray(arraySize, -100, 100);
    printf("Before sort:\n");
    printArray(array, arraySize);
    bubble_sort(array, arraySize);
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


#ifndef MY_HEAP_H_
# define MY_HEAP_H_

typedef struct  s_my_heap
{
    unsigned int    length;
    int*            array;
    int             end;
}               t_my_heap;


t_my_heap* init_heap(int size);
void delete_heap(t_my_heap* heap);
void insert_item(t_my_heap* heap, int item);
int pop_minimum(t_my_heap* heap);
int check_valid(t_my_heap* heap);
void print_heap(t_my_heap* heap);
void heap_sort(int *array, int length);

#endif /* MY_HEAP_H_ */


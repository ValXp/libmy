#ifndef MY_PRINTF_H_
# define MY_PRINTF_H_

void my_printf(const char *format, ...);

typedef struct  my_buffer_s
{
    int length;
    int cursor;
    char *buffer;
}               my_buffer_t;

# define BUFFER_SIZE_STEP 512

#endif /* MY_PRINTF_H_*/


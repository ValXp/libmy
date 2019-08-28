#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#include "my_printf.h"
#include "my_puts.h"
#include "my_strlen.h"
#include "my_int_to_str.h"
#include "my_strcpy.h"
#include "my_put_number.h"


void buffer_ensure_available(my_buffer_t *buffer, int available)
{
    int mult;
    int needed = buffer->cursor + available + 1;
    if (buffer->length <= needed) 
    {
        mult = (needed % BUFFER_SIZE_STEP) + 1;
        buffer->length = BUFFER_SIZE_STEP * mult;
        buffer->buffer = realloc(buffer->buffer, buffer->length * sizeof(*(buffer->buffer)));
    }
}

void buffer_append(my_buffer_t *buffer, const char *data, int count)
{
    buffer_ensure_available(buffer, count);
    my_strncpy(buffer->buffer + buffer->cursor, data, count);
    buffer->cursor += count;
}

void consume_argument(va_list ap, const char **format, my_buffer_t *buffer)
{
    char id = **format;
    char *s_arg;
    int d_arg;
    int digits;
    switch (id)
    {
        /* "%%" prints "%" */
        case '%':
            buffer_append(buffer, &id, 1);
        break;
        case 's':
            s_arg = va_arg(ap, char*);
            buffer_append(buffer, s_arg, my_strlen(s_arg));
        break;
        case 'd':
            d_arg = va_arg(ap, int);
            digits = my_int_to_str_count_digits(d_arg);
            buffer_ensure_available(buffer, digits);
            my_int_to_str_s(d_arg, buffer->buffer + buffer->cursor, digits);
            buffer->cursor += digits;
        break;
    }
    (*format)++;
}

void my_printf(const char *format, ...)
{
    va_list ap;
    char o;
    my_buffer_t *buffer;
    va_start(ap, format);
    buffer = (my_buffer_t*)calloc(1, sizeof(my_buffer_t));
    while (*format != '\0')
    {
        if (*format != '%')
        {
            buffer_append(buffer, format, 1);
            ++format;
        }
        else
        {
            ++format;
            consume_argument(ap, &format, buffer);
        }
    }
    o = '\0';
    buffer_append(buffer, &o, 1); 
    my_puts(buffer->buffer);
    free(buffer->buffer);
    free(buffer);
}



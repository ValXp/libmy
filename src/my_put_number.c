#include <stdlib.h>
#include "my_const.h"
#include "my_put_number.h"
#include "my_int_to_str.h"
#include "my_puts.h"


void my_put_number(int number)
{
    char *str = my_int_to_str(number);
    if (str != NULL)
    {
        my_puts(str);
        free(str);
    }
}


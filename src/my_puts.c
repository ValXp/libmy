#include <unistd.h>
#include "my_puts.h"
#include "my_strlen.h"

void my_puts(const char *str)
{
    write(1, str, my_strlen(str));
}


#include <unistd.h>

#define READ_BUFFER_SIZE 16

int my_read_int()
{
    char buffer[READ_BUFFER_SIZE];
    int number = 0;
    int read_count = 0;
    int is_first = 1;
    int sign = 1;
    int done = 0;
    int i;
    int operand;
    while (!done && (read_count = read(0, buffer, READ_BUFFER_SIZE)))
    {
        for (i = 0; !done && i < read_count; ++i)
        {
            if (is_first && buffer[i] == '-')
            {
                sign = -1;
            }
            else if (buffer[i] < '0' || buffer[i] > '9')
            {
                done = 1;
            }
            else
            {
                /* Check for overflow */
                if (number >= 0 && number * 10 < number)
                {
                    done = 1;
                }
                else
                {
                    number *= 10;
                    operand = buffer[i] - '0';
                    /* Check for overflow */
                    if (operand < 0 || number < 0 || (int)(operand + number) >= number)
                    {
                        number += buffer[i] - '0';
                    }
                    else
                    {
                        done = 1;
                    }
                }
            }
            is_first = 0;
        }
    }
    return sign * number;
}

#include <stdlib.h>
#include "my_pow.h"
#include "my_const.h"

int my_int_to_str_count_digits(int number)
{
    int isNegative = 0;
    int counter;
    int digits;

    if (number < 0)
    {
        isNegative = 1;
        number *= -1;
    }
    counter = number;
    digits = 0;
    if (isNegative || number == 0)
    {
        digits++;
    }

    /* Calculate how many digits we have */
    while (counter > 0)
    {
        ++digits;
        counter = counter / 10;
    }
    return digits;
}

void my_int_to_str_s(int number, char *str, int digits)
{
    int isNegative, i, pow, pow2, curNum, num, digit;
    char c;

    isNegative = 0;
    if (number < 0)
    {
        isNegative = 1;
        number *= -1;
    }

    /* Go through all digits */
    i = 0;
    for (digit = digits - 1; digit >= 0; --digit)
    {
        pow = my_pow(i + 1, 10);
        pow2 = my_pow(i, 10);
        curNum = number / pow2;
        num = curNum - ((curNum / 10) * 10);
        c = (char)num + '0';
        str[digit] = c;
        ++i;
    }
    if (isNegative)
    {
        str[0] = '-';
    }
}

char *my_int_to_str(int number)
{
    int digits;
    char *str;
    
    digits = my_int_to_str_count_digits(number);

    /* + 1 in size because of '/0' */
    str = (char*)malloc(sizeof(char) * (digits + 1));
    if (str == NULL)
    {
        return NULL;
    }

    my_int_to_str_s(number, str, digits);
    str[digits] = '\0';

    return str;
}



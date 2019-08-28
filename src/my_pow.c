#include "my_pow.h"

int my_pow(int n, int mult)
{
    int accum = 1;
    int i;
    for (i = 0; i < n; ++i)
    {
        accum *= mult;
    }
    return accum;
}


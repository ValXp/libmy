
int my_strcmp(const char *left, const char *right)
{
    while (*left && *right && *left == *right)
    {
        ++left;
        ++right;
    }
    return *left - *right;
}



void my_strcpy(char *dest, const char *src)
{
    while (*src)
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = 0;
}

void my_strncpy(char *dest, const char *src, int count)
{
    int i = 0;
    for (i = 0; i < count && src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }
    for (;i < count;++i)
    {
        dest[i] = '\0';
    }
}


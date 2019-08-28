#include <unistd.h>
#include <stdlib.h>

#define READ_BUFFER_SIZE 64

char *my_read_line()
{
    char buffer[READ_BUFFER_SIZE];
    int size = 0;
    char *target = NULL;
    int cursor = 0;
    int read_count = 0;
    int done = 0;
    int i;
    while (!done && (read_count = read(0, buffer, READ_BUFFER_SIZE)))
    {
        for (i = 0; !done && i < read_count; ++i)
        {
            if (buffer[i] == '\n' || buffer[i] == '\0')
            {
                done = 1;
                break;
            }
            else
            {
                if (cursor >= size)
                {
                    size += 64;
                    target = (char*)realloc(target, sizeof(*target) * size);
                }
                target[cursor] = buffer[i];
                cursor++;
            }
        }
    }
    if (cursor >= size)
    {
        size++;
        target = (char*)realloc(target, sizeof(*target) * size);
    }
    target[cursor] = 0;
    return target;
}

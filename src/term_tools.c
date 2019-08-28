
#include "term_tools.h"


struct termios g_term_stack[TERM_STACK_SIZE];
struct termios *g_stack_loc;


int save_terminal(struct termios *term)
{
    if (g_stack_loc == 0)
    {
        g_stack_loc = g_term_stack;
    }
    /* Overflow. Stack is too small */
    if (g_stack_loc - g_term_stack >= TERM_STACK_SIZE)
    {
        return -1;
    }
    /* Can't retrieve terminfo */
    if (tcgetattr(0, g_stack_loc++))
    {
        return -2;
    }
    if (term != NULL)
    {
        *term = *(g_stack_loc - 1);
    }
    return 0;
}

int restore_terminal()
{
    /* Stack is empty */
    if (g_stack_loc == 0 || g_stack_loc <= g_term_stack)
    {
        return -1;
    }
    /* Can't set terminfo */
    if (tcsetattr(0, TCSANOW, --g_stack_loc))
    {
        return -2;
    }
    return 0;
}


int set_terminal(struct termios *term)
{
    return tcsetattr(0, TCSANOW, term);
}


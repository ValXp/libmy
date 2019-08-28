#ifndef TERM_TOOLS_H_
# define TERM_TOOL_H_

# include <stddef.h>
# include <termios.h>
# define TERM_STACK_SIZE 512

/*
* Saves the current terminal onto a stack.
* *term arg is optional. On success it will be populated with the saved terminal
* Return values:
* 0     -> Success
* -1    -> Stack full
* -2    -> Can't retrieve terminfo
*/
int save_terminal(struct termios *term);

/*
* Restores the terminal from the stack.
* Return values:
* 0     -> Success
* -1    -> Stack empty
* -2    -> Can't set terminfo
*/
int restore_terminal();


int set_terminal(struct termios *term);

#endif /* TERM_TOOLD_H_ */


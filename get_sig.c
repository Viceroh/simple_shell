#include "viceroh.h"

/**
* get_sign_int - Handles and controls c prompt
* @sig: Signal handlers
*/
void get_sign_int(int sig)
{
(void)sig;
write(STDOUT_FILENO, "\n^-^ ", 5);
}

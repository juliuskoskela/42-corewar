#include <stdio.h>
#include <stdlib.h>

void	asm_exit_error(char *msg)
{
	perror(msg);
	exit(1);
}

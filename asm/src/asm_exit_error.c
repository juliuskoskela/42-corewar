#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include "core.h"

void	asm_exit_error(char *msg)
{
	if (msg != NULL && errno != 0)
		perror(msg);
	else if (msg != NULL)
		print_fd(2, "%s\n", msg);
	exit(1);
}

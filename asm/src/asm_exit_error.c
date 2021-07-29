#include <stdlib.h>
#include "core.h"

void	asm_exit_error(char *msg)
{
	if (msg != NULL)
		perror(msg);
	exit(1);
}

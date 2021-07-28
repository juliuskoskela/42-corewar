#include "argparser.h"
#include <stdlib.h>
#include <stdio.h>

void	_argparser_print_usage(t_argparser_state *state)
{
	if (state->root_argp->args_doc == NULL)
	{
		dprintf(2, "Usage: %s [OPTION...]\n", state->name);
	}
	else
	{
		dprintf(2, "Usage: %s [OPTION...] %s\n",
			state->name, state->root_argp->args_doc);
	}
}

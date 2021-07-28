#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>
#include <stdio.h>

void	argparser_usage(t_argparser_state *state)
{
	_argparser_print_usage(state);
	dprintf(2, "Try `%s --help` or `%s --usage` for more information.\n",
		state->name, state->name);
	exit(ARGP_EXIT_PARSE_ERROR);
}

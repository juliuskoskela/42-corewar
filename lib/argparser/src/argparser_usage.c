#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>
#include "core.h"

void	argparser_usage(t_argparser_state *state)
{
	_argparser_print_usage(state);
	print_fd(2, "Try `%s --help` or `%s --usage` for more information.\n",
		state->name, state->name);
	exit(ARGP_EXIT_PARSE_ERROR);
}

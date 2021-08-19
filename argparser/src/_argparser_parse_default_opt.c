#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>

int	_argparser_parse_default_opt(int key, char *arg, t_argparser_state *state)
{
	if (key == 1)
	{
		_argparser_help(state);
	}
	else if (key == 2)
	{
		_argparser_long_usage(state);
	}
	else if (key == ARGP_KEY_ARG && arg != NULL)
	{
		argparser_usage(state);
	}
	else if (key == ARGP_KEY_END)
	{
		return (0);
	}
	else
	{
		return (ARGP_ERR_UNKNOWN);
	}
	return (0);
}

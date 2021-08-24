#include "argparser.h"
#include "argparser_internal.h"

int	_argparser_parse_argument(const t_argparser *argp,
t_argparser_state *state)
{
	int			key;
	char		*arg;

	key = ARGP_KEY_ARG;
	arg = state->argv[state->next];
	if (argp->parser(key, arg, state) == ARGP_ERR_UNKNOWN)
		return (0);
	state->arg_num = state->arg_num + 1;
	state->next = state->next + 1;
	return (1);
}

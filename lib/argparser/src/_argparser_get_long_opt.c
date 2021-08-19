#include "argparser_internal.h"
#include <stdlib.h>

int	_argparser_get_long_opt(int *key, char **arg,
const t_argparser *argp, t_argparser_state *state)
{
	const t_argparser_option	*option;

	option = _argparser_get_option(&state->argv[state->next][2],
			argp->options, 1);
	if (option == NULL)
		return (0);
	*key = option->key;
	if (option->arg != NULL)
	{
		*arg = _argparser_get_arg(state);
		if (*arg == NULL
			&& (((unsigned int)option->flags) & OPTION_ARG_OPTIONAL) == 0)
			return (0);
	}
	return (1);
}

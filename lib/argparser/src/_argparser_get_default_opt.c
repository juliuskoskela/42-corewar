#include "argparser_internal.h"
#include <stdlib.h>

int	_argparser_get_default_opt(int *key, char **arg,
t_argparser_state *state, int long_option)
{
	const t_argparser_option	*option;

	if (long_option)
		option = _argparser_get_option(&state->argv[state->next][2],
				g_default_options, 1);
	else
		option = _argparser_get_option(&state->argv[state->next][1],
				g_default_options, 0);
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

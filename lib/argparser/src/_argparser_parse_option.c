#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>
#include "core.h"

int	_argparser_parse_option(const t_argparser *argp,
t_argparser_state *state)
{
	const t_argparser_option	*option;
	t_parse_func				parser;
	char						*arg;

	arg = NULL;
	parser = argp->parser;
	option = _argparser_get_option(state->argv[state->next], argp->options);
	if (option == NULL)
	{
		parser = _argparser_parse_default_option;
		option = _argparser_get_option(state->argv[state->next], g_default_options);
	}
	if (option == NULL)
		return (_argparser_error("Unrecognized option", argp, state));
	if (option->arg != NULL)
	{
		arg = _argparser_get_arg(state);
		if (arg == NULL && (option->flags & OPTION_ARG_OPTIONAL) == 0)
			return (_argparser_error("Missing argument for option", argp, state));
	}
	if (parser(option->key, arg, state) == ARGP_ERR_UNKNOWN)
		return (0);
	state->next = state->next + 1;
	return (1);
}

#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>
#include "core.h"

static int	argparser_loop(const t_argparser *argp, t_argparser_state *state)
{
	const char	*argument;

	while (state->next < state->argc)
	{
		argument = state->argv[state->next];
		if (argument[0] == '-')
		{
			if (_argparser_parse_option(argp, state) != 1)
				return (0);
		}
		else
		{
			if (_argparser_parse_argument(argp, state) != 1)
				return (0);
		}
	}
	argp->parser(ARGP_KEY_END, NULL, state);
	return (1);
}

static t_argparser_state	argparser_init_state(int argc, char **argv,
const t_argparser *argp, void *input)
{
	t_argparser_state	state;

	mset(&state, 0, sizeof(state));
	state.root_argp = argp;
	state.argc = argc;
	state.argv = argv;
	if ((argp->flags & ARGP_PARSE_ARGV0) == 0)
		state.next = 1;
	else
		state.next = 0;
	state.flags = argp->flags;
	state.name = argv[0];
	state.input = input;
	return (state);
}

int	argparser_parse(const t_argparser *argp, int argc, char **argv,
void *input)
{
	t_argparser_state	state;
	int					ret;

	state = argparser_init_state(argc, argv, argp, input);
	ret = argparser_loop(argp, &state);
	if (ret == 0 && (argp->flags & (ARGP_NO_ERRS | ARGP_NO_EXIT)) == 0)
		argparser_usage(&state);
	if (argp->arg_index != NULL)
		*(argp->arg_index) = state.next;
	return (ret);
}

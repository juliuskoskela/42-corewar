#include "argparser.h"
#include "argparser_internal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int	argparser_parse_option(const t_argparser *argp,
t_argparser_state *state, int long_option)
{
	int			key;
	char		*arg;

	if ((long_option && _argparser_get_long_opt(&key, &arg, argp, state))
		|| (!long_option && _argparser_get_short_opt(&key, &arg, argp, state)))
	{
		if (argp->parser(key, arg, state) == ARGP_ERR_UNKNOWN)
			return (0);
	}
	else if (_argparser_get_default_opt(&key, &arg, state, long_option))
	{
		_argparser_parse_default_opt(key, arg, state);
	}
	else
		return (0);
	state->next = state->next + 1;
	return (1);
}

static int	argparser_parse_argument(const t_argparser *argp,
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

static int	argparser_loop(const t_argparser *argp, t_argparser_state *state)
{
	const char	*argument;

	while (state->next < state->argc)
	{
		argument = state->argv[state->next];
		if (strncmp(argument, "--", 2) == 0)
		{
			if (!argparser_parse_option(argp, state, 1))
				return (0);
		}
		else if (strncmp(argument, "-", 1) == 0)
		{
			if (!argparser_parse_option(argp, state, 0))
				return (0);
		}
		else
		{
			if (!argparser_parse_argument(argp, state))
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

	memset(&state, 0, sizeof(state));
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
	if (ret == 0 && (argp->flags & ARGP_NO_ERRS) == 0)
	{
		dprintf(2, "Invalid option or argument: %s\n", state.argv[state.next]);
		if ((argp->flags & ARGP_NO_EXIT) == 0)
			argparser_usage(&state);
	}
	if (argp->arg_index != NULL)
		*(argp->arg_index) = state.next;
	return (ret);
}

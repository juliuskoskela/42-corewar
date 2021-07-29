#include "../include/argparser.h"
#include <string.h>
#include <stdlib.h>

void	argparser_help(struct argparser_state *state)
{
	dprintf(2, "help here for %s\n", state->name);
	exit(0);
}

char	*argparser_get_arg(struct argparser_state *state)
{
	
}

struct argparser_option	*argparser_get_option(char *argument, const struct argparser_option *options, int long_option)
{
	int	i;
	int	arg_len;

	arg_len = strlen(argument);
	if (arg_len == 0 || (long_option == 0 && arg_len > 1))
		return (NULL);
	i = 0;
	while (options[i].name != NULL)
	{
		if (long_option)
		{
			if (strcmp(argument, options[i].name) == 0)
				return (&options[i]);
		}
		else
		{
			if (argument[0] == (char)options[i].key)
				return (&options[i]);
		}
		i++;
	}
	return (NULL);
}

int	argparser_get_long_opt(int *key, char **arg, const struct argparser *argp, struct argparser_state *state)
{
	struct argparser_option *option;

	option = argparser_get_option(&state->argv[state->next][2], argp->options, 1);
	if (option == NULL)
		return (0);
	*key = option->key;
	if (option->arg != NULL)
	{
		*arg = argparser_get_arg(state);
		if (*arg == NULL && (option->flags & OPTION_ARG_OPTIONAL) == 0)
			return (0);
	}
	return (1);
}

int	argparser_get_short_opt(int *key, char **arg, const struct argparser *argp, struct argparser_state *state)
{
	struct argparser_option *option;

	option = argparser_get_option(&state->argv[state->next][1], argp->options, 0);
	if (option == NULL)
		return (0);
	*key = option->key;
	if (option->arg != NULL)
	{
		*arg = argparser_get_arg(state);
		if (*arg == NULL && (option->flags & OPTION_ARG_OPTIONAL) == 0)
			return (0);
	}
	return (1);
}

int	argparser_loop(const struct argparser *argp, struct argparser_state *state)
{
	const char	*argument;
	int			key;
	char		*arg;

	while (state->next < state->argc)
	{
		argument = state->argv[state->next];
		arg = NULL;
		if (strncmp(argument, "--", 2) == 0)
		{
			if (!argparser_get_long_opt(&key, &arg, argp, state))
				return (0);
		}
		else if (strncmp(argument, "-", 1) == 0)
		{
			if (!argparser_get_short_opt(&key, &arg, argp, state))
				return (0);
		}
		else
			key = ARGP_KEY_ARG;
		argp->parser(key, arg, state);
		if (key == ARGP_KEY_ARG)
			state->arg_num = state->arg_num + 1;
		state->next = state->next + 1;
	}
	argp->parser(ARGP_KEY_END, NULL, state);
	return (1);
}

static void	argparser_init_state(struct argparser_state *state, int argc, char **argv, unsigned int flags, void *input)
{
	state->argc = argc;
	state->argv = argv;
	if ((flags & ARGP_PARSE_ARGV0) == 0)
		state->next = 1;
	else
		state->next = 0;
	state->flags = flags;
	state->arg_num = 0;
	state->quoted = 0;
	state->input = input;
	state->name = argv[0];
	state->hook = NULL;
	state->pstate = NULL;
}

int	argparser_parse(const struct argparser *argp, int argc, char **argv,
	unsigned flags, int *arg_index, void *input)
{
	struct argparser_state	state;
	int						ret;

	argparser_init_state(&state, argc, argv, flags, input);
	ret = argparser_loop(argp, &state);
	if (ret == 0 && (flags & ARGP_NO_EXIT) != 0)
	{
		dprintf(2, "error occurred, exiting\n");
		exit(ARGP_EXIT_PARSE_ERROR);
	}
	return (ret);
}

void	argparser_usage(struct argparser_state *state)
{
	dprintf(2, "usage here for %s\n", state->name);
	exit(ARGP_EXIT_PARSE_ERROR);
}

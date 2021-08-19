#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

static void	argparser_add_newline(int *col)
{
	dprintf(1, "\n");
	*col = dprintf(1, "\t");
}

static void	argparser_print_short_options(const t_argparser_option *options,
int *col)
{
	size_t	i;

	i = 0;
	while (options[i].name != NULL)
	{
		if (isprint(options[i].key))
		{
			*col += dprintf(1, " [-%c", options[i].key);
			if (options[i].arg != NULL)
			{
				if (((unsigned int)options[i].flags & OPTION_ARG_OPTIONAL) == 0)
					*col += dprintf(1, " %s", options[i].arg);
				else
					*col += dprintf(1, " [%s]", options[i].arg);
			}
			*col += dprintf(1, "]");
		}
		if (*col > ARGP_MAX_WIDTH)
			argparser_add_newline(col);
		i++;
	}
}

static void	argparser_print_long_options(const t_argparser_option *options,
int *col)
{
	size_t	i;

	i = 0;
	while (options[i].name != NULL)
	{
		*col += dprintf(1, " [--%s", options[i].name);
		if (options[i].arg != NULL)
		{
			if (((unsigned int)options[i].flags & OPTION_ARG_OPTIONAL) == 0)
				*col += dprintf(1, " %s", options[i].arg);
			else
				*col += dprintf(1, " [%s]", options[i].arg);
		}
		*col += dprintf(1, "]");
		if (*col > ARGP_MAX_WIDTH)
			argparser_add_newline(col);
		i++;
	}
}

void	_argparser_long_usage(t_argparser_state *state)
{
	int	col;

	col = 0;
	col += dprintf(1, "Usage: %s", state->name);
	argparser_print_short_options(state->root_argp->options, &col);
	argparser_print_short_options(g_default_options, &col);
	argparser_print_long_options(state->root_argp->options, &col);
	argparser_print_long_options(g_default_options, &col);
	if (state->root_argp->args_doc != NULL)
		dprintf(1, " %s", state->root_argp->args_doc);
	dprintf(1, "\n");
	exit(0);
}

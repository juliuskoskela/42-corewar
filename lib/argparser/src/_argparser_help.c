#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static void	argparser_help_print_options(const t_argparser_option *options)
{
	size_t	i;
	int		col;

	i = 0;
	while (options[i].name != NULL)
	{
		col = 0;
		if (isprint(options[i].key))
			col += dprintf(1, " -%c, ", options[i].key);
		else
			col += dprintf(1, "     ");
		col += dprintf(1, "--%s", options[i].name);
		if (options[i].arg != NULL)
			col += dprintf(1, "=%s", options[i].arg);
		while (col < 30)
			col += dprintf(1, " ");
		dprintf(1, "%s\n", options[i].doc);
		i++;
	}
}

void	_argparser_help(t_argparser_state *state)
{
	_argparser_print_usage(state);
	if (state->root_argp->doc != NULL)
		dprintf(1, "%s\n", state->root_argp->doc);
	dprintf(1, "\n");
	argparser_help_print_options(state->root_argp->options);
	argparser_help_print_options(g_default_options);
	exit(0);
}

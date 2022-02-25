/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a header                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>
#include "core.h"

static void	argparser_add_newline(int *col)
{
	print_fd(1, "\n");
	*col = print_fd(1, "\t");
}

static void	argparser_print_short_options(const t_argparser_option *options,
int *col)
{
	size_t	i;

	i = 0;
	while (options[i].name != NULL)
	{
		if (is_print(options[i].key))
		{
			*col += print_fd(1, " [-%c", options[i].key);
			if (options[i].arg != NULL)
			{
				if (((unsigned int)options[i].flags & OPTION_ARG_OPTIONAL) == 0)
					*col += print_fd(1, " %s", options[i].arg);
				else
					*col += print_fd(1, " [%s]", options[i].arg);
			}
			*col += print_fd(1, "]");
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
		*col += print_fd(1, " [--%s", options[i].name);
		if (options[i].arg != NULL)
		{
			if (((unsigned int)options[i].flags & OPTION_ARG_OPTIONAL) == 0)
				*col += print_fd(1, " %s", options[i].arg);
			else
				*col += print_fd(1, " [%s]", options[i].arg);
		}
		*col += print_fd(1, "]");
		if (*col > ARGP_MAX_WIDTH)
			argparser_add_newline(col);
		i++;
	}
}

void	_argparser_long_usage(t_argparser_state *state)
{
	int	col;

	col = 0;
	col += print_fd(1, "Usage: %s", state->name);
	argparser_print_short_options(state->root_argp->options, &col);
	argparser_print_short_options(g_default_opts, &col);
	argparser_print_long_options(state->root_argp->options, &col);
	argparser_print_long_options(g_default_opts, &col);
	if (state->root_argp->args_doc != NULL)
		print_fd(1, " %s", state->root_argp->args_doc);
	print_fd(1, "\n");
	exit(0);
}

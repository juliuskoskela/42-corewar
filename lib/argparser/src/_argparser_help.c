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

static void	argparser_help_print_options(const t_argparser_option *options)
{
	size_t	i;
	int		col;

	i = 0;
	while (options[i].name != NULL)
	{
		col = 0;
		if (is_print(options[i].key))
			col += print_fd(1, " -%c, ", options[i].key);
		else
			col += print_fd(1, "     ");
		col += print_fd(1, "--%s", options[i].name);
		if (options[i].arg != NULL)
			col += print_fd(1, " %s", options[i].arg);
		while (col < 30)
			col += print_fd(1, " ");
		print_fd(1, "%s\n", options[i].doc);
		i++;
	}
}

void	_argparser_help(t_argparser_state *state)
{
	_argparser_print_usage(state);
	if (state->root_argp->doc != NULL)
		print_fd(1, "%s\n", state->root_argp->doc);
	print_fd(1, "\n");
	argparser_help_print_options(state->root_argp->options);
	argparser_help_print_options(g_default_opts);
	exit(0);
}

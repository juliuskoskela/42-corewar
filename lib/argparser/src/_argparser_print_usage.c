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
#include <stdlib.h>
#include "core.h"

void	_argparser_print_usage(t_argparser_state *state)
{
	if (state->root_argp->args_doc == NULL)
	{
		print_fd(2, "Usage: %s [OPTION...]\n", state->name);
	}
	else
	{
		print_fd(2, "Usage: %s [OPTION...] %s\n",
			state->name, state->root_argp->args_doc);
	}
}

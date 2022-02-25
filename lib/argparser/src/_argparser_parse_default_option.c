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

int	_argparser_parse_default_option(int key, char *arg,
t_argparser_state *state)
{
	if (key == 1)
	{
		_argparser_help(state);
	}
	else if (key == 2)
	{
		_argparser_long_usage(state);
	}
	else if (key == ARGP_KEY_ARG && arg != NULL)
	{
		argparser_usage(state);
	}
	else if (key == ARGP_KEY_END)
	{
		return (0);
	}
	else
	{
		return (ARGP_ERR_UNKNOWN);
	}
	return (0);
}

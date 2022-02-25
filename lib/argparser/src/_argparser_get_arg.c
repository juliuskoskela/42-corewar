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

char	*_argparser_get_arg(t_argparser_state *state)
{
	char	*next_argument;

	if (state->next + 1 == state->argc)
		return (NULL);
	next_argument = state->argv[state->next + 1];
	if (next_argument[0] == '-')
		return (NULL);
	else
	{
		state->next = state->next + 1;
		return (next_argument);
	}
}

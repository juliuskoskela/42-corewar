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
#include "core.h"

const t_argparser_option	*_argparser_get_option(char *argument,
const t_argparser_option *options)
{
	int		option_type;
	size_t	i;
	size_t	arg_len;

	if (s_ncmp(argument, "--", 2) == 0)
		option_type = ARGP_LONG_OPT;
	else
		option_type = ARGP_SHORT_OPT;
	arg_len = s_len(argument);
	if ((option_type == ARGP_LONG_OPT && arg_len == 2)
		|| (option_type == ARGP_SHORT_OPT && arg_len > 2))
		return (NULL);
	i = 0;
	while (options[i].name != NULL)
	{
		if (option_type == ARGP_LONG_OPT
			&& (s_cmp(&argument[2], options[i].name) == 0))
			return (&options[i]);
		else if (argument[1] == (char)options[i].key)
			return (&options[i]);
		i++;
	}
	return (NULL);
}

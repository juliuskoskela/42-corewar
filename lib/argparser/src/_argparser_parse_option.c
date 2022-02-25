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

int	_argparser_parse_option(const t_argparser *argp,
t_argparser_state *state)
{
	const t_argparser_option	*opt;
	t_parse_func				parser;
	char						*arg;

	arg = NULL;
	parser = argp->parser;
	opt = _argparser_get_option(state->argv[state->next], argp->options);
	if (opt == NULL)
	{
		parser = _argparser_parse_default_option;
		opt = _argparser_get_option(state->argv[state->next], g_default_opts);
	}
	if (opt == NULL)
		return (_argparser_error("Unrecognized option", argp, state));
	if (opt->arg != NULL)
	{
		arg = _argparser_get_arg(state);
		if (arg == NULL && (opt->flags & OPTION_ARG_OPTIONAL) == 0)
			return (_argparser_error("Missing argument for opt", argp, state));
	}
	if (parser(opt->key, arg, state) == ARGP_ERR_UNKNOWN)
		return (0);
	state->next = state->next + 1;
	return (1);
}

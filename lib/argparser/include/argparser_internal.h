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

#ifndef ARGPARSER_INTERNAL_H
# define ARGPARSER_INTERNAL_H

# include "argparser.h"

# define ARGP_EXIT_PARSE_ERROR	-1
# define ARGP_MAX_WIDTH			60

# define ARGP_SHORT_OPT			0
# define ARGP_LONG_OPT			1

static const t_argparser_option	g_default_opts[] = {
{"help", 1, 0, 0, "print this help message"},
{"usage", 2, 0, 0, "print a short usage message"},
{0, 0, 0, 0, 0}
};

int							_argparser_parse_argument(
								const t_argparser *argp,
								t_argparser_state *state);
int							_argparser_parse_option(
								const t_argparser *argp,
								t_argparser_state *state);
int							_argparser_parse_default_option(int key,
								char *arg,
								t_argparser_state *state);
const t_argparser_option	*_argparser_get_option(char *argument,
								const t_argparser_option *options);
char						*_argparser_get_arg(t_argparser_state *state);
void						_argparser_print_usage(t_argparser_state *state);
void						_argparser_long_usage(t_argparser_state *state);
void						_argparser_help(t_argparser_state *state);
int							_argparser_error(const char *msg,
								const t_argparser *argp,
								t_argparser_state *state);

#endif

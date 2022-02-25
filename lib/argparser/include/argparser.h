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

#ifndef ARGPARSER_H
# define ARGPARSER_H

# define OPTION_ARG_OPTIONAL		1U
/* Currently nsupported option flags
# define OPTION_HIDDEN				2U
# define OPTION_ALIAS				4U
# define OPTION_DOC					8U
*/

# define ARGP_PARSE_ARGV0			1U
# define ARGP_NO_ERRS 				2U
# define ARGP_NO_EXIT 				32U
/* Currently unsupported parser flags
# define ARGP_NO_ARGS 				4U
# define ARGP_IN_ORDER				8U
*/

# define ARGP_ERR_UNKNOWN			(-1)

# define ARGP_KEY_ARG				0
# define ARGP_KEY_END				1

typedef struct s_argparser_state
{
	const struct s_argparser		*root_argp;
	int								argc;
	char							**argv;
	int								next;
	unsigned int					flags;
	unsigned int					arg_num;
	int								quoted;
	void							*input;
	char							*name;
	void							*hook;
	void							*pstate;
}	t_argparser_state;

typedef struct s_argparser_option
{
	const char						*name;
	int								key;
	const char						*arg;
	unsigned int					flags;
	const char						*doc;
}	t_argparser_option;

typedef int	(*t_parse_func)(int key, char *arg, t_argparser_state *state);

typedef struct s_argparser
{
	const t_argparser_option		*options;
	t_parse_func					parser;
	const char						*args_doc;
	const char						*doc;
	unsigned int					flags;
	int								*arg_index;
}	t_argparser;

int									argparser_parse(const t_argparser *argp,
										int argc,
										char **argv,
										void *input);
void								argparser_usage(t_argparser_state *state);

#endif

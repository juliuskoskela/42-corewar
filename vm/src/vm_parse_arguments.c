/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:48 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:49 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "argparser.h"

static int	set_next_player_nbr(t_input_args *args)
{
	int	next_nbr;
	int	i;

	next_nbr = 1;
	i = 0;
	while (i < args->player_count)
	{
		if (next_nbr == args->player_numbers[i])
		{
			next_nbr += 1;
			i = 0;
		}
		else
			i++;
	}
	return (next_nbr);
}

static int	player_nbr_is_assigned(t_input_args *args, int nbr)
{
	int	i;

	i = 0;
	while (i < args->player_count)
	{
		if (args->player_numbers[i] == nbr)
			return (1);
		i++;
	}
	return (0);
}

static void	parse_numeric_option(int key, char *arg, t_argparser_state *state)
{
	t_input_args	*args;
	int				nbr;

	args = state->input;
	nbr = (int)s_toi(arg);
	if (nbr == 0 && s_cmp(arg, "0") != 0)
		argparser_usage(state);
	else if (key == 'd' && nbr > 0)
		args->dump_nbr_cycles = nbr;
	else if (key == 'v' && (nbr >= 0 && nbr <= 31))
		args->verbosity = nbr;
	else if (key == 'n' && nbr > 0 && !player_nbr_is_assigned(args, nbr))
		args->next_player_nbr = nbr;
	else if (key == 's' && nbr > 0)
		args->pause_nbr_cycles = nbr;
	else
		argparser_usage(state);
}

static int	parse_opt(int key, char *arg, t_argparser_state *state)
{
	t_input_args	*args;

	args = state->input;
	if (key == 'd' || key == 'v' || key == 'n' || key == 's')
		parse_numeric_option(key, arg, state);
	else if (key == 'c')
		args->coloured_output = 1;
	else if (key == 'i')
		args->interactive_mode = 1;
	else if (key == ARGP_KEY_ARG)
	{
		if (args->player_count == MAX_PLAYERS)
			argparser_usage(state);
		args->player_paths[args->player_count] = arg;
		args->player_numbers[args->player_count] = args->next_player_nbr;
		args->next_player_nbr = set_next_player_nbr(args);
		args->player_count += 1;
	}
	else if (key == ARGP_KEY_END && args->player_count == 0)
		argparser_usage(state);
	else if (args->player_count)
		return (ARGP_ERR_UNKNOWN);
	return (0);
}

t_input_args	vm_parse_arguments(int argc, char **argv)
{
	t_input_args					args;
	t_argparser						argparser;
	static const char				doc[] = "corewar: description";
	static const char				args_doc[] = "<path/to/player.cor> ...";
	static const t_argparser_option	options[] = {
	{"dump", 'd', "nbr_cycles", 0, "dump memory to standard output and exit\n\
		after nbr_cycles (> 0)"},
	{"show", 's', "nbr_cycles", 0, "dump memory every N cycles and pause until\n\
		a key is pressed"},
	{"verbosity", 'v', "level", 0, "verbosity level (set between 0 and 31)"},
	{"coloured", 'c', 0, 0, "use colours in printing to standard output"},
	{"nbr", 'n', "nbr", 0, "set the number (> 0) of the next player"},
	{"interactive", 'i', 0, 0, "execute vm in an interactive mode"},
	{0}
	};

	mzero(&args, sizeof(args));
	args.next_player_nbr = 1;
	mzero(&argparser, sizeof(argparser));
	argparser.doc = doc;
	argparser.args_doc = args_doc;
	argparser.options = options;
	argparser.parser = parse_opt;
	argparser_parse(&argparser, argc, argv, &args);
	return (args);
}

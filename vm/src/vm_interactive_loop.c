/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_interactive_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:12:00 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:12:00 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_interactive_option	vm_parse_user_input(
	const t_interactive_option *options, char *line, int *arg)
{
	size_t	i;
	size_t	opt_len;

	i = 0;
	while (options[i].name != NULL)
	{
		opt_len = s_len(options[i].opt);
		if (s_ncmp(options[i].opt, line, opt_len) == 0)
		{
			if (line[opt_len] != '\0')
				*arg = (int)s_toi(&line[opt_len]);
			break ;
		}
		i++;
	}
	return (options[i]);
}

static int	interactive_loop(t_arena *arena,
const t_interactive_option *options)
{
	int						arg;
	char					*line;
	t_interactive_option	option;

	while (1)
	{
		arg = -1;
		print(">>> ");
		line = NULL;
		if (s_readline(0, &line) <= 0)
			return (0);
		option = vm_parse_user_input(options, line, &arg);
		free(line);
		if (option.ptr != NULL)
			option.ptr(arena, arg);
		else
			break ;
	}
	if (option.name != NULL && s_ncmp(option.name, "n", 1) == 0 && arg > 0)
		return (arg);
	return (0);
}

int	vm_interactive_loop(t_arena *arena)
{
	static const t_interactive_option	options[] = {
	{"processes", "p", vm_interactive_print_processes},
	{"arena", "a", vm_interactive_print_arena},
	{"exit", "exit", vm_interactive_exit},
	{"help", "help", vm_interactive_help},
	{"next", "n", NULL},
	{0, 0, 0}
	};

	return (interactive_loop(arena, options));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_interactive_help.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:12:04 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:12:04 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_interactive_print_processes(t_arena *arena, int *arg)
{
	if (arg != NULL && *arg > (int)arena->player_count)
		print("Invalid process id %d\n", *arg);
	else
	{
		if (arg == NULL)
			vm_print_processes(arena, 1, 0);
		else
			vm_print_processes(arena, 0, *arg);
	}
}

void	vm_interactive_print_arena(t_arena *arena, int *arg)
{
	if (!arena || arg != NULL)
		return ;
	vm_print_arena(*arena, arena->processes);
}

void	vm_interactive_exit(t_arena *arena, int *arg)
{
	if (!arena || arg != NULL)
		exit(1);
	exit(0);
}

void	vm_interactive_help(t_arena *arena, int *arg)
{
	if (!arena || arg != NULL)
		return ;
	print("Interactive options:\n\
	p [ID]\t\tprint all processes (p 0) or processes related to an ID\n\
	a\t\tprint arena's memmory\n\
	exit\t\texit program\n\
	help\t\tprint this message\n\
	n [NBR]\t\tjump to the next cycle or NBR cycles forward\n");
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_battle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:12:42 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:12:42 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_process	*vm_free_processes(t_process **lst)
{
	t_process	*tmp;

	tmp = *lst;
	while (*lst)
	{
		tmp = *lst;
		*lst = lst[0]->next;
		mdel((void **)&tmp);
	}
	return (NULL);
}

static t_process	*init_processes(t_arena arena)
{
	t_int32		player_id;
	t_process	*process_lst;

	process_lst = NULL;
	player_id = 0;
	while (++player_id <= arena.player_count)
		process_lst = vm_create_process(arena, process_lst, player_id);
	return (process_lst);
}

void	vm_battle(t_arena a)
{
	int	interactive_mode_skip;

	a.processes = init_processes(a);
	vm_introduce_champs(a);
	interactive_mode_skip = 0;
	while (a.processes)
	{
		vm_execute_cycle(a.processes, &a);
		if (++a.cycles_since_check >= a.cycle_to_die)
			vm_check_live(&a.processes, &a);
		if (a.dump_nbr_cycles && a.current_cycle > a.dump_nbr_cycles)
		{
			vm_print_arena(a, a.processes);
			vm_free_processes(&a.processes);
			return ;
		}
		if (a.pause_nbr_cycles && a.current_cycle + 1 % a.pause_nbr_cycles)
			vm_pause_and_print_memory(a);
		if (interactive_mode_skip)
			interactive_mode_skip--;
		if (a.interactive_mode && interactive_mode_skip == 0)
			interactive_mode_skip = vm_interactive_loop(&a);
	}
	print("Contestant %d, \"%s\", has won !\n", a.last_player_alive,
		a.players[a.last_player_alive - 1].prog_name);
}

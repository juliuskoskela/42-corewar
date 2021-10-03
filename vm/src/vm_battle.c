#include "vm.h"

t_process	*vm_free_processes(t_process **lst)
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

t_process	*init_processes(t_arena arena)
{
	t_size		player_id;
	t_process	*process_lst;

	process_lst = NULL;
	player_id = 0;
	while (++player_id <= arena.player_count)
		process_lst = vm_create_process(arena, process_lst, player_id);
	return (process_lst);
}

/*
** Cycles are executed until a live check occurs. Checks occur every
** battle.cycle_to_die cycles.
*/

// void	vm_battle(t_arena arena)
// {
// 	arena.processes = init_processes(arena);
// //	vm_test_print_processes(arena.processes);
// 	vm_introduce_champs(arena);
// 	while (arena.processes)
// 	{
// 		vm_execute_cycle(arena.processes, &arena);
// 		while (++arena.cycles_since_check < arena.cycle_to_die)
// 		{
// 			if (arena.dump_nbr_cycles &&
// 			arena.current_cycle > arena.dump_nbr_cycles)
// 			{
// 				vm_print_arena(arena, arena.processes);
// 				vm_free_processes(&arena.processes);
// 				return ;
// 			}
// 			vm_execute_cycle(arena.processes, &arena);
// 			if (arena.pause_nbr_cycles
// 				&& arena.current_cycle + 1 % arena.pause_nbr_cycles)
// 				vm_pause_and_print_memory(arena);
// 		}
// 		vm_check_live(&arena.processes, &arena);
// 	}
// 	print("Player %d (%s) won\n", arena.last_player_alive,
// 		arena.players[arena.last_player_alive - 1].prog_name);
// }

void vm_battle(t_arena arena)
{
	arena.processes = init_processes(arena);
	vm_introduce_champs(arena);
	while (arena.processes)
	{
		vm_execute_cycle(arena.processes, &arena);
		if (++arena.cycles_since_check >= arena.cycle_to_die)
			vm_check_live(&arena.processes, &arena);
		if (arena.dump_nbr_cycles
		&& arena.current_cycle > arena.dump_nbr_cycles)
		{
			vm_print_arena(arena, arena.processes);
			vm_free_processes(&arena.processes);
			return ;
		}
		if (arena.pause_nbr_cycles
			&& arena.current_cycle + 1 % arena.pause_nbr_cycles)
			vm_pause_and_print_memory(arena);
	}
	print("Player %d (%s) won\n", arena.last_player_alive,
		arena.players[arena.last_player_alive - 1].prog_name);
}

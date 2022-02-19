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

void vm_battle(t_arena arena)
{
	t_size	interactive_mode_skip;

	arena.processes = init_processes(arena);
	vm_introduce_champs(arena);
	interactive_mode_skip = 0;
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
		if (interactive_mode_skip)
			interactive_mode_skip--;
		if (arena.interactive_mode && interactive_mode_skip == 0)
			interactive_mode_skip = vm_interactive_loop(&arena);
	}
	print("Contestant %d \"%s\", has won\n", arena.last_player_alive,
		arena.players[arena.last_player_alive - 1].prog_name);
}

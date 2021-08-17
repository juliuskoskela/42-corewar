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

/*
** Adds a t_process element to the end of the list.
*/

t_process	*create_process(t_arena arena, t_process *process_lst, \
int player_id)
{
	t_process	*new_process;

	new_process = minit(sizeof(t_process));
	if (!new_process)
		vm_error("Malloc failed in create_process\n");
	new_process->id = player_id;
	new_process->registers[0] = player_id;
	new_process->pc = (player_id - 1) * arena.offset;
//	new_process->pc = &arena.mem[MEM_SIZE / arena.player_count * player_id];
	new_process->cycles_before_execution = -1;
	new_process->next = process_lst;
	return (new_process);
}

t_process	*init_processes(t_arena arena)
{
	t_size		player_id;
	t_process	*process_lst;

	process_lst = NULL;
	player_id = 0;
	while (++player_id <= arena.player_count)
		process_lst = create_process(arena, process_lst, player_id);
	return (process_lst);
}

void	vm_init_battle(t_arena *arena)
{
	mzero(&arena->battle, sizeof(t_battle));
	arena->battle.cycle_to_die = CYCLE_TO_DIE;
	arena->battle.last_alive = arena->player_count;
}

/*
** Cycles are executed until a live check occurs. Checks occur every
** battle.cycle_to_die cycles.
*/

void	vm_battle(t_arena arena)
{
	arena.processes = init_processes(arena);
	vm_test_print_processes(arena.processes);
	vm_init_battle(&arena);
	vm_introduce_champs(arena);
	while (arena.processes)
	{
		vm_execute_cycle(arena.processes, &arena);
		while (++arena.battle.cycles_since_check < arena.battle.cycle_to_die)
		{
			if (arena.battle.cycles_executed == arena.dump_nbr_cycles)
			{
				vm_print_arena(arena, arena.processes);
				return ;
			}
			vm_execute_cycle(arena.processes, &arena);
		}
		vm_check_live(&arena.processes, &arena.battle);
	}
	print("Player %d (%s) won\n", arena.battle.last_alive, \
	arena.all_players[arena.battle.last_alive - 1].prog_name);
}

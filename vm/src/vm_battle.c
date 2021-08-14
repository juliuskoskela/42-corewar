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
	new_process->pc = (player_id - 1) * arena.offset;
//	new_process->pc = &arena.mem[MEM_SIZE / arena.player_count * player_id];
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

void	vm_init_battle(t_arena arena, t_battle *battle)
{
	mzero(battle, sizeof(t_battle));
	battle->cycle_to_die = CYCLE_TO_DIE;
	battle->last_alive = arena.player_count;
}

/*
** Cycles are executed until a live check occurs. Checks occur every
** battle.cycle_to_die cycles.
*/

void	vm_battle(t_arena arena)
{
	t_process	*process_lst;
	t_battle	battle;

	process_lst = init_processes(arena);
	vm_test_print_processes(process_lst);
	vm_init_battle(arena, &battle);
	vm_introduce_champs(arena);
	while (process_lst)
	{
		vm_execute_cycle(process_lst, &battle, &arena);
		while (++battle.cycles_since_check < battle.cycle_to_die)
		{
			if (battle.cycles_executed == arena.dump_nbr_cycles)
			{
				vm_print_arena(arena, process_lst);
				return ;
			}
			vm_execute_cycle(process_lst, &battle, &arena);
		}
		vm_check_live(&process_lst, &battle);
	}
	print("Player %d (%s) won\n", battle.last_alive, \
	arena.all_players[battle.last_alive - 1].prog_name);
}

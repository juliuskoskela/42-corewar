#include "vm.h"

/*
	Changed arena.all_players[] array into type t_header to
	avoid confusion with the list of processes.

	Started building VM loop. 
*/

/*
** Adds a t_process element to the end of the list of processes.
*/

void		vm_introduce_champs(t_arena arena)
{
	t_size i;

	i = 0;
	while (i < arena.player_count)
	{
		print("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", 
		i + 1, arena.all_players[i].prog_size, arena.all_players[i].prog_name,\
		arena.all_players[i].comment);
		i++;
	}
}

t_process	*create_process(t_arena arena, t_process *process_lst, int player_id)
{
	t_process *new_process;

	new_process = minit(sizeof(t_process));
	if (!new_process)
		vm_error("Malloc failed in create_process\n");
	new_process->id = player_id;
	new_process->pc = &arena.mem[MEM_SIZE / arena.player_count * player_id];
	new_process->next = process_lst;
	return (new_process);
}


t_process   *init_processes(t_arena arena)
{
	t_size     player_id;
	t_process   *process_lst;

	process_lst = NULL;
	player_id = 0;
	while (++player_id <= arena.player_count)
		process_lst = create_process(arena, process_lst, player_id);
	return (process_lst);
}

void	vm_battle(t_arena arena)
{
	t_process	*process_lst;
//	t_battle	battle;

	process_lst = init_processes(arena);
	vm_test_print_processes(process_lst);
	vm_introduce_champs(arena);
}
#include "vm.h"

/*
** Adds a t_process element to the end of the list.
*/

t_process	*vm_create_process(t_arena arena, t_process *process_lst, \
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
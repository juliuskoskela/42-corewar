#include "vm.h"

// If the argument is the id of one of the players, this
// instruction reports the player_number of first argument to be alive. This
// is done by modifying a->last_player_alive variable.
// Updates the value of last_live in the current process.

void vm_instr_alive(
		t_arena *a,
		t_process *p)
{
//	t_process	*cur;
	t_size		mem_i;
	t_uint64	id;

	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	id = vm_get_val(a, p, T_DIR, &mem_i);
//	cur = a->processes;
//	while (cur && cur->id != id)
//		cur = cur->next;
//	if (!cur)
//		vm_error("Process with id not found!\n");
	p->last_live = a->cycles_executed;
	p->pc = mem_i;
	if (id <= 0 || id > a->player_count)
		return ;
	a->last_player_alive = id;
	print("A process shows that player %d (%s) is alive\n", id, a->all_players[id - 1].prog_name);
}

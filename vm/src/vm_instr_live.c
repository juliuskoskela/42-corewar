#include "vm.h"

// If the argument is the id of one of the players, this
// instruction reports the player_number of first argument to be alive. This
// is done by modifying a->last_player_alive variable.
// Updates the value of last_live in the current process.

void vm_instr_live(
		t_arena *a,
		t_process *p)
{
	t_argument	arg;
	t_size		mem_i;
	t_uint64	id;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "live id");
	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	arg.type = T_DIR;
	arg.size = REG_SIZE;
	id = vm_get_val(a, p, arg, &mem_i);
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\tlive %d\n", (int)id);
	p->last_live = a->current_cycle;
	if (id > 0 && id < a->player_count)
	{
		a->last_player_alive = id;
		print("A process shows that player %d (%s) is alive\n",
			id, a->all_players[id - 1].prog_name);
	}
	if ((a->verbosity & VM_VERBOSE_PC) != 0)
		print("\tPC: %d => %d\n", (int)p->pc, (int)mem_i);
	p->pc = mem_i;
}

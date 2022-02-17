/// opcode:		1 (0x01)
/// mnemonic:	live
/// name:		alive
/// params:		1 : { T_DIR }
/// acb:		no
/// ncycles:	10
/// proto:		live id
/// descript:	Reports player #id as being alive

#include "vm.h"

void	vm_instr_live(t_arena *a, t_process *p)
{
	t_int32 id;

	//get live id from the first argument of the process
	vm_instr_get_param(&id, a, p, 0);

	//update last_live for the current_process
	p->last_live = a->current_cycle;

	//save id in the arena
	a->last_player_alive = id;
	vm_instr_null(a, p);
}

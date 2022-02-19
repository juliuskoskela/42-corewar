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

	vm_instr_get_param(&id, a, p, 0);
	id *= -1;
	if (id > 0 && id <= a->player_count)
	{
		p->last_live = a->current_cycle;
		a->last_player_alive = id;
		//add verbosity check
		if (a->verbosity & VM_VERBOSE_LIVES)
			print("A process shows that player %d (%s) is alive.",\
			 id, a->players[id - 1].prog_name);
	}
}

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
	// Read live ID from process param.
	
	// Search for corresponding process in `a`.
	
	// If corresponding process is found, update it's `last_live` to be
	// the current cycle.
	
	vm_instr_null(a, p);
}

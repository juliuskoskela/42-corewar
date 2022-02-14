/// opcode:		9 (0x09)
/// mnemonic:	zjmp
/// name:		jump if zero
/// params:		1 : { T_DIR }
/// acb:		false
/// ncycles:	20
/// proto:		zjmp offset
/// descript:	Moves the process's PC by offset only if the process's zf is set to 1.

#include "vm.h"

void	vm_instr_zjmp(t_arena *a, t_process *p)
{
	t_uint32 dirval;

	// Get dir val.
	vm_reg_store((t_byte *)&dirval, &p->current_instruction.args[0].data);

	// Check process zf and update pc
	if (p->zf)
		p->pc += dirval;
}

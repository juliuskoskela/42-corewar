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
	// Check process zf

	// Update PC
}

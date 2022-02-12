/// opcode:		16 (0x10)
/// mnemonic:	aff
/// name:		aff
/// params:		1 : { T_REG }
/// acb:		true
/// ncycles:	2
/// proto:		aff chr
/// descript:	Makes this process' champion talk by displaying chr's value. This instruction is useful if you want to ridicule your opponents.

#include "vm.h"

void	vm_instr_aff(t_arena *a, t_process *p)
{
	// Print CHR
}

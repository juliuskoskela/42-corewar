/// opcode:		10 (0x0a)
/// mnemonic:	ldi
/// name:		load index
/// params:		3 : { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG }
/// acb:		true
/// ncycles:	25
/// proto:		ldi lhs, rhs, dst
/// descript:	Computes lhs + rhs and uses the result as an offset to address memory and load a 32-bit value from memory into the register dst.

#include "vm.h"

void	vm_instr_ldi(t_arena *a, t_process *p)
{
	// Get lhs, rhs

	// Calculate index (lhs + rhs) % IDX_MOD

	// Store value at `index` to register dst
}
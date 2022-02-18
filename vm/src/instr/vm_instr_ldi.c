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
	t_int32 lhs;
	t_int32 rhs;
	t_int32 mem_addr;
	t_int32 reg_addr;

	// Get register
	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[2].data);\

	if (reg_addr > 16)
	{
		print("reg addr > 16\n");
		return ;
	}

	// Get lhs, rhs
	vm_instr_get_param(&lhs, a, p, 0);
	vm_instr_get_param(&rhs, a, p, 1);

	// Calculate index (lhs + rhs) % IDX_MOD
	mem_addr = (lhs + rhs) % IDX_MOD;

	// Load value from `mem_addr` to register dst.
	vm_mem_set_pos(&a->mem, (p->pc + mem_addr) % IDX_MOD);
	vm_mem_read((t_byte *)&p->registers[reg_addr - 1], &a->mem, 4);

	vm_instr_null(a, p);
}
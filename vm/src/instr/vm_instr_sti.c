/// opcode:		11 (0x0b)
/// mnemonic:	sti
/// name:		store index
/// params:		3 : { T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG }
/// acb:		true
/// ncycles:	25
/// proto:		sti src, lhs, rhs
/// descript:	Computes lhs + rhs and uses the result as an offset to address memory and store the value of the register src at that memory location.

#include "vm.h"

void	vm_instr_sti(t_arena *a, t_process *p)
{
	t_uint8		reg_addr;
	/*t_uint32	lhs;*/
	/*t_uint32	rhs;*/

	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[0].data);
	if (reg_addr > 16)
		return ;
	if (p->current_instruction.args[1].type == REG_CODE)
		vm_reg_copy(&p->registers[reg_addr - 1], &p->current_instruction.args[0].data);
	else
	{
		vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[1].data);
		if (reg_addr % IDX_MOD != 0)
			p->zf = TRUE;
		vm_mem_set_pos(&a->mem, p->pc + reg_addr % IDX_MOD);
		vm_mem_write(&a->mem, (t_byte *)&p->registers[reg_addr - 1], IND_ADDR_SIZE);
	}
	// print(" => %sR%d%s ", BLU, reg_addr, NRM);
	print(" => R%d ", reg_addr);
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
	return ;
}

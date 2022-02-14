#include "vm.h"

void	vm_instr_ld(t_arena *a, t_process *p)
{
	t_uint8		reg_addr;
	t_uint16	mem_addr;

	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[1].data);
	if (reg_addr > 16)
		return ;
	if (p->current_instruction.args[0].type == DIR_CODE)
		vm_reg_copy(&p->registers[reg_addr - 1], &p->current_instruction.args[0].data);
	else
	{
		vm_reg_store((t_byte *)&mem_addr, &p->current_instruction.args[0].data);
		if (mem_addr % IDX_MOD != 0)
			p->zf = TRUE;
		vm_mem_set_pos(&a->mem, (p->pc + mem_addr) % IDX_MOD);
		vm_mem_read((t_byte *)&p->registers[reg_addr - 1], &a->mem, 4);
	}
	// print(" => %sR%d%s ", BLU, reg_addr, NRM);
	print(" => R%d ", reg_addr);
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
	return ;
}

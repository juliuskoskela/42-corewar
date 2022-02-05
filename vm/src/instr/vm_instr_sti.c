#include "instr.h"

void	vm_instr_sti(t_arena *a, t_process *p)
{
	t_uint8		reg_addr;
	t_uint16	mem_addr;

	vm_reg_deref((t_byte *)&reg_addr, &p->current_instruction.args[0].data);
	if (reg_addr > 16)
		return ;
	if (p->current_instruction.args[1].type == REG_CODE)
		vm_reg_copy(&p->registers[reg_addr - 1], &p->current_instruction.args[0].data);
	else
	{
		vm_reg_deref((t_byte *)&mem_addr, &p->current_instruction.args[1].data);
		if (mem_addr % IDX_MOD != 0)
			p->zf = TRUE;
		vm_mem_set_pos(&a->mem, p->pc + mem_addr % IDX_MOD);
		vm_mem_write(&a->mem, (t_byte *)&p->registers[reg_addr - 1], IND_ADDR_SIZE);
	}
	print(" => %sR%d%s ", BLU, reg_addr, NRM);
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
	return ;
}

// 13 (0x0d) | ``lld`` | "long load" | 2 : { T_DIR | T_IND, T_REG } | yes | 10 | ``lld src, dst`` Long version of ld

#include "vm.h"

void	vm_instr_lld(t_arena *a, t_process *p)
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
		if (mem_addr % MEM_SIZE != 0)
			p->zf = TRUE;
		vm_mem_set_pos(&a->mem, (p->pc + mem_addr) % MEM_SIZE);
		vm_mem_read((t_byte *)&p->registers[reg_addr - 1], &a->mem, 4);
	}
	print(" => R%d ", reg_addr);
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
	return ;
}
#include "vm.h"

t_int32	vm_instr_get_param(t_int32 *param, t_arena *a, t_process *p, int index)
{
	t_uint8	reg_addr;
	t_int16	ind_offset;

	if (p->current_instruction.args[index].type == REG_CODE)
	{
		vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[index].data);
		print("param %d: reg addr: %d\n", index, (int)reg_addr);
		if (reg_addr > 16)
		{
			print("reg addr > 16\n");
			return (0);
		}
		vm_reg_store((t_byte *)param, &p->registers[reg_addr - 1]);
	}
	else if (p->current_instruction.args[index].type == DIR_CODE)
		vm_reg_store((t_byte *)param, &p->current_instruction.args[index].data);
	else
	{
		vm_reg_store((t_byte *)&ind_offset, &p->current_instruction.args[index].data);
		print("param %d: ind_offset: %d\n", index, (int)ind_offset);
		vm_mem_set_pos(&a->mem, p->pc + ind_offset);
		vm_mem_read((t_byte *)param, &a->mem, REG_SIZE);
	}
	print("param %d: %d\n", index, (int)*param);
	return (1);
}

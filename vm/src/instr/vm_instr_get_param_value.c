#include "vm.h"

t_int32	vm_instr_get_param_value(t_int32 *param, t_arena *a, t_process *p, int index)
{
	t_int8	reg_addr;
	t_int16	dir_value;
	t_int16	ind_offset;
	t_size	i;

	*param = 0;
	print(" => param %d: ", index);
	if (p->current_instruction.args[index].type == REG_CODE)
	{
		vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[index].data);
		print("reg addr: %d ", (int)reg_addr);
		if (reg_addr <= 0 || reg_addr > 16)
		{
			print("invalid register address\n");
			return (0);
		}
		vm_reg_store((t_byte *)param, &p->registers[reg_addr - 1]);
		print("=> value: %d", (int)*param);
	}
	else if (p->current_instruction.args[index].type == DIR_CODE)
	{
		if (p->current_instruction.args[index].data.len == 2)
		{
			vm_reg_store((t_byte *)&dir_value, &p->current_instruction.args[index].data);
			*param = (int)dir_value;
			print("=> value: %d", (int)*param);
		}
		else
		{
			vm_reg_store((t_byte *)param, &p->current_instruction.args[index].data);
			print("=> value: %d", (int)*param);
		}
	}
	else
	{
		vm_reg_store((t_byte *)&ind_offset, &p->current_instruction.args[index].data);
		print("ind_offset: %d ", (int)ind_offset);
		vm_mem_set_pos(&a->mem, (t_size)((int)p->pc + ind_offset));
		vm_mem_read((t_byte *)param, &a->mem, REG_SIZE);
		vm_reverse_bytes(param, param, REG_SIZE);
		print("=> value: %d", (int)*param);
	}
	print(" [");
	i = 0;
	while (i < 4)
	{
		print("%02x", ((t_byte *)param)[i]);
		if (i < 3)
			print(" ");
		i++;
	}
	print("]\n");
	return (1);
}

#include "vm.h"

t_int64	vm_get_val(
		t_arena *a,
		t_process *p,
		t_argument arg,
		t_size *mem_i)
{
	if (arg.type == T_REG)
	{
		vm_reverse_bytes(&arg.value, vm_get_reg_addr(p, a->mem[*mem_i]),
		 REG_SIZE);
		*mem_i = (*mem_i + REG_ADDR_SIZE) % MEM_SIZE;
	}
	else if (arg.type == IND_CODE)
	{
		vm_reverse_bytes(&arg.value,
		vm_get_mem_addr(a, a->mem[*mem_i]), IND_ADDR_SIZE);
		*mem_i = (*mem_i + REG_ADDR_SIZE) % MEM_SIZE;
	}
	else
	{
		vm_reverse_bytes(&arg.value, vm_get_mem_addr(a, *mem_i), arg.size);
		*mem_i = (*mem_i + arg.size) % MEM_SIZE;
	}
	return (arg.value);
}
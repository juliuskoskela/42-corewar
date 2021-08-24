#include "vm.h"

t_int64 vm_get_val(
		t_arena *a,
		t_process *p,
		t_uint8 acb,
		t_size *mem_i)
{
	t_int64	arg;

	arg = 0;
	if (acb == REG_CODE)
	{
		vm_reverse_bytes(&arg, vm_get_reg_addr(p, a->mem[*mem_i]), REG_SIZE);
		*mem_i = (*mem_i + REG_ADDR_SIZE) % MEM_SIZE;
	}
	else if (acb == IND_CODE)
	{
		vm_reverse_bytes(&arg, vm_get_mem_addr(a, a->mem[*mem_i]), IND_ADDR_SIZE);
		*mem_i = (*mem_i + IND_ADDR_SIZE) % MEM_SIZE;
	}
	else if (acb == DIR_CODE)
	{
		vm_reverse_bytes(&arg, vm_get_mem_addr(a, *mem_i), DIR_VAL_SIZE);
		*mem_i = (*mem_i + DIR_VAL_SIZE) % MEM_SIZE;
	}
	else
		vm_error("Error args!\n");
	return (arg);
}

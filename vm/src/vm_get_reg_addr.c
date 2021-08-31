#include "vm.h"

t_reg_addr vm_get_reg_addr(
		t_process *p,
		t_size i)
{
	if (i < 1 || i > 16)
	{
		print("Reg out of bounds!\n");
		return (NULL);
	}
	return (&p->registers[i - 1]);
}

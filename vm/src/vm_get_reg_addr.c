#include "vm.h"

t_reg_addr vm_get_reg_addr(
		t_process *p,
		t_size i)
{
	return (&p->registers[i - 1]);
}

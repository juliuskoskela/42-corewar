#include "vm.h"

t_mem_addr vm_get_mem_addr(
		t_arena *a,
		t_size i)
{
	return (&a->mem[i  % MEM_SIZE]);
}

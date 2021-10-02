#include "../inc/vm.h"

void	vm_mem_free(t_mem *src)
{
	if (!src)
		return ;
	free(src->mem);
	src->mem = NULL;
	src->pos = 0;
	src->len = 0;
}

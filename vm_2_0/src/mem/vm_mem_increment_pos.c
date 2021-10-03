#include "vm.h"

void	vm_mem_increment_pos(t_mem *src, t_size i)
{
	src->pos = (src->pos + i) % src->len;
}

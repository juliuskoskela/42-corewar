#include "vm.h"

t_mem	*vm_mem_set_pos(t_mem *src, t_size pos)
{
	if (!src)
		return (NULL);
	src->pos = pos % src->len;
	return (src);
}

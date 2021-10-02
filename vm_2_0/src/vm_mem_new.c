#include "../inc/vm.h"

t_mem	*vm_mem_new(t_mem *src, t_size len)
{
	src->mem = minit(sizeof(t_byte) * len);
	if (!src->mem)
		return (NULL);
	src->pos = 0;
	src->len = len;
	return (src);
}

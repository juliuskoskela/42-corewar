#include "vm.h"

t_bool	vm_mem_write(t_mem *dst, t_byte *src, size_t src_len)
{
	t_size	i;

	if (!dst || !src)
		return (FALSE);
	i = 0;
	while (i < src_len)
	{
		dst->mem[dst->pos] = src[i];
		vm_mem_increment_pos(dst, 1);
		i++;
	}
	return (TRUE);
}

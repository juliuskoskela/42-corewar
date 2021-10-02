#include "../inc/vm_2.h"

t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t dst_len)
{
	t_size	i;

	if (!dst || !src)
		return (FALSE);
	i = 0;
	while (i < dst_len)
	{
		dst[i] = src->mem[src->pos];
		mem_increment_pos(src, 1);
		i++;
	}
	return (TRUE);
}

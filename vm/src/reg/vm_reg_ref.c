#include "vm.h"

void	vm_reg_ref(t_reg *dst, t_byte *src)
{
	t_size	i;

	if (!dst || !src)
		return ;
	i = 0;
	if (ENDIAN_LITTLE)
	{
		while (i < dst->len)
		{
			dst->mem[dst->len - 1 - i] = src[i];
			i++;
		}
	}
	else
	{
		while (i < dst->len)
		{
			dst->mem[i] = src[i];
			i++;
		}
	}
}

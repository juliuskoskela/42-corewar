#include "reg.h"
#include "vm.h"

void	vm_reg_deref(t_byte *dst, t_reg *src)
{
	t_size	i;

	if (!dst || !src)
		return ;
	i = 0;
	if (ENDIAN_LITTLE)
	{
		while (i < src->len)
		{
			dst[i] = src->mem[src->len - 1 - i];
			i++;
		}
	}
	else
	{
		while (i < src->len)
		{
			dst[i] = src->mem[i];
			i++;
		}
	}
}

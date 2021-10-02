#include "vm.h"

void	reg_print(t_reg *src, char *colour)
{
	t_uint64	deref;
	t_size		i;

	if (!src || !src->len)
		return ;
	i = 0;
	print("%s[");
	while (i < src->len - 1)
	{
		print("0x%02x ", src->mem[i]);
		i++;
	}
	print("0x%02x", src->mem[i]);
	print("]%s", NRM);
	deref = 0;
	reg_deref((t_byte *)&deref, src);
	print(" %llu", deref);
}

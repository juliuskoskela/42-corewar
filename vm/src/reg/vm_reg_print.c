#include "vm.h"

void	vm_reg_print(t_reg *src)
{
	t_int32	deref;
	t_size		i;

	if (!src || !src->len)
	{
		print("[NULL]");
		return ;
	}
	i = 0;
	print("[");
	while (i < src->len - 1)
	{
		print("0x%02x ", src->mem[i]);
		i++;
	}
	print("0x%02x", src->mem[i]);
	print("]");
	deref = 0;
	vm_reg_store((t_byte *)&deref, src);
	print(" %d", deref);
}

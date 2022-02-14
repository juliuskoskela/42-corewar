#include "vm.h"

void	vm_mem_print_overlay(t_mem *src, t_size start, t_size len, char *colour)
{
	t_size	i;
	t_size 	rem;

	rem = (start + len) % src->len;
	i = 0;
	while (i < src->len)
	{
		if (i % ROW_SIZE == 0)
			print("\n");
		if (i == start || (rem > 0 && i == 0))
			print("%s", colour);
		print("%02x ", src->mem[i]);
		if (i == start + len || (rem > 0 && i == rem - 1))
			print("%s", NRM);
		i++;
	}
	print("%s\n\n", NRM);
}

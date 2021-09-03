#include "vm.h"

void	vm_print_bytes(void *memory, size_t len)
{
	t_byte	*bytes;
	size_t	i;

	bytes = (t_byte *)memory;
	i = 0;
	while (i < len)
	{
		print("%02x ", (unsigned int)bytes[i]);
		i++;
	}
}

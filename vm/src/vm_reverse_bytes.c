#include "vm.h"

/*
**	In the bytecode the magic code and prog_size are stored as little endian.
**	This function returns the bytes in big endian. All data in the header
**	struct is stored in big endian.
*/

void	*vm_reverse_bytes(void *dst, void *src, t_size size)
{
	t_byte	*tmp;
	t_byte	*dst_ptr;
	t_size	i;

	tmp = minit(size);
	if (!tmp)
		vm_exit_error("malloc failed \n");
	mcpy_safe(tmp, src, size);
	dst_ptr = (t_byte *)dst;
	i = 0;
	while (size--)
	{
		dst_ptr[i++] = tmp[size];
	}
	mdel((void **)&tmp);
	return ((void *)dst);
}

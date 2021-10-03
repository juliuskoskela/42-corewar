#include "vm.h"

t_arg	*vm_arg_read(t_arg *dst, t_mem *src)
{
	vm_mem_read((t_byte *)&dst->data.mem, src, dst->data.len);
	return (dst);
}

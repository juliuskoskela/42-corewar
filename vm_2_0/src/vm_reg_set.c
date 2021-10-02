#include "vm.h"

t_reg	*vm_reg_set(t_reg *src, t_size len)
{
	mzero(&src->mem, REG_SIZE);
	src->len = len;
	return (src);
}

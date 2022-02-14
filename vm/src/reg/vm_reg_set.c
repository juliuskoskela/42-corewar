#include "vm.h"

t_reg	*vm_reg_set_size(t_reg *src, t_size len)
{
	mzero(&src->mem, REG_SIZE);
	src->len = len;
	return (src);
}

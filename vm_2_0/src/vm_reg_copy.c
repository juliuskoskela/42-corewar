#include "vm.h"

void	vm_reg_copy(t_reg *dst, t_reg *src)
{
	mcpy(dst->mem, src->mem, src->len);
}

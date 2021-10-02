#include "vm.h"

t_arg	*vm_arg_new(t_arg *dst, t_uint8 type, t_uint8 promoted)
{
	mzero(dst, sizeof(t_arg));
	dst->type = type;
	if (type == DIR_CODE)
	{
		if (promoted == TRUE)
		{
			dst->promoted = TRUE;
			dst->data.len = REG_SIZE;
		}
		else
			dst->data.len = DIR_VAL_SIZE;
	}
	else if (type == IND_CODE)
		dst->data.len = IND_ADDR_SIZE;
	else if (type == REG_CODE)
		dst->data.len = REG_ADDR_SIZE;
	else
		dst->data.len = 1;
	return (dst);
}

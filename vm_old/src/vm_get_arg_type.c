#include "vm.h"

t_uint8	vm_get_arg_type(
		t_uint8 acb,
		t_size arg_i)
{
	t_uint8	mask;

	mask = 0b11000000 >> (arg_i * 2);
	return ((acb & mask) >> (6 - (arg_i * 2)));
}

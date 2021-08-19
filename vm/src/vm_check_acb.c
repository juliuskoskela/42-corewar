#include "vm.h"

// Take an argument coding byte acb and arg_i which represents the
// which argument is in question. Masks that part from the acb and
// shifts the results to the least significant bit.

t_uint8	vm_check_acb(
		t_uint8 acb,
		t_size arg_i)
{
	t_uint8	mask;

	mask = 0b11000000 >> (arg_i * 2);
	return ((acb & mask) >> (6 - (arg_i * 2)));
}

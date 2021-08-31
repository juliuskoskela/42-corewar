#include "vm.h"

// Take an argument coding byte acb and arg_i which represents the
// which argument is in question. Masks that part from the acb and
// shifts the results to the least significant bit.

t_uint8	vm_get_arg_type(
		t_uint8 acb,
		t_size arg_i)
{
	t_uint8	mask;

	mask = 0b11000000 >> (arg_i * 2);
	return ((acb & mask) >> (6 - (arg_i * 2)));
}

t_uint8 vm_check_acb(
		t_uint8 acb,
		t_size op)
{
	t_param_types arg;

	arg = g_op_tab[op - 1].param_types;
	print("op %s", g_op_tab[op - 1].description);
	if ((vm_get_arg_type(acb, 0) & arg.param1) == 0 && arg.param1)
		print("acb %d does not match arg1 %d\n", vm_get_arg_type(acb, 0), arg.param1);
	if ((vm_get_arg_type(acb, 1) & arg.param2) == 0 && arg.param2)
		print("acb does not match arg2\n");
	if ((vm_get_arg_type(acb, 2) & arg.param3) == 0 && arg.param3)
		print("acb does not match arg3\n");
	return(1);
}

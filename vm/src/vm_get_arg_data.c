#include "vm.h"

t_uint8	vm_get_arg_size(
		t_uint8 acb,
		t_uint8 opcode,
		t_uint8 arg_i)
{
	if (opcode == 2 && arg_i == 1 && vm_get_arg_type(acb, 1) == DIR_CODE)
		return (REG_SIZE);
	else if (opcode == 6 && (arg_i == 1 || arg_i == 2) &&
	vm_get_arg_type(acb, arg_i) == DIR_CODE)
		return (REG_SIZE);
	else if (opcode == 7 && (arg_i == 1 || arg_i == 2) &&
	vm_get_arg_type(acb, arg_i) == DIR_CODE)
		return (REG_SIZE);
	else if (opcode == 8 && (arg_i == 1 || arg_i == 2) &&
	vm_get_arg_type(acb, arg_i) == DIR_CODE)
		return (REG_SIZE);
	else if (opcode == 14 && (arg_i == 1 || arg_i == 2) &&
	vm_get_arg_type(acb, arg_i) == DIR_CODE)
		return (REG_SIZE);
	else if (vm_get_arg_type(acb, arg_i) == DIR_CODE)
		return (DIR_VAL_SIZE);
	else if (vm_get_arg_type(acb, arg_i) == IND_CODE)
		return (IND_ADDR_SIZE);
	else
		return (REG_SIZE);
}

t_argument	vm_get_arg_data(
		t_uint8 acb,
		t_uint8 opcode,
		t_uint8 arg_i)
{
	t_argument arg;

	arg.type = vm_get_arg_type(acb, arg_i);
	arg.size = vm_get_arg_size(acb, opcode, arg_i);
	arg.value = 0;
	return (arg);
}

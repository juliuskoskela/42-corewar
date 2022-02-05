#include "vm.h"

void	vm_print_instr_arg(t_arg *arg)
{
	print("%s%s%s ", BLU, vm_type_name(arg->type), NRM);
	vm_reg_print(&arg->data);
}

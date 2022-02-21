#include "vm.h"

void	vm_print_instr_arg(t_arg *arg)
{
	print("%s ", vm_type_name(arg->type));
	vm_reg_print(&arg->data);
}

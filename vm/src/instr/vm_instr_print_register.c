#include "vm.h"

void	vm_instr_print_register(char *msg, t_int8 reg_addr, t_process *p)
{
	print(msg, reg_addr);
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
}

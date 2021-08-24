#include "vm.h"

// Converts the value of the first argument (T_REG) into type char
// and prints it to standard output.
//
// In the original, the output of the aff is switched on using the -a flag.

void	vm_instr_aff(
		t_arena *a,
		t_process *p)
{
	t_size	mem_i;
	t_uint8	acb;
	char	out;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "aff chr");
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	if (vm_check_acb(acb, 0) != REG_CODE)
		vm_error("Error arg 1 sti!\n");
	mem_i = (mem_i + 1) % MEM_SIZE;
	out = (char)*vm_get_reg_addr(p, mem_i);
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\taff %c\n", out);
	print("%c", out);
	mem_i += REG_ADDR_SIZE % MEM_SIZE;
	if ((a->verbosity & VM_VERBOSE_PC) != 0)
		print("\tPC: %d => %d\n", (int)p->pc, (int)mem_i);
	p->pc = mem_i;
}

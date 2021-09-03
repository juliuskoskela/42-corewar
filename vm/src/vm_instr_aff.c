#include "vm.h"

// Converts the value of the first argument (T_REG) into type char
// and prints it to standard output.
//
// In the original, the output of the aff is switched on using the -a flag.

void	vm_instr_aff(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_reg_addr	reg;
	char		out;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t\t%s\n", "aff chr");
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	if (!vm_check_acb(acb, p->current_instruction.opcode))
	{
		vm_advance_pc(&p->pc, 1, a->mem, a->verbosity);
		return ;
	}
	mem_i = (mem_i + 1) % MEM_SIZE;
	reg = vm_get_reg_addr(p, mem_i);
	if (reg == NULL)
	{
		vm_advance_pc(&p->pc, 1, a->mem, a->verbosity);
		return ;
	}
	out = (char)*reg;
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t\taff %c\n", out);
	print("Aff: %c\n", out);
	mem_i = (mem_i + REG_ADDR_SIZE) % MEM_SIZE;
	vm_advance_pc(&p->pc, mem_i - p->pc, a->mem, a->verbosity);
}

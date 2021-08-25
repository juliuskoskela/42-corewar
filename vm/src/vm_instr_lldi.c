#include "vm.h"

// Loads the value from address (FIRST_PARAMETER + SECOND_PARAMETER)
// and loads it to the T_REG in THIRD_PARAMETER.

void vm_instr_lldi(
		t_arena *a,
		t_process *p)
{
	t_int64		rhs;
	t_int64		lhs;
	t_size		mem_i;
	t_uint8		acb;
	t_reg_addr	dst;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "lldi lhs, rhs, dst");
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	mem_i = (p->pc + 1) % MEM_SIZE;

	lhs = vm_get_val(a, p, vm_get_arg_data(acb, 14, 1), &mem_i);

	rhs = vm_get_val(a, p, vm_get_arg_data(acb, 14, 2), &mem_i);

	dst = vm_get_reg_addr(p, a->mem[mem_i]);
	*dst = (lhs + rhs) % MEM_SIZE;
	if ((a->verbosity & VM_VERBOSE_PC) != 0)
		print("\tPC: %d => %d\n", (int)p->pc, (int)mem_i);
	p->pc = mem_i;
}

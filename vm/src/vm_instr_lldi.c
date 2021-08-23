#include "vm.h"

// Loads the value from address (FIRST_PARAMETER + SECOND_PARAMETER)
// and loads it to the T_REG in THIRD_PARAMETER.

void vm_instr_lldi(	
		t_arena *a,
		t_process *p)
{
	t_uint64	rhs;
	t_uint64	lhs;
	t_size		mem_i;
	t_uint8		acb;
	t_reg_addr	dst;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "lldi lhs, rhs, dst");
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	if (vm_check_acb(acb, 0) != REG_CODE &&
		vm_check_acb(acb, 0) != DIR_CODE &&
		vm_check_acb(acb, 0) != IND_CODE)
			vm_error("Error arg 1 ldi\n");
	mem_i = (p->pc + 1) % MEM_SIZE;
	lhs = vm_get_val(a, p, vm_check_acb(acb, 1), &mem_i);

	if (vm_check_acb(acb, 1) != REG_CODE
	&& vm_check_acb(acb, 1) != DIR_CODE)
		vm_error("Error arg 2 ldi\n");
	rhs = vm_get_val(a, p, vm_check_acb(acb, 2), &mem_i);

	if (vm_check_acb(acb, 2) != REG_CODE)
		vm_error("Error arg 3 ldi\n");
	dst = vm_get_reg_addr(p, a->mem[mem_i]);
	*dst = (lhs + rhs) % MEM_SIZE;
}
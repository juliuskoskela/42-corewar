#include "vm.h"

// STI (T_REG src, (T_REG | T_DIR | T_IND) lhs, T_DIR | T_REG rhs
// Computes lhs + rhs and uses the result as an offset to address memory
// and store the value of the register src at that memory location.

void vm_instr_sti(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_mem_addr	dst;
	t_reg_addr	src;
	t_uint64	lhs;
	t_uint64	rhs;

	// acb
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];

	// arg 1
	if (vm_check_acb(acb, 0) != REG_CODE)
		vm_error("Error arg 1 sti!\n");
	mem_i = (mem_i + 1) % MEM_SIZE;
	src = vm_get_reg_addr(p, a->mem[mem_i] - 1);
	mem_i = (mem_i + 1) % MEM_SIZE;

	// arg 2
	if (vm_check_acb(acb, 1) != REG_CODE
		&& vm_check_acb(acb, 1) != IND_CODE
		&& vm_check_acb(acb, 1) != DIR_CODE)
		vm_error("Error arg 2 sti!\n");
	lhs = vm_get_val(a, p, vm_check_acb(acb, 1), &mem_i);

	// arg 3
	if (vm_check_acb(acb, 2) != REG_CODE
		&& vm_check_acb(acb, 2) != DIR_CODE)
		vm_error("Error arg 3 sti!\n");
	rhs = vm_get_val(a, p, vm_check_acb(acb, 2), &mem_i);

	// store at index
	print("(%d + %d) + pc = %d + %d => %d \n", lhs, rhs, lhs + rhs, p->pc, lhs + rhs + p->pc);
	dst = vm_get_mem_addr(a, p->pc + lhs + rhs);
	vm_reverse_bytes(dst, src, REG_SIZE);
	p->pc = mem_i;
}

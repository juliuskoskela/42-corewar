#include "vm.h"

// ADD (T_REG lhs, T_REG rhs, T_REG dst)
// Computes lhs + rhs and stores the result in the register dst. The result affects zf.

void vm_instr_add(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_mem_addr	dst;
	t_uint64	lhs;
	t_uint64	rhs;
	t_uint64	res;

	// acb
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	mem_i = (mem_i + 1) % MEM_SIZE;
	
	// arg 1
	if (vm_check_acb(acb, 1) != REG_CODE)
		vm_error("Error arg 1 sti!\n");
	lhs = vm_get_val(a, p, vm_check_acb(acb, 1), &mem_i);

	// arg 2
	if (vm_check_acb(acb, 2) != REG_CODE)
		vm_error("Error arg 2 sti!\n");
	rhs = vm_get_val(a, p, vm_check_acb(acb, 2), &mem_i);

	// arg 3
	if (vm_check_acb(acb, 0) != REG_CODE)
		vm_error("Error arg 3 sti!\n");
	dst = vm_get_reg_addr(p, a->mem[mem_i]);
	mem_i = (mem_i + 1) % MEM_SIZE;

	// store at index
	res = lhs + rhs;
	vm_reverse_bytes(dst, &res, REG_SIZE);
	p->pc = mem_i;
}

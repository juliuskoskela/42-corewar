#include "vm.h"

void vm_instr_or(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_reg_addr	dst;
	t_int64		lhs;
	t_int64		rhs;

	// acb
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];

	// arg 1
	lhs = vm_get_val(a, p, vm_get_arg_data(acb, 8, 1), &mem_i);

	// arg 2
	rhs = vm_get_val(a, p, vm_get_arg_data(acb, 8, 2), &mem_i);

	// arg 3
	if (vm_get_arg_type(acb, 2) != REG_CODE)
		vm_error("Error arg 3 add!\n");
	dst = vm_get_reg_addr(p, a->mem[mem_i]);

	*dst = lhs | rhs;
	if (*dst == 0)
		p->zf = 1;
	else
		p->zf = 0;
	vm_reverse_bytes(dst, dst, REG_SIZE);
	p->pc = mem_i + 1;
}

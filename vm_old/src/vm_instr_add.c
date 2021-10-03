#include "vm.h"

void vm_instr_add(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_reg_addr	dst;
	t_int64		lhs;
	t_int64		rhs;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "add lhs, rhs, dst");
	// acb
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	mem_i = (mem_i + 1) % MEM_SIZE;


	//check acb
	if (!vm_check_acb(acb, 4))
		print("invalid acb in add\n");

	// arg 1
	lhs = vm_get_val(a, p, vm_get_arg_data(acb, 4, 1), &mem_i);

	// arg 2
	rhs = vm_get_val(a, p, vm_get_arg_data(acb, 4, 2), &mem_i);

	// arg 3
	dst = vm_get_reg_addr(p, a->mem[mem_i]);

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
	{
		print("\tadd %d + %d = %d to %d\n",
			(int)lhs, (int)rhs, (int)(lhs + rhs), a->mem[mem_i]);
	}
	*dst = lhs + rhs;
	if (*dst == 0)
		p->zf = 1;
	else
		p->zf = 0;
	vm_reverse_bytes(dst, dst, REG_SIZE);
	p->pc = mem_i + 1;
}

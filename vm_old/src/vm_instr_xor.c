#include "vm.h"

//note to self. If negative indirect value is used as an index in mem array
// it might go out of segment.

//and performs a "exclusive or" statement for the values ​of the first two
// arguments T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR
// and writes the result to the T_REG passed as the third argument

void vm_instr_xor(
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

	// check arguments
	if (!vm_check_acb(acb, 8))
		print("invalid acb in xor\n");

	lhs = vm_get_val(a, p, vm_get_arg_data(acb, 8, 1), &mem_i);


	// arg 2

	rhs = vm_get_val(a, p, vm_get_arg_data(acb, 8, 2), &mem_i);

	// arg 3

	dst = vm_get_reg_addr(p, a->mem[mem_i]);

	*dst = lhs ^ rhs;
	if (*dst == 0)
		p->zf = 1;
	else
		p->zf = 0;
	vm_reverse_bytes(dst, dst, REG_SIZE);
	p->pc = mem_i + 1;
}

// get_argument_data
// get_argument_value
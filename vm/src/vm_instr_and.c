#include "vm.h"

void vm_instr_and(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_reg_addr	dst;
	t_int64		lhs;
	t_int64		rhs;
	t_int64		result;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t\t%s\n", "and lhs, rhs, dst");
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	if (!vm_check_acb(acb, p->current_instruction.opcode))
	{
		vm_advance_pc(&p->pc, 1, a->mem, a->verbosity);
		return ;
	}
	mem_i = (mem_i + 1) % MEM_SIZE;
	lhs = vm_get_val(a, p, vm_get_arg_data(acb, p->current_instruction.opcode, 0), &mem_i);
	rhs = vm_get_val(a, p, vm_get_arg_data(acb, p->current_instruction.opcode, 1), &mem_i);
	dst = vm_get_reg_addr(p, a->mem[mem_i]);
	if (dst == NULL)
	{
		vm_advance_pc(&p->pc, 1, a->mem, a->verbosity);
		return ;
	}
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
	{
		print("\t\t%d & %d = %d to r%d\n",
			(int)lhs, (int)rhs, (int)(lhs & rhs), a->mem[mem_i]);
	}
	result = lhs & rhs;
	vm_reverse_bytes(dst, &result, REG_SIZE);
	if (*dst == 0)
		p->zf = 1;
	else
		p->zf = 0;
	mem_i = (mem_i + 1) % MEM_SIZE;
	vm_advance_pc(&p->pc, mem_i - p->pc, a->mem, a->verbosity);
}

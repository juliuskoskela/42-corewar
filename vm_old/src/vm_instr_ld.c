#include "vm.h"

// ld T_DIR | T_IND src, T_REG dst
// if first argument is T_DIR, it is 4 bytes T_IND is 2 bytes.
// Contains ACB
// If the first argument is T_IND, it represents the memory addr % IDX_MOD.
// Loads src in the register dst. src's value affects zf.

void	vm_instr_ld(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_mem_addr	src;
	t_reg_addr	dst;
	t_int64		mem_addr;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "ld src, dst");
	// acb
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	mem_i = (mem_i + 1) % MEM_SIZE;

	//check arguments
	if (!vm_check_acb(acb, p->current_instruction.opcode))
		print("acb does not match the arguments");

	// arg 1
	mem_addr = vm_get_val(a, p, vm_get_arg_data(acb, p->current_instruction.opcode, 0), &mem_i);
	if (vm_get_arg_type(acb, 0) == IND_CODE)
		mem_addr = mem_addr % IDX_MOD;
	src = vm_get_mem_addr(a, mem_addr);

	// arg 2
	dst = vm_get_reg_addr(p, a->mem[mem_i]);
	mem_i = (mem_i + 1) % MEM_SIZE;

	// store load to register
	vm_reverse_bytes(dst, src, REG_SIZE);
	if ((a->verbosity & VM_VERBOSE_PC) != 0)
	{
		vm_print_process(p);
		print("\tPC: %d => %d\n", (int)p->pc, (int)mem_i);
	}
	p->pc = mem_i;
}

#include "vm.h"

// lld T_DIR | T_IND src, T_REG dst
// Contains ACB
// Loads src in the register dst. src's value affects zf.

void vm_instr_lld(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_mem_addr	src;
	t_reg_addr	dst;
	t_int64		mem_addr;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "lld src, dst");
	// acb
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	mem_i = (mem_i + 1) % MEM_SIZE;

	// arg 1
	if (vm_check_acb(acb, 0) != DIR_CODE
		&& vm_check_acb(acb, 0) != IND_CODE)
		vm_error("Error arg 1 sti!\n");
	mem_addr = vm_get_val(a, p, vm_check_acb(acb, 0), &mem_i);
	src = vm_get_mem_addr(a, mem_addr);

	// arg 2
	if (vm_check_acb(acb, 1) != REG_CODE)
		vm_error("Error arg 2 sti!\n");
	dst = vm_get_reg_addr(p, a->mem[mem_i]);

	// store load to register
	print("mem addr = %d\n", mem_addr);
	vm_reverse_bytes(dst, src, 2);
	if ((a->verbosity & VM_VERBOSE_PC) != 0)
		print("\tPC: %d => %d\n", (int)p->pc, (int)mem_i);
	p->pc = mem_i;
}

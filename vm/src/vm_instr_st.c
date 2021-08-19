#include "vm.h"

void vm_instr_st(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_byte		*dst;
	t_byte		*src;

	dst = NULL;
	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	if (vm_check_acb(acb, 0) != REG_CODE)
		vm_error("Error st arg1!\n");
	mem_i = (mem_i + 1) % MEM_SIZE;
	src = (t_byte *)&p->registers[a->mem[mem_i]];
	mem_i = (mem_i + 1) % MEM_SIZE;
	if (vm_check_acb(acb, 1) == REG_CODE)
		dst = (t_byte *)&p->registers[a->mem[mem_i]];
	else if (vm_check_acb(acb, 1) == IND_CODE)
		dst = (t_byte *)&a->mem[a->mem[mem_i] + p->pc];
	else
		vm_error("Error st arg2!\n");
	vm_reverse_bytes(dst, src, REG_SIZE);
	p->pc = (mem_i + 1) % MEM_SIZE;
}

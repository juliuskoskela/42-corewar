#include "vm.h"

// 3 : { (T_REG), (T_REG | T_DIR | T_IND), (T_DIR | T_REG) }
// sti src, lhs, rhs
// Computes lhs + rhs and uses the result as an offset to address memory
// and store the value of the register src at that memory location.

typedef t_byte* t_mem_addr;
typedef t_uint64* t_reg_addr;

t_reg_addr	vm_get_reg_addr(t_process *p, t_size i)
{
	return (&p->registers[i]);
}

t_mem_addr	vm_get_mem_addr(t_arena *a, t_size i)
{
	return (&a->mem[i  % MEM_SIZE]);
}

t_uint64 vm_get_val(
		t_arena *a,
		t_process *p,
		t_uint8 acb,
		t_size *mem_i)
{
	t_uint64	arg;

	arg = 0;
	if (acb == REG_CODE)
	{
		vm_reverse_bytes(&arg, vm_get_reg_addr(p, a->mem[*mem_i] - 1), REG_SIZE);
		*mem_i = (*mem_i + REG_ADDR_SIZE) % MEM_SIZE;
	}
	else if (acb == IND_CODE)
	{
		vm_reverse_bytes(&arg, vm_get_mem_addr(a, a->mem[*mem_i]), IND_ADDR_SIZE);
		*mem_i = (*mem_i + IND_ADDR_SIZE) % MEM_SIZE;
	}
	else if (acb == DIR_CODE)
	{
		vm_reverse_bytes(&arg, vm_get_mem_addr(a, *mem_i), DIR_VAL_SIZE);
		*mem_i = (*mem_i + DIR_VAL_SIZE) % MEM_SIZE;
	}
	else
		vm_error("Error args!\n");
	return (arg);
}

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

	// arg 2
	mem_i = (mem_i + 1) % MEM_SIZE;
	if (vm_check_acb(acb, 1) != REG_CODE
		&& vm_check_acb(acb, 1) != IND_CODE
		&& vm_check_acb(acb, 1) != DIR_CODE)
		vm_error("Error arg 2 sti!\n");
	lhs = vm_get_val(a, p, vm_check_acb(acb, 1), &mem_i);

	// arg 3
	if (vm_check_acb(acb, 1) != REG_CODE
		&& vm_check_acb(acb, 1) != DIR_CODE)
		vm_error("Error arg 3 sti!\n");
	rhs = vm_get_val(a, p, vm_check_acb(acb, 2), &mem_i);

	// store at index
	print("%d + %d = %d\n", lhs, rhs, lhs + rhs);
	dst = vm_get_mem_addr(a, lhs + rhs);
	vm_reverse_bytes(dst, src, REG_SIZE);
	p->pc = mem_i;
}

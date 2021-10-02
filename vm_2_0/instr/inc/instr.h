#ifndef INSTR_H
# define INSTR_H

# include "vm.h"
# include "corewar.h"

void	vm_instr_ld(t_arena *a, t_process *p);
void	vm_instr_null(t_arena *a, t_process *p);

static const t_exec g_instr_funcs[] =
{
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
};

#endif
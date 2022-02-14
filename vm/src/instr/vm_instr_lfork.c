/// opcode:		15 (0x0f)
/// mnemonic:	lfork
/// name:		lfork
/// params:		1 : { T_DIR }
/// acb:		false
/// ncycles:	1000
/// proto:		lfork offset
/// descript:	Long version of fork. Forks this process: effectively creates a new process that inherits the current process' registers and zf. The spawned process has its PC set to his parent's PC offseted by offset.

#include "vm.h"

void	vm_instr_lfork(t_arena *a, t_process *p)
{
	t_int32     offset;
	t_process	*new;

	//Save first argument T_DIR value
	vm_reg_store((t_byte *)&offset, &p->current_instruction.args[0].data);
	new = minit(sizeof(t_process));
	if (!new)
		vm_exit_error("Malloc fail\n");
	mcpy(new, p, sizeof(t_process));
	new->pc = (p->pc + offset) % MEM_SIZE;
	new->next = a->processes;
	new->cycles_before_execution = -1;
	mzero(&new->current_instruction, sizeof(t_instr));
	a->processes = new;
	vm_test_fork(a->processes);
}
// Check the byte in memory that the process->pc is pointing to.
// Validate opcode and save the opcode and cycles_before_execution.
// Rest of the memory will be read on the cycle of execution.

#include "vm.h"

t_op	*vm_get_instruction(t_byte opcode)
{
	int	i;

	i = 0;
	while (g_op_tab[i].mnemonic != 0)
	{
		if (opcode == g_op_tab[i].opcode)
			return ((t_op *)&g_op_tab[i]);
		i++;
	}
	return (NULL);
}

void	vm_init_instruction_execution(t_process *process, t_arena *arena)
{
	t_byte	opcode;
	t_op	*instruction;

	vm_mem_set_pos(&arena->mem, process->pc);
	vm_mem_read(&opcode, &arena->mem, 1);
	instruction = vm_get_instruction(opcode);
	if (instruction == NULL)
		vm_increment_process_pc(process, 1, 0);
	else
	{
		mzero(&process->current_instruction,
			sizeof(process->current_instruction));
		process->current_instruction.opcode = opcode;
		process->current_instruction.op = instruction;
		process->cycles_before_execution = (int)instruction->cycles;
		if (!vm_read_instr_arguments(process, arena))
		{
			vm_process_debug("Error on reading arguments", arena->verbosity);
			vm_increment_process_pc(process, 2, arena->verbosity);
			return ;
		}
		if (opcode == 1)
			process->current_instruction = vm_validate_instr(process, arena);
	}
}

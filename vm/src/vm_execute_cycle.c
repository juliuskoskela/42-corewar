#include "vm.h"

void	vm_execute_instruction(t_process *process,
t_arena *arena)
{
	t_size	new_pc;

	if (!vm_read_instr_arguments(process, arena))
	{
		print("an error occured while reading arguments");
		return ;
	}
	vm_print_instr(arena, process);
	g_instr_funcs[process->current_instruction.opcode - 1](arena, process);
	new_pc = (process->pc + vm_instr_size(&process->current_instruction)) % MEM_SIZE;
	print(" => %s %d (%#06x) => %d (%#06x) \n", "pc: ", process->pc, process->pc, new_pc, new_pc);
	process->pc = new_pc;
}

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

// Check the byte in memory that the process->pc is pointing to.
// Validate opcode and save the opcode and cycles_before_execution.
// Rest of the memory will be read on the cycle of execution.

void	vm_init_instruction_execution(t_process *process, t_arena *arena)
{
	t_byte	opcode;
	t_op	*instruction;

	vm_mem_set_pos(&arena->mem, process->pc);
	vm_mem_read(&opcode, &arena->mem, 1);
	instruction = vm_get_instruction(opcode);
	if (instruction == NULL)
		process->pc++;
	else
	{
		mzero(&process->current_instruction, sizeof(process->current_instruction));
		process->current_instruction.opcode = opcode;
		process->current_instruction.op = instruction;
		process->cycles_before_execution = instruction->cycles;
//		print("Next instr to be executed: %s, wait %d cycles before execution\n", instruction->description, instruction->cycles); //test
	}
}

void	vm_execute_process(t_process *process, t_arena *arena)
{
	if (process->cycles_before_execution == -1)
		vm_init_instruction_execution(process, arena);
	if (process->cycles_before_execution > 0)
		process->cycles_before_execution--;
	if (process->cycles_before_execution == 0)
	{
		vm_execute_instruction(process, arena);
		process->cycles_before_execution = (-1);
	}
}

void	vm_execute_cycle(t_process *process, t_arena *arena)
{
	if ((arena->verbosity & VM_VERBOSE_CYCLES) != 0)
		print("This is cycle\t%d\n", arena->current_cycle);
	while (process)
	{
		vm_execute_process(process, arena);
		process = process->next;
	}
	arena->current_cycle++;
}

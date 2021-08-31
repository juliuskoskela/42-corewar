#include "vm.h"

void	vm_execute_instruction(t_op instruction, t_process *process,
t_arena *arena)
{
	print("P %d:\tat pc %d opcode %d => execute %s\n",
		(int)process->id,
		(int)process->pc,
		(int)arena->mem[process->pc],
		instruction.mnemonic);
	g_instr_funcs[instruction.opcode - 1](arena, process);
}

t_op	vm_get_instruction(t_byte opcode)
{
	int	i;

	i = 0;
	while (g_op_tab[i].mnemonic != 0)
	{
		if (opcode == g_op_tab[i].opcode)
			break ;
		i++;
	}
	return (g_op_tab[i]);
}

void	vm_init_instruction_execution(t_process *process, t_arena *arena)
{
	t_op	instruction;

	instruction = vm_get_instruction(arena->mem[process->pc]);
	if (instruction.mnemonic == 0)
		vm_advance_pc(&process->pc, 1);
	else
	{
		process->current_instruction = instruction;
		process->cycles_before_execution = instruction.cycles - 2;
	}
}

void	vm_finish_instruction_execution(t_process *process, t_arena *arena)
{
	vm_execute_instruction(process->current_instruction, process, arena);
	process->cycles_before_execution = - 2;
}

void	vm_execute_process(t_process *process, t_arena *arena)
{
	if (process->cycles_before_execution > 0)
		process->cycles_before_execution--;
	else if (process->cycles_before_execution == 0)
		vm_finish_instruction_execution(process, arena);
	else
		vm_init_instruction_execution(process, arena);
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
	arena->current_cycle += 1;
}

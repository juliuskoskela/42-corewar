#include "vm.h"

void	vm_execute_instruction(t_op instruction, t_process *process,
t_arena *arena)
{
	print("player %d: with opcode %d at pc %d, execute %s\n",
		(int)process->id,
		(int)arena->mem[process->pc],
		(int)process->pc,
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
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
	else
	{
		process->next_instruction.instruction = instruction;
		if (instruction.has_argument_coding_byte)
			process->next_instruction.acb = arena->mem[(process->pc + 1) % MEM_SIZE];
		else
			process->next_instruction.acb = 0;
		process->cycles_before_execution = instruction.cycles;
	}
}

void	vm_finish_instruction_execution(t_process *process, t_arena *arena)
{
	vm_execute_instruction(process->next_instruction.instruction, process, arena);
	process->cycles_before_execution = -1;
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
	while (process)
	{
		vm_execute_process(process, arena);
		process = process->next;
	}
	arena->battle.cycles_executed += 1;
}

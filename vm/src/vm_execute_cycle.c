#include "vm.h"

t_bool	vm_check_acb(t_acb acb, t_op *op)
{
	t_byte	arg;
	t_uint8	params[3];
	t_size	i;

	params[0] = op->param_types.param1;
	params[1] = op->param_types.param2;
	params[2] = op->param_types.param3;
	i = 0;
	while (i < op->param_count)
	{
		arg = g_arg_codes[acb.arg[i]];
		if ((arg & params[i]) == 0)
		{
			print("invalid argument");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

t_acb	vm_decompose_acb(t_byte acb)
{
	t_acb	out;

	out.arg[0] = (acb & 0b11000000) >> 6;
	out.arg[1] = (acb & 0b00110000) >> 4;
	out.arg[2] = (acb & 0b00001100) >> 2;
	return (out);
}

int	vm_check_arg_types(t_acb *acb, t_process *process, t_arena *arena)
{
	if (process->current_instruction.op->has_argument_coding_byte)
	{
		vm_mem_read(&process->current_instruction.acb, &arena->mem, 1);
		*acb = vm_decompose_acb(process->current_instruction.acb);
		if (!vm_check_acb(*acb, process->current_instruction.op))
		{
			process->pc += 2;
			return (0);
		}
	}
	else
	{
		acb->arg[0] = process->current_instruction.op->param_types.param1;
		acb->arg[1] = process->current_instruction.op->param_types.param2;
		acb->arg[2] = process->current_instruction.op->param_types.param3;
	}
	return (1);
}

int	vm_read_instr_arguments(t_process *process, t_arena *arena)
{
	t_acb	acb;
	t_bool	is_promoted;
	size_t	i;

	is_promoted = FALSE;
	vm_mem_set_pos(&arena->mem, process->pc + 1);
	if (!vm_check_arg_types(&acb, process, arena))
		return (0);
	// if (acb.arg[0] == REG_CODE || acb.arg[1] == REG_CODE || acb.arg[2] == REG_CODE)
	// 	is_promoted = TRUE;
	i = 0;
	while (i < process->current_instruction.op->param_count)
	{
		if (s_cmp(process->current_instruction.op->mnemonic, "live") == 0)
			is_promoted = TRUE;
		else if (s_cmp(process->current_instruction.op->mnemonic, "lldi") == 0
			|| s_cmp(process->current_instruction.op->mnemonic, "and") == 0
			|| s_cmp(process->current_instruction.op->mnemonic, "or") == 0
			|| s_cmp(process->current_instruction.op->mnemonic, "xor") == 0
			|| s_cmp(process->current_instruction.op->mnemonic, "ld") == 0)
		{
			if (acb.arg[i] == DIR_CODE)
				is_promoted = TRUE;
		}
		vm_arg_new(&process->current_instruction.args[i], acb.arg[i], is_promoted);
		vm_arg_read(&process->current_instruction.args[i], &arena->mem);
		i++;
	}
	return (1);
}

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

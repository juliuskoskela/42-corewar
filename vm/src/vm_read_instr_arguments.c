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
			print("invalid argument\n");
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
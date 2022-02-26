/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_instr_arguments.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:04 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:05 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bool	vm_check_acb(t_acb acb, t_op *op)
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
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_acb	vm_decompose_acb(t_byte acb)
{
	t_acb	out;

	out.arg[0] = (acb & 0xC0) >> 6;
	out.arg[1] = (acb & 0x30) >> 4;
	out.arg[2] = (acb & 0xC) >> 2;
	return (out);
}

static int	vm_check_arg_types(t_acb *acb, t_process *process, t_arena *arena)
{
	if (process->current_instruction.op->has_argument_coding_byte)
	{
		vm_mem_read(&process->current_instruction.acb, &arena->mem, 1);
		*acb = vm_decompose_acb(process->current_instruction.acb);
		if (!vm_check_acb(*acb, process->current_instruction.op))
			return (0);
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
	t_acb		acb;
	t_bool		is_promoted;
	size_t		i;
	const char	*instr;

	is_promoted = FALSE;
	vm_mem_set_pos(&arena->mem, process->pc + 1);
	if (!vm_check_arg_types(&acb, process, arena))
		return (0);
	instr = process->current_instruction.op->mnemonic;
	i = 0;
	while (i < process->current_instruction.op->param_count)
	{
		if (s_cmp(instr, "live") == 0)
			is_promoted = TRUE;
		else if (acb.arg[i] == DIR_CODE && (!(s_ncmp(instr, "lld", 3))
				|| !s_cmp(instr, "and") || !s_cmp(instr, "or")
				|| !s_cmp(instr, "xor") || !s_cmp(instr, "ld")))
			is_promoted = TRUE;
		vm_arg_new(&process->current_instruction.args[i],
			acb.arg[i], is_promoted);
		vm_arg_read(&process->current_instruction.args[i], &arena->mem);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a header                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks that the instruction arguments are valid and
// fetches the next instruction if needed.

#include "vm.h"

int	vm_validate_live_instr(t_process *process, t_arena *arena)
{
	t_int32	arg_value;

	vm_instr_get_param_value(&arg_value, arena, process, 0);
	arg_value *= -1;
	if (arg_value > arena->player_count || arg_value < 1)
	{
		vm_increment_process_pc(process,
			(int)vm_instr_size(&process->current_instruction),
			arena->verbosity);
		return (0);
	}
	return (1);
}

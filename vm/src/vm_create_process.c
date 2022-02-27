/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_create_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:12:31 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/27 13:27:56 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Adds a t_process element to the end of the list.
*/

t_process	*vm_create_process(t_arena arena, t_process *process_lst, \
t_int32 player_id)
{
	t_process	*new_process;
	int			i;

	i = 0;
	new_process = minit(sizeof(t_process));
	if (!new_process)
		vm_exit_error("Malloc failed in create_process\n");
	new_process->id = (VM_NEGATIVE_IDS * -1) * player_id;
	while (i < REG_NUMBER)
	{
		vm_reg_set_size(&new_process->registers[i], REG_SIZE);
		i++;
	}
	vm_reg_load(&new_process->registers[0], (t_byte *)&new_process->id);
	new_process->id = new_process->id % 1;
	new_process->pc = (t_size)(player_id - 1) * arena.offset;
	new_process->cycles_before_execution = -1;
	new_process->next = process_lst;
	return (new_process);
}

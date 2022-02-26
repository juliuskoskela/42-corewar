/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_live.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:14:50 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/26 18:01:33 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// opcode:		1 (0x01)
/// mnemonic:	live
/// name:		alive
/// params:		1 : { T_DIR }
/// acb:		no
/// ncycles:	10
/// proto:		live id
/// descript:	Reports player #id as being alive

#include "vm.h"

void	vm_instr_live(t_arena *a, t_process *p)
{
	t_int32	id;

	vm_instr_get_param_value(&id, a, p, 0);
	p->last_live = a->current_cycle;
	a->lives_since_check += 1;
	if (VM_NEGATIVE_IDS)
		id = -id;
	if (id > 0 && id <= a->player_count)
	{
		a->last_player_alive = (t_size)id;
		if (a->verbosity & VM_VERBOSE_LIVES)
		{
			print("Player %d (%s) is said to be alive\n",
				id, a->players[id - 1].prog_name);
		}
	}
}

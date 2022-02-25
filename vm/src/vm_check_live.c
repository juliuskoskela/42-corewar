/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check_live.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:12:38 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:12:39 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_process	*vm_delete_process(t_process **head,
t_process *current, t_process *prev)
{
	if (!prev)
	{
		*head = (*head)->next;
		mdel((void **)&current);
		current = *head;
	}
	else
	{
		prev->next = current->next;
		mdel((void **)current);
		current = prev->next;
	}
	return (current);
}

// A process that performed its live statement cycles_to_die 
// or more cycles back is considered dead.

static void	check_live_processes(t_process **head, t_arena *arena)
{
	t_process	*current;
	t_process	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->last_live < arena->current_cycle - arena->cycle_to_die)
		{
			if ((arena->verbosity & VM_VERBOSE_DEATHS) != 0)
				print("Process %d hasn't lived for %d cycles (CTD %d)\n",
					(int)current->id, arena->current_cycle - current->last_live,
					arena->cycle_to_die);
			current = vm_delete_process(head, current, prev);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

/*
**	A check occurs every cycle_to_die cycles, while cycle_to_die is greater
** than zero. If cycle_to_die >= 0, a check occurs after each cycle.

**	if a process performed live cycle_to_die cycles or more ago, it will
**	be killed and removed from the list.

**	cycle_to_die is decreased by CYCLE_DELTA if the number of lives performed
**	in the last period was greater than or equal to
**	NBR_LIVE.

**	If the value of cycle_to_die does not change after MAX_CHECKS checks,
**	it will be decreased by CYCLE_DELTA.

**	After each check, the number of lives stated will be reset to 0.
*/

void	vm_check_live(t_process **head, t_arena *arena)
{
	check_live_processes(head, arena);
	arena->checks_performed += 1;
	if (arena->lives_since_check >= NBR_LIVE || \
		arena->checks_performed >= MAX_CHECKS)
	{
		if (arena->cycle_to_die <= CYCLE_DELTA)
			arena->cycle_to_die = 0;
		else
			arena->cycle_to_die -= CYCLE_DELTA;
		arena->checks_performed = 0;
	}
	arena->lives_since_check = 0;
	arena->cycles_since_check = 0;
}

#include "vm.h"

t_process	*vm_delete_process(t_process **head, t_process *current, \
t_process *prev)
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

/*
**	A check occurs every cycle_to_die cycles, while cycle_to_die is greater
** than zero. If cycle_to_die >= 0, a check occurs after each cycle.

**	if a carriage performed live cycle_to_die cycles or more ago, it will
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
	t_process	*current;
	t_process	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->last_live <= \
			arena->current_cycle - arena->cycle_to_die)
		{
			if ((arena->verbosity & VM_VERBOSE_DEATHS) != 0)
				print("Killing process %d\n", (int)current->id);
			current = vm_delete_process(head, current, prev);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	arena->checks_performed += 1;
	if (arena->lives_since_check >= NBR_LIVE || \
		arena->checks_performed >= MAX_CHECKS)
	{
		arena->cycle_to_die -= CYCLE_DELTA;
		arena->checks_performed = 0;
	}
	arena->lives_since_check = 0;
}

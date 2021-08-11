#include "vm.h"

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

void	vm_check_live(t_process *processes, t_battle *battle)
{
	t_int32		processes_alive;
	t_process	*tmp;

	processes_alive = 0;
	while (processes)
	{
		if (processes->last_live <= \
			battle->cycles_executed - battle->cycle_to_die)
		{
			tmp = processes->next;
			*processes = *processes->next;
			mdel((void **)&tmp);
		}
		else
			processes = processes->next;
	}
	battle->checks_performed += 1;
	if (battle->lives_since_check >= NBR_LIVE || \
		battle->checks_performed >= MAX_CHECKS)
	{
		battle->cycle_to_die -= CYCLE_DELTA;
		battle->checks_performed = 0;
	}
	battle->lives_since_check = 0;
}

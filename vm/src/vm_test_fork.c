#include "vm.h"

void vm_test_fork(t_process *p_lst)
{
	int			count;
	t_process	*tmp;

	count = 0;
	tmp = p_lst;
	print("Youngest process pc: %d ", p_lst->pc);
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	print("Total processes: %d\n", count);
	tmp = p_lst;
	while(tmp)
	{
		print("%d ", tmp->id);
		tmp = tmp->next;
	}
	print("\n");
}

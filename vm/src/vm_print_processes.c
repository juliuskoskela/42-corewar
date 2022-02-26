/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:15 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:16 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_print_processes(t_arena *a, int print_all, int id)
{
	t_bool		found_live_processes;
	t_process	*p;

	found_live_processes = 0;
	p = a->processes;
	print("printing processes:\n");
	while (p)
	{
		if (print_all || p->id == id)
		{
			vm_print_process(p);
			print("\n");
			found_live_processes = 1;
		}
		p = p->next;
	}
	if (!found_live_processes)
		print("no live processes\n");
}

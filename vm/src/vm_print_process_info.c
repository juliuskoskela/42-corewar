/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_process_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:24 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:24 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_print_process_info(t_arena *a, t_process *p)
{
	print("[%#06llu][%#06llu][%#06llu] ", a->current_cycle, p->id, p->pc);
}

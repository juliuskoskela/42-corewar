/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_pause_and_print_memory.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:44 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:45 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_pause_and_print_memory(t_arena arena)
{
	char	c;

	vm_print_arena(arena, arena.processes);
	read(1, &c, 1);
}

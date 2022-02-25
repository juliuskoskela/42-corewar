/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_introduce_champs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:56 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:57 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_introduce_champs(t_arena arena)
{
	t_int32	i;

	print("Introducing contestants...\n");
	i = 0;
	while (i < arena.player_count)
	{
		print("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", \
		i + 1, arena.players[i].prog_size, \
		arena.players[i].prog_name, arena.players[i].comment);
		i++;
	}
}

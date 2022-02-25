/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:13:52 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:13:52 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_mem_print(t_mem *src)
{
	t_size	i;

	i = 0;
	while (i < src->len)
	{
		if (i == ROW_SIZE)
			print("\n");
		print("%#02x ", src->mem[i]);
		i++;
	}
	print("\n");
}

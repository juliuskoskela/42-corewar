/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:13:56 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:13:57 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t dst_len)
{
	t_size	i;

	if (!dst || !src)
		return (FALSE);
	i = 0;
	while (i < dst_len)
	{
		dst[i] = src->mem[src->pos];
		vm_mem_increment_pos(src, 1);
		i++;
	}
	return (TRUE);
}

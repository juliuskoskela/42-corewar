/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_reg_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:13:09 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:13:10 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_reg_load(t_reg *dst, t_byte *src)
{
	t_size	i;

	if (!dst || !src)
		return ;
	i = 0;
	if (ENDIAN_BIG)
	{
		while (i < dst->len)
		{
			dst->mem[dst->len - 1 - i] = src[i];
			i++;
		}
	}
	else
	{
		while (i < dst->len)
		{
			dst->mem[i] = src[i];
			i++;
		}
	}
}

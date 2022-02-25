/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_reg_store.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:13:22 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:13:23 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reg.h"
#include "vm.h"

void	vm_reg_store(t_byte *dst, t_reg *src)
{
	t_size	i;

	if (!dst || !src)
		return ;
	i = 0;
	if (ENDIAN_LITTLE)
	{
		while (i < src->len)
		{
			dst[i] = src->mem[src->len - 1 - i];
			i++;
		}
	}
	else
	{
		while (i < src->len)
		{
			dst[i] = src->mem[i];
			i++;
		}
	}
}

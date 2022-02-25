/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_reg_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:13:14 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:13:14 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_dereferenced_value(t_int32 value, t_size len)
{
	t_size	i;

	if (len == 1)
		print("%hhd", value);
	else if (len == 2)
		print("%hd", value);
	else if (len == 4)
		print("%d", value);
	i = 0;
	print(" [");
	while (i < len)
	{
		print("%02x", ((t_byte *)&value)[i]);
		if (i < len - 1)
			print(" ");
		i++;
	}
	print("]");
}

void	vm_reg_print(t_reg *src)
{
	t_int32	deref;
	t_size	i;

	if (!src || !src->len)
	{
		print("[NULL]");
		return ;
	}
	print("[");
	i = 0;
	while (i < src->len - 1)
	{
		print("0x%02x ", src->mem[i]);
		i++;
	}
	print("0x%02x", src->mem[i]);
	print("] => ");
	deref = 0;
	vm_reg_store((t_byte *)&deref, src);
	print_dereferenced_value(deref, src->len);
}

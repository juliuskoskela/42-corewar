/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:12:46 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:12:46 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_arg	*vm_arg_read(t_arg *dst, t_mem *src)
{
	vm_mem_read((t_byte *)&dst->data.mem, src, dst->data.len);
	return (dst);
}

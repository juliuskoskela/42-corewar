/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:13:43 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:13:43 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_mem	*vm_mem_new(t_mem *src, t_size len)
{
	src->mem = minit(sizeof(t_byte) * len);
	if (!src->mem)
		return (NULL);
	src->pos = 0;
	src->len = len;
	return (src);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_reg_set_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:13:17 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:13:18 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_reg	*vm_reg_set_size(t_reg *src, t_size len)
{
	mzero(&src->mem, REG_SIZE);
	src->len = len;
	return (src);
}

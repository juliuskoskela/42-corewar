/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_reg_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 10:54:14 by ksuomala          #+#    #+#             */
/*   Updated: 2022/02/26 13:34:41 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_int32	vm_reg_value(t_reg src)
{
	t_int32	value;

	if (BIG_ENDIAN)
		vm_reverse_bytes((void *)&value, (void *)&src.mem, src.len);
	else
		value = (t_int32) * src.mem;
	return (value);
}

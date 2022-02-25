/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a header                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	asm_print_output_info(const char *str,
const char *param_type, int32_t value)
{
	if (param_type != NULL)
		print("%s %s %d : %#x\n", str, param_type, value, value);
	else
		print("%s %d : %#x\n", str, value, value);
}

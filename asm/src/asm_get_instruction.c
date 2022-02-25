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

#include "asm.h"
#include "core.h"

int	asm_get_instruction(t_op *dst, char *mnemonic)
{
	size_t	i;

	i = 0;
	while (i < OP_COUNT)
	{
		if (s_cmp(mnemonic, g_op_tab[i].mnemonic) == 0)
		{
			*dst = g_op_tab[i];
			return (1);
		}
		i++;
	}
	return (0);
}

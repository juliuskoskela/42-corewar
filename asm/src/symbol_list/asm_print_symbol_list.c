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
#include "ast.h"
#include "core.h"

void	asm_print_symbol_list(t_symbol_list *symbols, const char *title)
{
	print("%s\n", title);
	while (symbols != NULL)
	{
		if (symbols->node != NULL && symbols->symbol != NULL)
		{
			print("label '%s', value %#x\n",
				symbols->symbol,
				symbols->node->num_value);
		}
		symbols = symbols->next;
	}
	print("\n");
}

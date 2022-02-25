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
#include <stdlib.h>

t_symbol_list	*asm_symbol_list_lookup(t_symbol_list *list, char *symbol)
{
	while (list != NULL)
	{
		if (list->symbol != NULL && s_cmp(list->symbol, symbol) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

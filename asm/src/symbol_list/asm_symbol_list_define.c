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
#include <stdlib.h>

int	asm_symbol_list_define(t_symbol_list *list, t_astnode *node)
{
	if (list->node == NULL)
	{
		list->node = node;
		list->symbol = node->value;
		return (1);
	}
	while (list->next != NULL)
		list = list->next;
	list->next = asm_symbol_list_new(node, node->value);
	return (1);
}

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

t_symbol_list	*asm_symbol_list_new(t_astnode *node, char *symbol)
{
	t_symbol_list	*list;

	list = (t_symbol_list *)malloc(sizeof(t_symbol_list));
	if (list == NULL)
		asm_exit_error("Malloc error in allocating symbol list");
	list->node = node;
	list->forward_refs = NULL;
	list->symbol = symbol;
	list->next = NULL;
	return (list);
}

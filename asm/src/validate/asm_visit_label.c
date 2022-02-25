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
#include "validate.h"

void	asm_visit_label(t_astnode *node, t_symbol_list *symbols)
{
	size_t	i;

	i = 0;
	while (node->value[i] != '\0')
	{
		if (s_chr(LABEL_CHARS, node->value[i]) == NULL)
			asm_semantic_error(node, "Invalid character in label");
		i++;
	}
	if (asm_symbol_list_lookup(symbols, node->value) != NULL)
		asm_semantic_error(node, "Duplicate definition for label");
	asm_symbol_list_define(symbols, node);
}

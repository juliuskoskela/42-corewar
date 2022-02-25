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

void	asm_visit_statement(t_astnode *node, t_symbol_list *symbols,
t_header *header)
{
	if (node->left_child != NULL)
		asm_visit_label(node->left_child, symbols);
	if (node->right_child != NULL && node->right_child->type == DIRECTIVE)
		asm_visit_directive(node->right_child, header);
	else if (node->right_child != NULL
		&& node->right_child->type == INSTRUCTION)
		asm_visit_instruction(node->right_child);
}

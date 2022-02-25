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

void	asm_visit_program(t_astnode *node, t_symbol_list *symbols,
t_header *header)
{
	if (node->right_child != NULL)
		asm_visit_statement_list(node->right_child, symbols, header);
	if (header->prog_name[0] == '\0')
		asm_semantic_error(node, "Missing .name directive");
	else if (header->comment[0] == '\0')
		asm_semantic_error(node, "Missing .comment directive");
}

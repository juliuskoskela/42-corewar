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
#include "generate.h"
#include <stdlib.h>
#include "core.h"

void	asm_generate_bytecode_program(t_output_data *data, t_astnode *tree)
{
	t_location_counters		lc;
	t_symbol_list			*defined_labels;
	t_astnode				*statement_list;

	lc.current = 0;
	defined_labels = NULL;
	statement_list = tree->right_child;
	while (statement_list != NULL)
	{
		asm_generate_statement(data, &lc,
			&defined_labels, statement_list->left_child);
		statement_list = statement_list->right_child;
	}
	if (defined_labels != NULL)
		asm_resolve_label_address(data, lc.current, &defined_labels);
	data->header.prog_size = lc.current;
	if (data->verbose)
		asm_print_symbol_list(&data->symbols,
			"\n\nSymbol table after second pass through AST:");
}

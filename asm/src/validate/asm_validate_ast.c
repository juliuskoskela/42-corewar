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

void	asm_validate_ast(t_output_data *data, t_astnode *tree)
{
	asm_visit_program(tree, &data->symbols, &data->header);
	if (data->verbose)
		asm_print_symbol_list(&data->symbols,
			"Symbol table after first pass through AST:");
}

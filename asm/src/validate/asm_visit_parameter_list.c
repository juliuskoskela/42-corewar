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

int	asm_visit_parameter_list(t_astnode *node, uint32_t param_nbr,
t_op instruction)
{
	int	param_count;

	if (param_nbr > instruction.param_count)
		asm_semantic_error(node, "Too many arguments for instruction");
	asm_visit_parameter(node->left_child, param_nbr, instruction);
	param_count = 1;
	if (node->right_child != NULL)
	{
		param_count += asm_visit_parameter_list(node->right_child,
				param_nbr + 1, instruction);
	}
	return (param_count);
}

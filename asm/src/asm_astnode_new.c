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

#include "ast.h"
#include "asm.h"
#include <stdlib.h>

t_astnode	*asm_astnode_new(t_astnode_type type, char *value, t_token token)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(t_astnode));
	if (node == NULL)
		asm_exit_error("Malloc error in allocating AST node");
	node->type = type;
	node->value = value;
	node->num_value = 0;
	node->token = token;
	node->left_child = NULL;
	node->right_child = NULL;
	return (node);
}

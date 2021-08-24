#include "ast.h"
#include "asm.h"
#include "core.h"
#include "validate.h"

void	asm_visit_directive(t_astnode *node, t_header *header)
{
	size_t				len;
	char				*dst;
	static const char	*cmd_string[2] = {
		NAME_CMD_STRING,
		COMMENT_CMD_STRING
	};

	dst = NULL;
	if (s_cmp(node->left_child->value, &cmd_string[0][1]) == 0)
		dst = header->prog_name;
	else if (s_cmp(node->left_child->value, &cmd_string[1][1]) == 0)
		dst = header->comment;
	else
		asm_semantic_error(node->left_child, "Unrecognized directive");
	if (dst[0] != '\0')
		asm_semantic_error(node->left_child, "Duplicate directive");
	if (node->right_child == NULL)
		asm_semantic_error(node, "Missing string for directive");
	len = s_len(node->right_child->value);
	if ((s_cmp(node->left_child->value, &cmd_string[0][1]) == 0
		&& len > PROG_NAME_LENGTH)
		|| (s_cmp(node->left_child->value, &cmd_string[1][1]) == 0
			&& len > COMMENT_LENGTH))
		asm_semantic_error(node, "String too long for directive");
	s_ncpy(dst, node->right_child->value, len);
}

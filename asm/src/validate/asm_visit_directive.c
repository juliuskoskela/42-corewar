#include "ast.h"
#include "asm.h"
#include "core.h"
#include "validate.h"

int	asm_visit_directive(t_astnode *node, t_header *header)
{
	size_t				len;
	char				*dst;
	static const char	*cmd_string[2] = {
		NAME_CMD_STRING,
		COMMENT_CMD_STRING
	};

	if (s_cmp(node->left_child->value, &cmd_string[0][1]) == 0)
		dst = header->prog_name;
	else if (s_cmp(node->left_child->value, &cmd_string[1][1]) == 0)
		dst = header->comment;
	else
		return (asm_semantic_error(node, "Unrecognized directive"));
	if (dst[0] != '\0')
		return (asm_semantic_error(node, "Duplicate directive"));
	if (node->right_child == NULL)
		return (asm_semantic_error(node, "Missing string for directive"));
	len = s_len(node->right_child->value);
	if ((s_cmp(node->left_child->value, &cmd_string[0][1]) == 0
		&& len > PROG_NAME_LENGTH)
		|| (s_cmp(node->left_child->value, &cmd_string[1][1]) == 0
			&& len > COMMENT_LENGTH))
		return (asm_semantic_error(node, "String too long for directive"));
	s_ncpy(dst, node->right_child->value, len);
	return (1);
}

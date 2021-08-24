#ifndef VALIDATE_H
# define VALIDATE_H

void	asm_semantic_error(t_astnode *node, char *msg);
void	asm_visit_parameter(t_astnode *node,
			uint32_t param_nbr, t_op instruction);
int		asm_visit_parameter_list(t_astnode *node, uint32_t param_nbr,
			t_op instruction);
void	asm_visit_instruction(t_astnode *node);
void	asm_visit_directive(t_astnode *node, t_header *header);
void	asm_visit_label(t_astnode *node, t_symbol_list *symbols);
void	asm_visit_statement(t_astnode *node, t_symbol_list *symbols,
			t_header *header);
void	asm_visit_statement_list(t_astnode *node, t_symbol_list *symbols,
			t_header *header);
void	asm_visit_program(t_astnode *node, t_symbol_list *symbols,
			t_header *header);

#endif

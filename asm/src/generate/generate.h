#ifndef GENERATE_H
# define GENERATE_H

void	asm_write_bytes(t_output_data *data, uint32_t *lc, void *bytes, int n);
void	asm_generate_error(t_astnode *node, char *msg);
void	asm_print_output_info(const char *str,
			const char *param_type, int32_t value);

int		asm_generate_statement(t_output_data *data, uint32_t *lc,
			t_symbol_list **labels, t_astnode *node);
int		asm_generate_instruction(t_output_data *data, uint32_t *lc,
			t_symbol_list **labels, t_astnode *node);
void	asm_write_arguments(t_output_data *data, uint32_t *lc,
			uint32_t current_op_lc, t_astnode *parameter_list);
int		asm_get_numeric_value(int32_t *dst, char *str);

#endif

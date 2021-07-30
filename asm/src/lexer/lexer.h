#ifndef LEXER_H
# define LEXER_H

# include "asm.h"

void			asm_init_lexer(t_lexer *lexer, const char *input);
t_token			asm_get_next_token(t_lexer *lexer);
t_token_type	asm_peek_next_token(t_lexer *lexer);

char			asm_lexer_peek(t_lexer *lexer);
void			asm_lexer_advance(t_lexer *lexer);
void			asm_print_lexer_error(t_lexer *lexer, const char *msg);
t_token			asm_get_character_token(t_lexer *lexer);
t_token			asm_get_eof_token(t_lexer *lexer);
t_token			asm_get_string_token(t_lexer *lexer);
t_token			asm_get_int_token(t_lexer *lexer);
t_token			asm_get_id_token(t_lexer *lexer);
t_token			asm_get_error_token(t_lexer *lexer);

void			asm_print_lexer_error(t_lexer *lexer, const char *msg);

#endif

###############################################################################
#
#	Makefile
#
###############################################################################

NAME		=	asm

SRC_DIR		=	src/
SRC_SUBDIRS	=	lexer parser symbol_list validate generate
INC_DIR		=	inc/
OBJ_DIR		=	obj/
DEP_DIR		=	.deps/

LIB_CORE_DIR	=	../lib/core/
LIB_CORE	=	$(LIB_CORE_DIR)libcore.a

LIB_ARGPARSER_DIR	=	../lib/argparser/
LIB_ARGPARSER	=	$(LIB_ARGPARSER_DIR)libargparser.a

CC			=	gcc
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC -fsanitize=address
DFLAGS		=	-Wunreachable-code -Wpedantic -Wtype-limits #-Wconversion
CPPFLAGS	=	-I $(INC_DIR) -I ../inc/ -I $(LIB_CORE_DIR)inc -I $(LIB_ARGPARSER_DIR)include
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
LDFLAGS		=	-L $(LIB_CORE_DIR) -L $(LIB_ARGPARSER_DIR)
LDLIBS		=	-l core -l argparser
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(DFLAGS) $(CPPFLAGS) -c

SRC_LEXER	=	$(addprefix lexer/,\
				asm_get_character_token.c \
				asm_get_eof_token.c \
				asm_get_error_token.c \
				asm_get_id_token.c \
				asm_get_int_token.c \
				asm_get_next_token.c \
				asm_get_string_token.c \
				asm_init_lexer.c \
				asm_lexer_advance.c \
				asm_lexer_peek.c \
				asm_peek_next_token.c \
				asm_lexer_error.c \
			)

SRC_PARSER	=	$(addprefix parser/,\
				asm_ast_direct.c \
				asm_ast_directive.c \
				asm_ast_indirect.c \
				asm_ast_instruction.c \
				asm_ast_label.c \
				asm_ast_parameter_list.c \
				asm_ast_program.c \
				asm_ast_register.c \
				asm_ast_statement_list.c \
				asm_ast_statement.c \
				asm_consume_token.c \
				asm_init_empty_token.c \
				asm_init_parser.c \
				asm_parse.c \
				asm_parser_error.c \
			)

SRC_SYMBOL_LIST	=	$(addprefix symbol_list/,\
					asm_print_symbol_list.c \
					asm_symbol_list_define.c \
					asm_symbol_list_delete.c \
					asm_symbol_list_free.c \
					asm_symbol_list_lookup.c \
					asm_symbol_list_new.c \
				)

SRC_VALIDATE	=	$(addprefix validate/,\
					asm_validate_ast.c \
					asm_semantic_error.c \
					asm_visit_directive.c \
					asm_visit_instruction.c \
					asm_visit_label.c \
					asm_visit_parameter_list.c \
					asm_visit_parameter.c \
					asm_visit_program.c \
					asm_visit_statement_list.c \
					asm_visit_statement.c \
				)

SRC_GENERATE	=	$(addprefix generate/,\
					asm_generate_error.c \
					asm_generate_instruction.c \
					asm_generate_bytecode_program.c \
					asm_generate_statement.c \
					asm_get_param_sizes.c \
					asm_get_numeric_value.c \
					asm_get_label_value.c \
					asm_print_output_info.c \
					asm_write_argument_coding_byte.c \
					asm_write_arguments.c \
					asm_write_bytes.c \
					asm_resolve_label_address.c \
				)

SRC_OTHER	=	asm_main.c \
				asm_read_input.c \
				asm_parse_arguments.c \
				asm_init_token.c \
				asm_init_output_data.c \
				asm_write_output_to_file.c \
				asm_print_output_hexdump.c \
				asm_write_ast_dot_to_file.c \
				asm_print_ast_dot.c \
				asm_get_instruction.c \
				asm_exit_error.c \
				asm_astnode_new.c \
				asm_astnode_free.c

ALL_SRC		=	$(SRC_LEXER) \
				$(SRC_PARSER) \
				$(SRC_SYMBOL_LIST) \
				$(SRC_VALIDATE) \
				$(SRC_GENERATE) \
				$(SRC_OTHER)

# SRC_BASE	=	asm_main.c \
# 				asm_read_input.c \
# 				asm_init_lexer.c \
# 				asm_lexer_advance.c \
# 				asm_lexer_peek.c \
# 				asm_init_token.c \
# 				asm_init_empty_token.c \
# 				asm_get_next_token.c \
# 				asm_peek_next_token.c \
# 				asm_init_parser.c \
# 				asm_parse.c \
# 				asm_validate.c \
# 				asm_init_output_data.c \
# 				asm_generate_output.c \
# 				asm_write_output_to_file.c \
# 				asm_print_output_hexdump.c \
# 				asm_symbol_list_new.c \
# 				asm_symbol_list_lookup.c \
# 				asm_symbol_list_define.c \
# 				asm_symbol_list_delete.c \
# 				asm_symbol_list_free.c \
# 				asm_print_symbol_list.c \
# 				asm_write_ast_dot_to_file.c \
# 				asm_print_ast_dot.c \
# 				asm_get_instruction.c \
# 				asm_get_numeric_value.c \
# 				asm_exit_error.c \
# 				asm_astnode_new.c \
# 				asm_astnode_free.c

SRC			=	$(addprefix $(SRC_DIR), $(ALL_SRC))
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

.PHONY: all fclean clean re

all: $(NAME)

$(NAME): $(OBJ) $(LIB_CORE) $(LIB_ARGPARSER)
				$(CC) $(CFLAGS) $(DFLAGS) -o $@ $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
				@echo "\\n\033[32;1mASSEMBLER COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | obj
				@$(CC) $(CFLAGS) $(DFLAGS) $(CPPFLAGS) -c $< -o $@
				@echo $@

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(DEP_DIR) $(OBJ_DIR)
# 				$(COMPILE.c) $< -o $@
# 				@echo $@

obj:
				mkdir -p $(addprefix $(OBJ_DIR), $(SRC_SUBDIRS))

# $(DEP_DIR):
# 				mkdir -p $(addprefix obj/, $(SRC_SUBDIRS))

$(LIB_CORE):
				@$(MAKE) -C $(LIB_CORE_DIR)

$(LIB_ARGPARSER):
				@$(MAKE) -C $(LIB_ARGPARSER_DIR)

# DEPFILES = $(addprefix $(DEP_DIR), $(SRC_BASE:.c=.d))
# $(DEPFILES):

clean:
				@rm -rf $(OBJ_DIR) $(DEP_DIR)
				@make clean -C $(LIB_CORE_DIR)
				@make clean -C $(LIB_ARGPARSER_DIR)

fclean: clean
				@rm -rf $(NAME) $(NAME).dSYM
				@make fclean -C $(LIB_CORE_DIR)
				@make fclean -C $(LIB_ARGPARSER_DIR)

re: fclean all

#include $(wildcard $(DEPFILES))

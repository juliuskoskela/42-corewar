###############################################################################
#
#	Makefile
#
###############################################################################

NAME		=	asm

SRC_DIR		=	src/
INC_DIR		=	inc/
OBJ_DIR		=	obj/
DEP_DIR		=	.deps/

CC			=	gcc
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC #-fsanitize=address
DFLAGS		=	-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
CPPFLAGS	=	-I $(INC_DIR) -I ../inc
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
LDLIBS		=	#../lib/core/libcore.a
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

SRC_BASE	=	asm_main.c \
				asm_read_input.c \
				asm_init_lexer.c \
				asm_lexer_advance.c \
				asm_lexer_peek.c \
				asm_init_token.c \
				asm_get_next_token.c \
				asm_peek_next_token.c \
				asm_init_parser.c \
				asm_parse.c \
				asm_validate.c \
				asm_generate_output.c \
				asm_write_output_to_file.c \
				asm_symbol_list_new.c \
				asm_symbol_list_lookup.c \
				asm_symbol_list_define.c \
				asm_symbol_list_delete.c \
				asm_print_symbol_list.c \
				asm_write_dot_to_file.c \
				asm_print_ast_dot.c \
				asm_exit_error.c \
				asm_astnode_new.c 

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
				@$(CC) $(CFLAGS) -o $@ $(OBJ) $(CPPFLAGS) $(LDLIBS)
				@echo "\\n\033[32;1mASSEMBLER COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(OBJ_DIR) $(DEP_DIR)
				@$(COMPILE.c) $< -o $@
				@echo $@

$(OBJ_DIR):
				@mkdir -p $@

$(DEP_DIR):
				@mkdir -p $@

DEPFILES = $(addprefix $(DEP_DIR), $(SRC_BASE:.c=.d))
$(DEPFILES):

clean:
				@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
				@rm -rf $(NAME);

re: fclean all

.PHONY: all fclean clean re

include $(wildcard $(DEPFILES))

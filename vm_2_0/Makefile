###############################################################################
#
#	Makefile
#
###############################################################################

NAME		=	corewar

SRC_DIR		=	src/
INC_DIR		=	inc/
OBJ_DIR		=	obj/
DEP_DIR		=	.deps/

LIB_CORE		= ../lib/core/libcore.a
LIB_ARGPARSER	= ../lib/argparser/libargparser.a
LIB_CORE_DIR		= ../lib/core/
LIB_ARGPARSER_DIR	= ../lib/argparser/

CC			=	clang
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC -fsanitize=address
DFLAGS		=	-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
CPPFLAGS	=	-I $(INC_DIR) -I ../inc -I ../lib/core/inc -I ../lib/argparser/include
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
LDFLAGS		=	-L $(LIB_CORE_DIR) -L $(LIB_ARGPARSER_DIR)
LDLIBS		=	-l argparser -l core
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

SRC_BASE	=	vm_main.c \
				vm_parse_arguments.c \
				vm_save_input.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

.PHONY: all fclean clean re

all: $(NAME)

$(NAME): $(OBJ) $(LIB_CORE) $(LIB_ARGPARSER)
				@$(CC) $(CFLAGS) -o $@ $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
				@echo "\\n\033[32;1mCOREWAR VIRTUAL MACHINE COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(OBJ_DIR) $(DEP_DIR)
				@$(COMPILE.c) $< -o $@
				@echo $@

$(OBJ_DIR):
				@mkdir -p $@

$(DEP_DIR):
				@mkdir -p $@

$(LIB_CORE):
	$(MAKE) -C ../lib/core/

$(LIB_ARGPARSER):
	$(MAKE) -C ../lib/argparser/

DEPFILES = $(addprefix $(DEP_DIR), $(SRC_BASE:.c=.d))
$(DEPFILES):

clean:
				@rm -rf $(OBJ_DIR) $(DEP_DIR)
				@make clean -C ../lib/core
				@make clean -C ../lib/argparser

fclean: clean
				@rm -rf $(NAME);
				@make fclean -C ../lib/core
				@make fclean -C ../lib/argparser

re: fclean all


include $(wildcard $(DEPFILES))
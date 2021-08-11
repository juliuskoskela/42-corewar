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

CC			=	gcc
CFLAGS 		=	-O3 -Wall -Wextra -Werror -fPIC
DFLAGS		=	-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
CPPFLAGS	=	-I $(INC_DIR)
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
LDLIBS		=	../lib/core/libcore.a
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

SRC_BASE	=	vm_main.c \
				vm_error.c \
				vm_reverse_bytes.c \
				vm_save_input.c \
				vm_test_print.c \
				vm_create_player.c \
				vm_battle.c \
				vm_execute_cycle.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

all:
				@$(MAKE) -j $(NAME)

$(NAME): $(OBJ)
				@$(CC) $(CFLAGS) -o $@ $(OBJ) $(CPPFLAGS) $(LDLIBS)
				@echo "\\n\033[32;1mCOREWAR VIRTUAL MACHINE COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(OBJ_DIR) $(DEP_DIR) $(LDLIBS)
				@$(COMPILE.c) $< -o $@
				@echo $@

$(OBJ_DIR):
				@mkdir -p $@

$(DEP_DIR):
				@mkdir -p $@

DEPFILES = $(addprefix $(DEP_DIR), $(SRC_BASE:.c=.d))
$(DEPFILES):

$(LDLIBS):
	make -C ../lib/core/

clean:
				@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
				@rm -rf $(NAME);

re: fclean all

.PHONY: all fclean clean re

include $(wildcard $(DEPFILES))
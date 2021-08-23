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
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC -fsanitize=address
DFLAGS		=	-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
CPPFLAGS	=	-I $(INC_DIR) -I ../lib/core/inc
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
LDLIBS		=	../lib/core/libcore.a
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

SRC_BASE	=	vm_main.c \
				vm_error.c \
				vm_reverse_bytes.c \
				vm_save_input.c \
				vm_test_print.c \
				vm_create_player.c \
				vm_create_process.c \
				vm_battle.c \
				vm_execute_cycle.c \
				vm_check_live.c \
				vm_introduce_champs.c \
				vm_print_arena.c \
				vm_get_mem_addr.c \
				vm_get_reg_addr.c \
				vm_get_val.c \
				vm_instr_null.c \
				vm_instr_live.c \
				vm_instr_st.c \
				vm_instr_sti.c \
				vm_check_acb.c \
				vm_instr_ld.c \
				vm_instr_ldi.c \
				vm_instr_fork.c \
				vm_instr_lld.c \
				vm_instr_zjmp.c \
				vm_instr_lldi.c \
				vm_instr_lfork.c \
				vm_instr_aff.c \

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

all:
				@$(MAKE) -j $(NAME)

$(NAME): $(OBJ) $(LDLIBS)
				@$(CC) $(CFLAGS) -o $@ $(OBJ) $(CPPFLAGS) $(LDLIBS)
				@echo "\\n\033[32;1mCOREWAR VIRTUAL MACHINE COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(OBJ_DIR) $(DEP_DIR)
				@$(COMPILE.c) $< -o $@
				@echo $@

$(OBJ_DIR):
				@mkdir -p $@

$(DEP_DIR):
				@mkdir -p $@

$(LDLIBS):
	make -C ../lib/core/

DEPFILES = $(addprefix $(DEP_DIR), $(SRC_BASE:.c=.d))
$(DEPFILES):

clean:
				@rm -rf $(OBJ_DIR) $(DEP_DIR)
				@make clean -C ../lib/core

fclean: clean
				@rm -rf $(NAME);
				@make fclean -C ../lib/core

re: fclean all

.PHONY: all fclean clean re

include $(wildcard $(DEPFILES))
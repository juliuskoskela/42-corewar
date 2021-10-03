###############################################################################
#
#	Makefile
#
###############################################################################

NAME		=	corewar

SRC_DIR		=	src/
SRC_SUBDIRS	=	instr mem reg
INC_DIR		=	inc/
OBJ_DIR		=	obj/
DEP_DIR		=	.deps/

LIB_CORE		= ../lib/core/libcore.a
LIB_ARGPARSER	= ../lib/argparser/libargparser.a
LIB_CORE_DIR		= ../lib/core/
LIB_ARGPARSER_DIR	= ../lib/argparser/

CC			=	gcc
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC -fsanitize=address
DFLAGS		=	-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
CPPFLAGS	=	-I $(INC_DIR) -I ../inc -I ../lib/core/inc -I ../lib/argparser/include
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
LDFLAGS		=	-L $(LIB_CORE_DIR) -L $(LIB_ARGPARSER_DIR)
LDLIBS		=	-l argparser -l core
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

SRC_BASE	=	vm_main.c \
				vm_error.c \
				vm_reverse_bytes.c \
				vm_save_input.c \
				vm_parse_arguments.c \
				vm_test_print.c \
				vm_create_player.c \
				vm_create_process.c \
				vm_battle.c \
				vm_execute_cycle.c \
				vm_check_live.c \
<<<<<<< HEAD:vm_2_0/Makefile
				vm_exit_error.c \
				vm_reverse_bytes.c \
				vm_arg_new.c \
				vm_arg_read.c \
				vm_print_arena.c \
#				vm_test_print.c \
=======
				vm_introduce_champs.c \
>>>>>>> 7e19e624ac9d87f214fac750e03333c7d245cf98:vm_old/Makefile
				vm_print_arena.c \
				vm_get_mem_addr.c \
				vm_get_reg_addr.c \
				vm_get_arg_data.c \
				vm_get_arg_type.c \
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
				vm_instr_add.c \
				vm_instr_sub.c \
				vm_instr_and.c \
				vm_instr_or.c \
				vm_instr_xor.c \
				vm_advance_pc.c \
				vm_pause_and_print_memory.c \
				vm_print_bytes.c \
<<<<<<< HEAD:vm_2_0/Makefile
				vm_print_process.c

SRC_INSTR =		$(addprefix instr/,\
				vm_instr_null.c \
				vm_instr_size.c \
)

SRC_MEM =		$(addprefix mem/,\
				vm_mem_new.c \
				vm_mem_set.c \
				vm_mem_write.c \
				vm_mem_read.c \
				vm_mem_increment_pos.c \
				vm_mem_free.c \
				vm_mem_print_overlay.c \
				vm_mem_print.c \
)

SRC_REG =		$(addprefix reg/,\
				vm_reg_copy.c \
				vm_reg_deref.c \
				vm_reg_print.c \
				vm_reg_ref.c \
				vm_reg_set.c \
)

ALL_SRC = $(SRC_BASE) $(SRC_INSTR) $(SRC_MEM) $(SRC_REG)
=======
				vm_print_process.c \
>>>>>>> 7e19e624ac9d87f214fac750e03333c7d245cf98:vm_old/Makefile

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

.PHONY: all fclean clean re

all: $(NAME)

$(NAME): $(OBJ) $(LIB_CORE) $(LIB_ARGPARSER)
<<<<<<< HEAD:vm_2_0/Makefile
				$(CC) $(CFLAGS) -o $@ $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
				@echo "\\n\033[32;1mCOREWAR VIRTUAL MACHINE COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
				@$(COMPILE.c) $< -o $@
				@echo $@
$(OBJ_DIR):
				mkdir -p $(addprefix $(OBJ_DIR), $(SRC_SUBDIRS))
=======
				@$(CC) $(CFLAGS) -o $@ $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
				@echo "\\n\033[32;1mCOREWAR VIRTUAL MACHINE COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(OBJ_DIR) $(DEP_DIR)
				@$(COMPILE.c) $< -o $@
				@echo $@

$(OBJ_DIR):
				@mkdir -p $@
>>>>>>> 7e19e624ac9d87f214fac750e03333c7d245cf98:vm_old/Makefile

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
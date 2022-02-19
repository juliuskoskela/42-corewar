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

CC			=	clang
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC -fsanitize=address
DFLAGS		=	-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
CPPFLAGS	=	-I $(INC_DIR) -I src/instr -I ../inc -I ../lib/core/inc -I ../lib/argparser/include
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
LDFLAGS		=	-L $(LIB_CORE_DIR) -L $(LIB_ARGPARSER_DIR)
LDLIBS		=	-l argparser -l core
COMPILE.c	=	$(CC) $(CFLAGS) $(CPPFLAGS) -c

SRC_BASE	=	vm_main.c \
				vm_parse_arguments.c \
				vm_save_input.c \
				vm_battle.c \
				vm_create_player.c \
				vm_create_process.c \
				vm_introduce_champs.c \
				vm_execute_cycle.c \
				vm_pause_and_print_memory.c \
				vm_check_live.c \
				vm_exit_error.c \
				vm_reverse_bytes.c \
				vm_arg_new.c \
				vm_arg_read.c \
				vm_print_arena.c \
				vm_print_processes.c \
				vm_test_fork.c \
				vm_interactive_loop.c \
				vm_print_instr_arg.c \
				vm_print_instr.c \
				vm_print_process_info.c \
				vm_type_name.c \
				vm_instr_size.c \
				vm_read_instr_arguments.c \
				vm_print_process.c

SRC_INSTR =		$(addprefix instr/,\
				vm_instr_null.c \
				vm_instr_fork.c \
				vm_instr_lfork.c \
				vm_instr_st.c \
				vm_instr_sti.c \
				vm_instr_ld.c \
				vm_instr_ldi.c \
				vm_instr_lld.c \
				vm_instr_zjmp.c \
				vm_instr_lldi.c \
				vm_instr_aff.c \
				vm_instr_add.c \
				vm_instr_sub.c \
				vm_instr_and.c \
				vm_instr_or.c \
				vm_instr_xor.c \
				vm_instr_live.c \
				vm_instr_get_param.c \
)

SRC_MEM =		$(addprefix mem/,\
				vm_mem_new.c \
				vm_mem_set_pos.c \
				vm_mem_write.c \
				vm_mem_read.c \
				vm_mem_increment_pos.c \
				vm_mem_free.c \
				vm_mem_print_overlay.c \
				vm_mem_print.c \
)

SRC_REG =		$(addprefix reg/,\
				vm_reg_copy.c \
				vm_reg_store.c \
				vm_reg_print.c \
				vm_reg_load.c \
				vm_reg_set_size.c \
)

ALL_SRC = $(SRC_BASE) $(SRC_INSTR) $(SRC_MEM) $(SRC_REG)

SRC			=	$(addprefix $(SRC_DIR), $(ALL_SRC))
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

.PHONY: all fclean clean re

all: $(NAME)

$(NAME): $(OBJ) $(LIB_CORE) $(LIB_ARGPARSER)
				$(CC) $(CFLAGS) -o $@ $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
				@echo "\\n\033[32;1mCOREWAR VIRTUAL MACHINE COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
				@$(COMPILE.c) $< -o $@
				@echo $@
$(OBJ_DIR):
				mkdir -p $(addprefix $(OBJ_DIR), $(SRC_SUBDIRS))

# $(DEP_DIR):
# 				mkdir -p $@/instr

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
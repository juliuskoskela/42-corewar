NAME		=	libsys.a

SRC_DIR		=	src/
INC_DIR		=	inc/
OBJ_DIR		=	obj/
DEP_DIR		=	.deps/

CC			=	gcc
<<<<<<< HEAD:argparser/Makefile
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC \
				-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
=======
CFLAGS 		=	-O3 -Wall -Wextra -Werror -fPIC
DFLAGS		=	-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
>>>>>>> instr:lib/core/core_system/Makefile
CPPFLAGS	=	-I $(INC_DIR)
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

<<<<<<< HEAD:argparser/Makefile
SRC_BASE	=	argparser_parse.c \
				argparser_usage.c \
				_argparser_help.c \
				_argparser_long_usage.c \
				_argparser_print_usage.c \
				_argparser_get_option.c \
				_argparser_get_arg.c \
				_argparser_get_default_opt.c \
				_argparser_get_long_opt.c \
				_argparser_get_short_opt.c \
				_argparser_parse_default_opt.c
=======
SRC_BASE	=	cr_activate.c \
				cr_static.c \
				cr_deactivate.c \
				cr_debug.c \
				cr_error.c \
				cr_log.c \
				cr_stacktrace.c \
>>>>>>> instr:lib/core/core_system/Makefile

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

all:
				@$(MAKE) -j $(NAME)

$(NAME): $(OBJ)

				@echo "\\n\033[32;1mSYSTEM FUNCTIONS COMPILED\033[0m \\n"

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

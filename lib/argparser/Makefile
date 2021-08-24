NAME		=	libargparser.a

SRC_DIR		=	src/
INC_DIR		=	include/
OBJ_DIR		=	obj/
DEP_DIR		=	.deps/

LIB_CORE_DIR	=	../core/
LIB_CORE	=	$(LIB_CORE_DIR)libcore.a

CC			=	gcc
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC -fsanitize=address\
				-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
CPPFLAGS	=	-I $(INC_DIR) -I $(LIB_CORE_DIR)inc
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

SRC_BASE	=	argparser_parse.c \
				argparser_usage.c \
				_argparser_help.c \
				_argparser_long_usage.c \
				_argparser_print_usage.c \
				_argparser_get_option.c \
				_argparser_get_arg.c \
				_argparser_parse_default_option.c \
				_argparser_parse_argument.c \
				_argparser_parse_option.c \
				_argparser_error.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

.PHONY: all fclean clean re

all: $(NAME)

$(NAME): $(OBJ) $(LIB_CORE)
				ar -rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(OBJ_DIR) $(DEP_DIR)
				@$(COMPILE.c) $< -o $@
				@echo $@

$(OBJ_DIR):
				@mkdir -p $@

$(DEP_DIR):
				@mkdir -p $@

$(LIB_CORE):
				@$(MAKE) -C $(LIB_CORE_DIR)

DEPFILES = $(addprefix $(DEP_DIR), $(SRC_BASE:.c=.d))
$(DEPFILES):

clean:
				@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
				@rm -rf $(NAME)

re: fclean all

include $(wildcard $(DEPFILES))

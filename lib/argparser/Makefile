NAME		=	libargparser.a

SRC_DIR		=	src/
INC_DIR		=	include/
OBJ_DIR		=	obj/
DEP_DIR		=	.deps/

CC			=	gcc
CFLAGS 		=	-g -Wall -Wextra -Werror -fPIC \
				-Wunreachable-code -Wconversion -Wpedantic -Wtype-limits
CPPFLAGS	=	-I $(INC_DIR)
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

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

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

.PHONY: all fclean clean re

all: $(NAME)

$(NAME): $(OBJ)
				@ar -rcs $(NAME) $(OBJ)

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
				@rm -rf $(NAME)

re: fclean all

include $(wildcard $(DEPFILES))

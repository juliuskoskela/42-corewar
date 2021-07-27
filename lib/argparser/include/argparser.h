#ifndef ARGPARSER_H
# define ARGPARSER_H

# include <stdio.h>

# define OPTION_ARG_OPTIONAL		1U
//# define OPTION_HIDDEN				2U
//# define OPTION_ALIAS				4U
//# define OPTION_DOC					8U

# define ARGP_PARSE_ARGV0			1U
# define ARGP_NO_ERRS 				2U
//# define ARGP_NO_ARGS 				4U
//# define ARGP_IN_ORDER				8U
# define ARGP_NO_HELP 				16U
# define ARGP_NO_EXIT 				32U
# define ARGP_LONG_ONLY 			64U
# define ARGP_SILENT 				128U

# define ARGP_ERR_UNKNOWN			(-1)
# define ARGP_KEY_ARG				0
# define ARGP_KEY_END				1

# define ARGP_EXIT_PARSE_ERROR		-1

struct argparser_state
{
	int								argc;
	char							**argv;
	int								next;
	unsigned int					flags;
	unsigned int					arg_num;
	int								quoted;
	void							*input;
	char							*name;
	void							*hook;
	void							*pstate;
};

typedef int (*t_arg_parser)(int key, char *arg, struct argparser_state *state);

struct argparser_option
{
	const char						*name;
	int								key;
	const char						*arg;
	int								flags;
	const char						*doc;
	int								group;
};

struct argparser
{
	const struct argparser_option	*options;
	t_arg_parser					parser;
	const char						*args_doc;
	const char						*doc;
};

int	argparser_parse(const struct argparser *argp, int argc, char **argv,
	unsigned flags, int *arg_index, void *input);

#endif

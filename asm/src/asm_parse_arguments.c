#include "asm.h"
#include "ast.h"
#include <stdlib.h>
#include "core.h"
#include "argparser.h"

int	parse_opt(int key, char *arg, t_argparser_state *state)
{
	t_input_args	*arguments;

	arguments = state->input;
	if (key == 'h')
		arguments->print_hex_dump = 1;
	else if (key == 'd')
		arguments->print_ast_dot = 1;
	else if (key == 'v')
		arguments->verbose = 1;
	else if (key == ARGP_KEY_ARG)
	{
		if (state->arg_num != 0)
			argparser_usage(state);
		arguments->input_path = arg;
	}
	else if (key == ARGP_KEY_END)
	{
		if (state->arg_num == 0)
			argparser_usage(state);
	}
	else
		return (ARGP_ERR_UNKNOWN);
	return (0);
}

t_input_args	asm_parse_arguments(int argc, char **argv)
{
	t_input_args					arguments;
	t_argparser						argparser;
	static const char				doc[] = "asm: description";
	static const char				args_doc[] = "path/to/player.s";
	static const t_argparser_option	options[] = {
		{"hex-dump", 'h', 0, 0, "print the resulting output as a hex dump\
				to standard output"},
		{"dot", 'd', 0, 0, "write the intermediate AST/parse tree to path/to/player.dot\n\
				from which an image can be generated with\n\
				`dot -Tpng -o player_dot.png path/to/player.dot`"},
		{"verbose", 'v', 0, 0, "verbose mode"},
		{0}
	};

	mzero(&arguments, sizeof(arguments));
	mzero(&argparser, sizeof(argparser));
	argparser.doc = doc;
	argparser.args_doc = args_doc;
	argparser.options = options;
	argparser.parser = parse_opt;
	argparser_parse(&argparser, argc, argv, &arguments);
	return (arguments);
}

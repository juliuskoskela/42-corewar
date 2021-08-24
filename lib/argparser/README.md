# Argparser - library that implements ``argp`` style argument parsing

``Argp`` is an interface in the GNU C library for parsing (unix-style argument vectors)[https://www.gnu.org/software/libc/manual/html_node/Argp.html]. Here, a subset of the functionality of ``argp`` is implemented under the name of ``argparser``.

Like ``argp``, ``argparser`` provides a relatively simple interface to parse command line arguments of a program. 

This library provides two function prototypes that can be called:
```c
int		argparser_parse(const t_argparser *argp, int argc, char **argv, void *input);
void	argparser_usage(t_argparser_state *state);
```

The original ``argp_parse`` prototype differs from this in that it passes to additional parameters, ``unsigned int flags, int *arg_index``, but for ``argparser_parse``, these will have to be passed inside the ``argp`` struct. To use it, you need to define a couple of elements.

First, you will need to define a structure where information about the parsed command line options and arguments will be saved, denoted by ``input`` in the function prototype. This pointer will be saved in a special ``state`` structure through which it will be available for your parser function.

Second is a struct ``t_argparser`` that will contain six fields:
```c
typedef struct s_argparser
{
	const t_argparser_option		*options;
	t_parse_func					parser;
	const char						*args_doc;
	const char						*doc;
	unsigned int					flags;
	int								*arg_index;
}	t_argparser;
```

1) A ``t_argparser_option`` array that contains an element for each implemented option:

```c
typedef struct s_argparser_option
{
	const char						*name;
	int								key;
	const char						*arg;
	int								flags;
	const char						*doc;
}	t_argparser_option;
```

- ``name`` defines the long option version of the option that will be prefixed with ``--`` on the command line, such as ``--verbose``
- ``key``, if set to be a printable character, defines the short one-char option that will be prefixed with ``-``
- ``arg`` determines whether the option takes an argument by giving it a name (if not, otherwise set to 0)
- ``flags`` provides additional information about the option. Currently, it can be set to either zero or ``OPTION_ARG_OPTIONAL`` that means that the argument the option takes is optional
- Finally, ``doc`` should contain a short description of the option that will be shown in the builtin ``--help`` message.

2) A parser function that fits the typedef ``typedef int	(*t_parse_func)(int key, char *arg, t_argparser_state *state);``
- The parser function is responsible for defining how each encountered option from the above array should be handled. In essence, the argparser will call ``t_parse_func`` for every successfully parsed option and pass along three arguments:
- ``key``, that will either correspond to the short option defined in ``t_argparser_option`` or be set to ``ARGP_KEY_ARG`` that designates that ``arg`` will contain a command line argument, not an option (one that is not prefixed with ``-``s)
- ``arg``, which will be NULL if the parsed option does not take an argument, and non-NULL if an argument was found for an option or if it is a non-option argument
- ``state``, which is a struct containing information about the current state of parsing, which argparser makes use of internally as well.

The examples directory contains an example program that uses argparser. There, the following parser function is defined:
```c
static int parse_opt(int key, char *arg, t_argparser_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'v':
      arguments->verbose = 1;
      break;
    case 'a':
      arguments->string1 = arg;
      break;
    case 'b':
      arguments->string2 = arg;
      break;
    case 'o':
      arguments->outfile = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
	{
	  argparser_usage(state);
	}
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 2)
	{
	  argparser_usage(state);
	}
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}
```

3) An ``argc_doc`` string that gives the format of non-optional arguments that the program takes. This string will be displayed in the builtin ``--help`` and ``--usage`` messages.

4) A ``doc`` string that contains a short description of the program itself that, if given, is used in the ``--help`` and ``--usage`` messages

5) A flag variable that can be used to optionally specify additional constaints for the parser. Multiple flags can be or'ed. Currently, the ones supported are ``ARGP_PARSE_ARGV0``, ``ARGP_NO_ERRS`` and ``ARGP_NO_EXIT``. 

6) Pointer to an integer, ``arg_index``. If non-null, this will be set to the index of last command line argument that was not parsed, or argc if all were successfully parsed.

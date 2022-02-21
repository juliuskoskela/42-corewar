#include "vm.h"

void	vm_interactive_print_processes(t_arena *arena, int arg)
{
	if (arg == 0 || arg > (int)arena->player_count)
		print("Invalid process id %d\n", arg);
	else
		vm_print_processes(arena, arg);
}

void	vm_interactive_print_arena(t_arena *arena, int arg)
{
	if (!arena || arg != -1)
		return ;
	vm_print_arena(*arena, arena->processes);
}

void	vm_interactive_exit(t_arena *arena, int arg)
{
	if (!arena || !arg)
		;
	exit(0);
}

void	vm_interactive_help(t_arena *arena, int arg)
{
	if (!arena || !arg)
		;
	print("Interactive options:\n\
	p [ID]\t\tprint all processes or processes related to an ID\n\
	a\t\tprint arena's memmory\n\
	exit\t\texit program\n\
	help\t\tprint this message\n\
	n [NBR]\t\tjump to the next cycle or NBR cycles forward\n");
}

static t_interactive_option	vm_parse_user_input(
	const t_interactive_option *options, char *line, int *arg)
{
	size_t	i;
	size_t	opt_len;

	i = 0;
	while (options[i].name != NULL)
	{
		opt_len = s_len(options[i].opt);
		if (s_ncmp(options[i].opt, line, opt_len) == 0)
		{
			if (line[opt_len] != '\0')
				*arg = (int)s_toi(&line[opt_len]);
			break ;
		}
		i++;
	}
	return (options[i]);
}

static int	interactive_loop(t_arena *arena,
const t_interactive_option *options)
{
	int						arg;
	char					*line;
	t_interactive_option	option;

	while (1)
	{
		arg = -1;
		print(">>> ");
		line = NULL;
		if (s_readline(0, &line) <= 0)
			return (0);
		option = vm_parse_user_input(options, line, &arg);
		free(line);
		if (option.ptr != NULL)
			option.ptr(arena, arg);
		else
			break ;
	}
	if (option.name != NULL && s_ncmp(option.name, "n", 1) == 0 && arg > 0)
		return (arg);
	return (0);
}

int	vm_interactive_loop(t_arena *arena)
{
	static const t_interactive_option	options[] = {
	{"processes", "p", vm_interactive_print_processes},
	{"arena", "a", vm_interactive_print_arena},
	{"exit", "exit", vm_interactive_exit},
	{"help", "help", vm_interactive_help},
	{"next", "n", NULL},
	{0, 0, 0}
	};

	return (interactive_loop(arena, options));
}

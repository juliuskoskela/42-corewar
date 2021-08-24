#include "argparser.h"
#include "argparser_internal.h"
#include <stdlib.h>
#include "core.h"

int	_argparser_error(const char *msg, const t_argparser *argp,
t_argparser_state *state)
{
	if ((argp->flags & ARGP_NO_ERRS) == 0)
		print_fd(2, "%s: %s\n", msg, state->argv[state->next]);
	return (-1);
}

#include "vm.h"

void	vm_process_debug(char *msg, int verbosity)
{
	if (verbosity & VM_VERBOSE_OPS)
		print("%s\n", msg);
}

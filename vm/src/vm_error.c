#include "../inc/vm.h"

void	vm_error(const char *message)
{
	print("%s", message);
	exit(0);
}

#include "vm.h"

void    vm_test_print_processes(t_arena *a)
{
    t_process *p;

    p = a->processes;
    print("printing processes: \n");
    while (p)
    {
        vm_print_process_info(a, p);
    }
}
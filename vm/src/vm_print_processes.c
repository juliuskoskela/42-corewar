#include "vm.h"

static void vm_print_process(t_process *p)
{
    t_size i;

    print("id: %d pc: %d zf: %d\n", p->id, p->pc, p->zf);
    print("last_live: %d\n", p->last_live);
    print("cycles before exec: %d\n", p->cycles_before_execution);
    if (p->current_instruction.op != NULL)
        print("current instruction: %s\n", p->current_instruction.op->mnemonic);
    i = 0;
    while (i < 16)
    {
        print("R%d\t", i + 1);
        vm_reg_print(&p->registers[i]);
        print("\n");
        i++;
    }
}

void    vm_print_processes(t_arena *a, int id)
{
    t_bool      found_live_processes;
    t_process   *p;

    found_live_processes = 0;
    p = a->processes;
    print("printing processes:\n");
    while (p)
    {
        if (id == -1 || p->id == (t_uint32)id)
        {
            vm_print_process(p);
            print("\n");
            found_live_processes = 1;
        }
        p = p->next;
    }
    if (!found_live_processes)
        print("no live processes\n");
}

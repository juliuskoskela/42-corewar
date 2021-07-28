#ifndef VM_H
# define VM_H

///////////////////////////////////////////////////////////////////////////////
///
/// vm.h
///
/// \authors Satu Koskinen, Kalle Suomala, Julius Koskela
///
/// \brief
///
///////////////////////////////////////////////////////////////////////////////

# include "../../inc/corewar.h"

void	vm_error(const char *message);
void	vm_save_input(t_arena *arena, t_uint32 argc, char **argv);
void	vm_create_player(t_arena *arena, t_uint32 *player_number, char *name);
void	*vm_reverse_bytes(void *dst, void *src, t_size size);

#endif

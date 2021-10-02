#include "instr.h"

char	*vm_type_name(t_byte type)
{
	if (type == REG_CODE)
		return ("T_REG");
	else if (type == IND_CODE)
		return ("T_IND");
	else if (type == DIR_CODE)
		return ("T_DIR");
	else
		return ("NULL");
}

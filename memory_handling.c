#include "lib/core/inc/core.h"
#include "inc/corewar.h"
// #include "vm/inc/vm.h"

# define LITTLE 0
# define BIG 1
# define ROW_SIZE 64
#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
# define META	0x1 << 3
# define REG_SIZE 4
# define DIR_SIZE 2
# define IND_SIZE 2

typedef struct s_reg
{
	t_byte		mem[REG_SIZE];
	t_size		len;
}	t_reg;

typedef struct s_arg
{
	t_reg		data;
	t_uint8		type;
	t_uint8		promoted;
}	t_arg;

typedef struct s_instr
{
	t_arg		opcode;
	t_arg		acb;
	t_arg		args[3];
}	t_instr;

typedef struct s_acb
{
	t_uint8		arg[3];
}	t_acb;

typedef struct s_buff
{
	t_byte		*mem;
	t_size		pos;
	t_size		len;
}	t_buff;

typedef struct s_process
{
	t_uint32	id;
	t_size		pc;
	t_bool		zf;
	t_int32		last_live;
	t_int32		cycles_before_execution;
	t_instr		*current_instruction;
	t_reg		registers[REG_NUMBER];
}	t_process;

typedef struct s_player
{
	t_header	header;
	t_byte		program[CHAMP_MAX_SIZE];
}	t_player;

typedef struct s_arena
{
	t_player	players[MAX_PLAYERS];
	t_size		player_count;
	t_buff		buffer;
	t_size		offset;
	t_process	*processes;
	t_size		current_cycle;
}	t_arena;

typedef void (*t_exec)(t_arena *, t_process *);

t_uint8	g_endianness = LITTLE;

///////////////////////////////////////////////////////////////////////////////

t_reg	*reg_set(t_reg *src, t_size len)
{
	mzero(&src->mem, REG_SIZE);
	src->len = len;
	return (src);
}

void	reg_copy(t_reg *dst, t_reg *src)
{
	mcpy(dst->mem, src->mem, src->len);
}

void	reg_deref(t_byte *dst, t_reg *src)
{
	t_size	i;

	if (!dst || !src)
		return ;
	i = 0;
	if (g_endianness == LITTLE)
	{
		while (i < src->len)
		{
			dst[i] = src->mem[src->len - 1 - i];
			i++;
		}
	}
	else
	{
		while (i < src->len)
		{
			dst[i] = src->mem[i];
			i++;
		}
	}
}

void	reg_ref(t_reg *dst, t_byte *src)
{
	t_size	i;

	if (!dst || !src)
		return ;
	i = 0;
	if (g_endianness == LITTLE)
	{
		while (i < dst->len)
		{
			dst->mem[dst->len - 1 - i] = src[i];
			i++;
		}
	}
	else
	{
		while (i < dst->len)
		{
			dst->mem[i] = src[i];
			i++;
		}
	}
}

void	reg_print(t_reg *src, char *colour)
{
	t_size	i;

	if (!src || !src->len)
		return ;
	i = 0;
	print("%s");
	while (i < src->len - 1)
	{
		print("0x%02x ", src->mem[i]);
		i++;
	}
	print("0x%02x", src->mem[i]);
	print("%s", NRM);
}

///////////////////////////////////////////////////////////////////////////////

t_buff	*buff_new(t_buff *src, t_size len)
{
	src->mem = minit(sizeof(t_byte) * len);
	if (!src->mem)
		return (NULL);
	src->pos = 0;
	src->len = len;
	return (src);
}

void	buff_free(t_buff *src)
{
	if (!src)
		return ;
	free(src->mem);
	src->mem = NULL;
	src->pos = 0;
	src->len = 0;
}

void	buff_increment_pos(t_buff *src, t_size i)
{
	src->pos = (src->pos + i) % src->len;
}

t_buff	*buff_set(t_buff *src, t_size pos)
{
	if (!src)
		return (NULL);
	src->pos = pos % src->len;
	return (src);
}

t_bool	buff_read(t_byte *dst, t_buff *src, size_t dst_len)
{
	t_size	i;

	if (!dst || !src)
		return (FALSE);
	i = 0;
	while (i < dst_len)
	{
		dst[i] = src->mem[src->pos];
		buff_increment_pos(src, 1);
		i++;
	}
	return (TRUE);
}

t_bool	buff_write(t_buff *dst, t_byte *src, size_t src_len)
{
	t_size	i;

	if (!dst || !src)
		return (FALSE);
	i = 0;
	while (i < src_len)
	{
		dst->mem[dst->pos] = src[i];
		buff_increment_pos(dst, 1);
		i++;
	}
	return (TRUE);
}

void	buff_print(t_buff *src)
{
	t_size	i;

	i = 0;
	while (i < src->len)
	{
		if (i == ROW_SIZE)
			print("\n");
		print("%#02x ", src->mem[i]);
		i++;
	}
	print("\n");
}

void	buff_print_overlay(t_buff *src, t_size start, t_size len, char *colour)
{
	t_size	i;
	t_size 	rem;

	rem = (start + len) % src->len;
	i = 0;
	while (i < src->len)
	{
		if (i % ROW_SIZE == 0)
			print("\n");
		if (i == start || (rem > 0 && i == 0))
			print("%s", colour);
		print("%02x ", src->mem[i]);
		if (i == start + len || (rem > 0 && i == rem - 1))
			print("%s", NRM);
		i++;
	}
	print("%s\n\n", NRM);
}

///////////////////////////////////////////////////////////////////////////////

void	vm_instr_null(t_arena *a, t_process *p)
{
	return ;
}

char	*vm_type_name(t_byte type)
{
	if (type == REG_CODE)
		return ("T_REG");
	else if (type == IND_CODE)
		return ("T_IND");
	else if (type == DIR_CODE)
		return ("T_DIR");
	else
		return ("EMPTY");
}

void	vm_instr_ld(t_arena *arena, t_process *p)
{
	t_uint8		reg_addr;
	t_uint16	mem_addr;

	reg_deref((t_byte *)&reg_addr, &p->current_instruction->args[1].data);
	if (reg_addr > 16)
		return ;
	if (p->current_instruction->args[0].type == DIR_CODE)
		reg_copy(&p->registers[reg_addr - 1], &p->current_instruction->args[0].data);
	else
	{
		reg_deref((t_byte *)&mem_addr, &p->current_instruction->args[0].data);
		if (mem_addr % IDX_MOD != 0)
			p->zf = TRUE;
		buff_set(&arena->buffer, p->pc + mem_addr % IDX_MOD);
		buff_read((t_byte *)&p->registers[reg_addr - 1], &arena->buffer, IND_SIZE);
	}
	print("[%#08llu]%s[%#08x]%s[LOAD][%s src, %s dst][", arena->current_cycle, GRN, p->id, NRM, vm_type_name(p->current_instruction->args[0].type), vm_type_name(p->current_instruction->args[1].type));
	reg_print(&p->registers[reg_addr - 1], GRN);
	print("]\n");
	return ;
}

static const t_exec g_instr[] =
{
	vm_instr_null,
	vm_instr_ld,
};

///////////////////////////////////////////////////////////////////////////////

t_process	*vm_new_process(t_uint32 id, t_size pc)
{
	t_process	*new;
	t_size		i;

	new = malloc(sizeof(t_process));
	if (!new)
		return (NULL);
	new->id = id;
	new->pc = pc;
	new->zf = FALSE;
	new->last_live = 0;
	new->cycles_before_execution = 0;
	new->current_instruction = NULL;
	i = 0;
	while (i < REG_NUMBER)
	{
		reg_set(&new->registers[i], REG_SIZE);
		i++;
	}
	return (new);
}

t_arg	*vm_arg_new(t_arg *dst, t_uint8 type, t_uint8 promoted)
{
	mzero(dst, sizeof(t_arg));
	dst->type = type;
	if (type == DIR_CODE)
	{
		if (promoted == TRUE)
		{
			dst->promoted = TRUE;
			dst->data.len = REG_SIZE;
		}
		else
			dst->data.len = DIR_SIZE;
	}
	else if (type == IND_CODE)
		dst->data.len = IND_SIZE;
	else if (type == REG_CODE)
		dst->data.len = 1;
	else
		dst->data.len = 1;
	return (dst);
}

t_arg	*vm_arg_read(t_arg *dst, t_buff *src)
{
	buff_read((t_byte *)&dst->data.mem, src, dst->data.len);
	return (dst);
}

t_acb	vm_decomp_acb(t_byte acb)
{
	t_acb	out;

	out.arg[0] = (acb & 0b11000000) >> 6;
	out.arg[1] = (acb & 0b00110000) >> 4;
	out.arg[2] = (acb & 0b00001100) >> 2;
	return (out);
}

t_byte	vm_compose_acb(t_acb *acb)
{
	t_byte out;

	out = (acb->arg[0] | (acb->arg[1] << 2) | (acb->arg[2] << 4));
	return (out);
}

t_size	vm_instr_size(t_instr *src)
{
	return (
		src->opcode.data.len
		+ src->acb.data.len
		+ src->args[0].data.len
		+ src->args[1].data.len
		+ src->args[2].data.len);
}

void	vm_print_instr(t_instr *instr)
{
	reg_print(&instr->opcode.data, BLU);
	reg_print(&instr->acb.data, YEL);
	reg_print(&instr->args[0].data, CYN);
	reg_print(&instr->args[1].data, MAG);
	reg_print(&instr->args[2].data, RED);
}

static const t_byte g_arg_codes[] =
{
	0,
	1,
	(1U << 1U),
	(1U << 2U)
};

t_bool	vm_check_acb(t_op op, t_acb acb)
{
	t_byte	arg;
	t_uint8	params[3];
	t_size	i;

	params[0] = op.param_types.param1;
	params[1] = op.param_types.param2;
	params[2] = op.param_types.param3;
	i = 0;
	while (i < op.param_count)
	{
		arg = g_arg_codes[acb.arg[i]];
		if ((arg & params[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	vm_read_instr(t_buff *b, t_process *p)
{
	t_acb			acb;
	t_byte			opcode;
	t_instr			*instr;
	t_op			op;
	t_bool			promoted;
	t_size			i;

	promoted = FALSE;
	instr = minit(sizeof(t_instr));

	// Set buffet to the position of the program counter.
	buff_set(b, p->pc);

	// Read opcode.
	vm_arg_read(vm_arg_new(&instr->opcode, META, FALSE), b);
	reg_deref((t_byte *)&opcode, &instr->opcode.data);

	// Validate opcode
	if (opcode > OP_COUNT)
	{
		print("%s[%#08x] %sERR_INVALID_OPCODE \n", RED, p->id, NRM);
		p->pc++;
		return ;
	}

	// Get op from global tab.
	op = g_op_tab[opcode - 1];

	// Check if corresponding op has acb.
	if (op.has_argument_coding_byte == TRUE)
	{
		// Read acb.
		vm_arg_read(vm_arg_new(&instr->acb, META, FALSE), b);

		// Decompose acb
		acb = vm_decomp_acb(*instr->acb.data.mem);

		// Check that flags are valid.
		if (vm_check_acb(op, acb) == FALSE)
		{
			print("%s[%#08x] %sERR_INVALID_ACB \n", RED, p->id, NRM);
			p->pc++;
			return ;
		}
	}
	// If instruction has no acb, acb is composed from the op tab (only 1 possible type per param).
	else
	{
		acb.arg[0] = op.param_types.param1;
		acb.arg[1] = op.param_types.param2;
		acb.arg[2] = op.param_types.param3;
	}

	// Check direct value promotion.
	if (acb.arg[0] == REG_CODE || acb.arg[1] == REG_CODE || acb.arg[2] == REG_CODE)
		promoted = TRUE;

	// Read arguments.
	i = 0;
	while (i < op.param_count)
	{
		vm_arg_read(vm_arg_new(&instr->args[i], acb.arg[i], promoted), b);
		i++;
	}
	p->current_instruction = instr;
	print("%s[%#08x] %sCOMP_READ_INSTR: ", GRN, p->id, NRM);
	vm_print_instr(p->current_instruction);
	p->cycles_before_execution = op.cycles;
	print("\n%s[%#08x] %sCYCLES_TO_EXEC: %lu\n", GRN, p->id, NRM, p->cycles_before_execution);
}

void	vm_execute_instr(t_arena *arena, t_process *p)
{
	t_byte	opcode;

	reg_deref((t_byte *)&opcode, &p->current_instruction->opcode.data);
	if (opcode < 1 || opcode > 16)
		return ;
	g_instr[opcode - 1](arena, p);
	p->pc = (p->pc + vm_instr_size(p->current_instruction)) % MEM_SIZE;
	free(p->current_instruction);
	p->current_instruction = NULL;
}

void	exit_error(char *msg)
{
	print("%s\n", msg);
	exit(1);
}

void	read_player_header(t_header *player, int fd)
{
	t_reg	player_magic;
	t_reg	player_program_size;

	reg_set(&player_magic, sizeof(player->magic));
	if (read(fd, &player_magic.mem, sizeof(player->magic)) != sizeof(player->magic))
		exit_error("Failed to read magic number");
	reg_deref((t_byte *)&player->magic, &player_magic);
	if (read(fd, &player->prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		exit_error("Failed to read program name");
	reg_set(&player_program_size, sizeof(player->prog_size));
	if (read(fd, &player_program_size, sizeof(player->prog_size)) != sizeof(player->prog_size))
		exit_error("Failed to read program size");
	reg_deref((t_byte *)&player->prog_size, &player_program_size);
	if (player->prog_size > CHAMP_MAX_SIZE)
		exit_error("Player program size > CHAMP_MAX_SIZE");
	if (read(fd, &player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		exit_error("Failed to read comment");
}

void	read_player_program(t_byte *program, int prog_size, int fd)
{
	if (read(fd, program, prog_size) != prog_size)
		exit_error("Failed to read program");
}

void	vm_read_player(t_arena *arena, const char *path)
{
	int			fd;
	int			player_index;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_error("Invalid path to player");
	player_index = arena->player_count;
	mzero(&arena->players[player_index], sizeof(t_player));
	read_player_header(&arena->players[player_index].header, fd);
	read_player_program((t_byte *)&arena->players[player_index].program,
		arena->players[player_index].header.prog_size, fd);
	arena->player_count += 1;
	arena->offset = MEM_SIZE / arena->player_count;
}

void	vm_init_arena(t_arena *arena)
{
	mzero(arena, sizeof(t_arena));
	buff_new(&arena->buffer, MEM_SIZE);
}

///////////////////////////////////////////////////////////////////////////////

void	test_ld(const char *corfile)
{
	t_arena			arena;
	t_byte			secret_val;
	t_size			process_pc;
	t_process	*p;

	vm_init_arena(&arena);
	vm_read_player(&arena, corfile);

	secret_val = 42;

	print("\n%sSTART OF BATTLE LOG%s\n\n", BLU, NRM);
	print("%s[current_cycle][process_id][action][result]%s\n\n", GRN, NRM);

	// Create process.
	process_pc = MEM_SIZE - 3;
	mcpy(&arena.buffer.mem[(process_pc + 70) % MEM_SIZE], &secret_val, 1);
	buff_set(&arena.buffer, process_pc);
	buff_write(&arena.buffer, (t_byte *)&arena.players[0].program, arena.players[0].header.prog_size);
	p = vm_new_process(1, process_pc);

	// Read instruction from memory.
	vm_read_instr(&arena.buffer, p);

	// Print buffer.
	buff_print_overlay(&arena.buffer, process_pc, vm_instr_size(p->current_instruction), GRN);

	// Execute current instruction.
	vm_execute_instr(&arena, p);

	buff_free(&arena.buffer);
	free(p);
}

int main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	else
	{
		if (s_cmp(argv[1], "BIG") == 0)
			g_endianness = BIG;
		else
			g_endianness = LITTLE;
	}
	test_ld(argv[2]);
}

// void	test_ld()
// {
// 	// Set example values.
// 	t_byte			opcode = 2;
// 	t_byte			acb = vm_compose_acb(&(t_acb){T_IND, T_REG, EMPTY});
// 	t_size			pc = MEM_SIZE - 3;
// 	t_uint16		ind_addr = 70;
// 	t_uint16		secret_val = 42;
// 	t_uint8			reg_addr = 3;

// 	// Create the example incstruction (bit convoluted but just setup for example).

// 	t_reg	instr_mem;
// 	t_reg	ind_addr_ref;
// 	t_reg	reg_addr_ref;

// 	reg_set(&instr_mem, 5);
// 	mcpy(&instr_mem.mem[0], &opcode, 1);
// 	mcpy(&instr_mem.mem[1], &acb, 1);
// 	reg_set(&ind_addr_ref, 2);
// 	reg_ref(&ind_addr_ref, (t_byte *)&ind_addr);
// 	mcpy(&instr_mem.mem[2], ind_addr_ref.mem, 2);
// 	reg_set(&ind_addr_ref, 1);
// 	reg_ref(&ind_addr_ref, (t_byte *)&reg_addr);
// 	mcpy(&instr_mem.mem[4], &reg_addr, 1);

// 	// Create buffer and write instruction to buffer at pc.

// 	t_buff	buffer;

// 	buff_new(&buffer, MEM_SIZE);
// 	buff_set(&buffer, pc);
// 	buff_write(&buffer, &instr_mem);

// 	// Hide secret val.

// 	mcpy(&buffer.mem[(pc + ind_addr) % MEM_SIZE], &secret_val, 2);

// 	// Print buffer.

// 	buff_print_overlay(&buffer, pc, 5, GRN);

// 	// Create process.

// 	t_process	*p;

// 	print("\n%sSTART OF BATTLE LOG%s\n\n", BLU, NRM);
// 	print("%s[process_id]%s\n\n", GRN, NRM);
// 	p = vm_new_process(1, pc);
// 	buff_set(&buffer, 0);

// 	// Read instruction from memory.

// 	vm_read_instr(&buffer, p);

// 	// Execute current instruction.

// 	vm_execute_instr(&buffer, p);

// 	buff_free(&buffer);

// 	free(p);
// }

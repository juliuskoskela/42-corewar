###############################################################################
#
#	Makefile
#
###############################################################################

ASM	= asm/
VM	= vm/

all: vm asm
	mkdir -p bin
	cp vm/corewar bin
	cp asm/asm bin

.PHONY: vm asm clean fclean re

vm:
	make -C $(VM)

asm:
	make -C $(ASM)

clean:
	make clean -C $(VM)
	make clean -C $(ASM)

fclean:
	make fclean -C $(VM)
	make fclean -C $(ASM)
	rm -rf bin

re: fclean all

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
	$(MAKE) -C $(VM)

asm:
	$(MAKE) -C $(ASM)

clean:
	$(MAKE) clean -C $(VM)
	$(MAKE) clean -C $(ASM)

fclean:
	$(MAKE) fclean -C $(VM)
	$(MAKE) fclean -C $(ASM)
	rm -rf test/output
	rm -rf bin

re: fclean all

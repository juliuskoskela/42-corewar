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

test: all
	cd test && bash test_single_player_diff.sh subject_reference/champs/Gagnant.s 5000
	cd test && bash test_multiplayer_diff.sh subject_reference/champs/examples/bee_gees.s subject_reference/champs/examples/zork.s 10000
	@echo "\\n\033[1;33mRunning with no champion params. Usage should be outputted\033[0m \\n"
	@-./bin/corewar
	@echo "\\n\033[1;33mRunning with too many champion. Usage should be outputted\033[0m \\n"
	@-./bin/corewar champ.cor champ.cor champ_3.cor champ_4.cor champ_5.cor
	@echo "\\n\033[1;33mtest champion distribution\033[0m \\n"
	@cd test && bash test_multiplayer_diff.sh test_instructions/test_live.s test_instructions/test_live.s 1

re: fclean all

## VM: A virtual arena for players to battle as processes in its memory

```
➜  ./bin/corewar --help
Usage: ./bin/corewar [OPTION...] <path/to/player.cor> ...
corewar: description

 -d, --dump nbr_cycles        dump memory to standard output and exit
				after nbr_cycles (> 0)
 -s, --show nbr_cycles        dump memory every N cycles and pause until
				a key is pressed
 -v, --verbosity level        verbosity level (set between 0 and 31)
 -c, --coloured               use colours in printing to standard output
 -n, --nbr nbr                set the number (> 0) of the next player
 -i, --interactive            execute vm in an interactive mode
     --help                   print this help message
     --usage                  print a short usage message
```

```
➜  ./bin/corewar --usage
Usage: ./bin/corewar [-d nbr_cycles] [-s nbr_cycles] [-v level]
	 [-c] [-n nbr] [-i] [--dump nbr_cycles] [--show nbr_cycles] [--verbosity level]
	 [--coloured] [--nbr nbr] [--interactive] [--help] [--usage]
	 <path/to/player.cor> ...
```
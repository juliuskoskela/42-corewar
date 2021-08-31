.name "TEST_LFORK"
.comment "garden of LONG forking paths"

# lfork offset

# Long version of fork:
# Forks this process: creates a new process that
# inherits the current process' registers and zf;
# spawned process has its PC set to parent's PC offseted by offseted

# x cycles

# { T_DIR }

lfork 100
lfork -100
lfork 1000
lfork -1000
lfork 0
lfork 42
lfork 1

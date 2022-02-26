.name "TEST_FORK"
.comment "garden of forking paths"

# fork offset

# Forks this process: creates a new process that
# inherits the current process' registers and zf;
# spawned process has its PC set to parent's PC offseted by offseted

# x cycles

# { T_DIR }

forkhere:
fork %100
fork %-100
fork %1000
fork %-1000
fork %10000
fork %-10000
fork %0
fork %42
fork %1
fork %:forkhere

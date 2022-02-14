.name "TEST_sub"
.comment "test sub! instruction!!!!!"

# sub lhs, rhs, dst

# Computes lhs - rhs and stores the result in register dst
# Result affects zf

# x cycles

# { T_REG, T_REG, T_REG }

sub r2, r4, r5
sub r1, r2, r1
sub r1, r1, r1
sub r10, r15, r16
sub r8, r12, r3

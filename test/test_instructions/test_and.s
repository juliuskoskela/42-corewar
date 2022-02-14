.name "TEST_and"
.comment "test and instruction!!!!!"

# and lhs, rhs, dst

# Computes lhs & rhs and stores the result in register dst
# Result affects zf

# x cycles

# { T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG }

and r2, r4, r4
and r2, r4, r5
and r1, r1, r1
and r10, r15, r16
and r8, r12, r3

and %2, r4, r4
and %2, r4, r5
and %1, r1, r1
and %10, r15, r16
and %8, r12, r3

and r2, %4, r4
and r2, %4, r5
and r1, %4, r1
and r10,%4, r16
and r8, %4, r3

and %2, %4, r4
and %2, %4, r5
and %1, %4, r1
and %10,%4, r16
and %8, %4, r3

and 2, %4, r4
and 2, %4, r5
and 1, %4, r1
and 10,%4, r16
and 8, %4, r3

and %2, 4, r4
and %2, 4, r5
and %1, 4, r1
and %10,4, r16
and %8, 4, r3

and 2, 4, r4
and 2, 4, r5
and 1, 4, r1
and 10,4, r16
and 8, 4, r3

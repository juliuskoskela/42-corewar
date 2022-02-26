.name "TEST_or"
.comment "test or instruction!!!!!"

# or lhs, rhs, dst

# Computes lhs | rhs and stores the result in register dst
# Result affects zf

# x cycles

# { T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG }

or %2, r4, r4
or %2, r4, r5
or %1, r1, r1
or %10, r15, r16
or %8, r12, r3

or r2, %4, r4
or r2, %4, r5
or r1, %4, r1
or r10,%4, r16
or r8, %4, r3

or %2, %4, r4
or %2, %4, r5
or %1, %4, r1
or %10,%4, r16
or %8, %4, r3

or 2, %4, r4
or 2, %4, r5
or 1, %4, r1
or 10,%4, r6
or 8, %4, r3

or %2, 4, r4
or %2, 4, r5
or %1, 4, r1
or %10,4, r6
or %8, 4, r3

or 2, 4, r4
or 2, 4, r5
or 1, 4, r1
or 10,4, r6
or 8, 4, r3

or r2, r16, r4
or r3, r4, r5
or r2, r4, r4
or r2, r4, r5
or r1, r1, r1
or r10, r15, r16
or r8, r12, r3

st r1, 100
st r2, 100
st r3, 100
st r4, 100
st r5, 100
st r6, 100
st r7, 100
st r8, 100
st r9, 100
st r10, 100
st r11, 100
st r12, 100
st r13, 100
st r14, 100
st r15, 100
st r16, 100

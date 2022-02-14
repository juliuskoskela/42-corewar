.name "TEST_xor"
.comment "test xor instruction!!!!!"

# xor lhs, rhs, dst

# Computes lhs ^ rhs and stores the result in register dst
# Result affects zf

# x cycles

# { T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG }

xor r2, r4, r4
xor r2, r4, r5
xor r1, r1, r1
xor r10, r15, r16
xor r8, r12, r3

xor %2, r4, r4
xor %2, r4, r5
xor %1, r1, r1
xor %10, r15, r16
xor %8, r12, r3

xor r2, %4, r4
xor r2, %4, r5
xor r1, %4, r1
xor r10,%4, r16
xor r8, %4, r3

xor %2, %4, r4
xor %2, %4, r5
xor %1, %4, r1
xor %10,%4, r16
xor %8, %4, r3

xor 2, %4, r4
xor 2, %4, r5
xor 1, %4, r1
xor 10,%4, r16
xor 8, %4, r3

xor %2, 4, r4
xor %2, 4, r5
xor %1, 4, r1
xor %10,4, r16
xor %8, 4, r3

xor 2, 4, r4
xor 2, 4, r5
xor 1, 4, r1
xor 10,4, r16
xor 8, 4, r3

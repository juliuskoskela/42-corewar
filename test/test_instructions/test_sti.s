.name "TEST_STI"
.comment "TESTING STI"

# sti src, lhs, rhs

# Computer lhs + rhs and uses the result as an offset
# to address memory and store the value of register src
# at that memory location

# x cycles

# { T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG }

liveup: live %-1

sti r1, r2, r3
sti r16, r10, r2

sti r1, %42, %-500
sti r2, %1, %542

sti r1, %:liveup, %1
sti r1, %:liveishere, %1

liveishere:
live %100

sti r1, 42, r1
sti r1, r1, %1000
sti r1, %-42, %666
sti r1, 0, %0
sti r1, %0, %0
sti r1, -10, %-10
sti r1, %-10, %-10
sti r1, 34, %45
sti r1, %34, %45

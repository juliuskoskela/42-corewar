# 0c 00 64 0c, ff 9c 0c 03, e8 0c fc 18, 0c 00 00 0c, 00 2a 0c 00, 01 00 00 00-> test_fork

# 02 90 0c 00 64 0c 02 02 90 03 0c 9c ff 03 02 90 18 fc 0c e8 04 02 90 0c 00 00 0c 05 02 90 00 0c 2a 00 06 02 90 01 00 00 00 07
.name "TEST_COMPLEX"
.comment "test load and store instruction to memory"

ld %0x0c00640c, r2
ld %51158271, r3
ld %419171560, r4
ld %201326604, r5
ld %797184, r6
ld %0x01000000, r7

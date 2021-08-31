.name "TEST_LIVE"
.comment "living the lyfe"

# live id

# Reports player #id as being alive

# x cycles

# { T_DIR }

live %1
live %3
live %0
live %100
live %-15

# Store process ID from r1 to live's argument above; assumes sti works
sti r1, %:live, %1
live: live %5



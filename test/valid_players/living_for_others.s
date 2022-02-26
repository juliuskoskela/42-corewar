.name "living for others"
.comment "i love my enemies"

ld %1, r2
ld %-1, r3
add r1, r2, r10
add r1, r3, r11

sti r10, %:live, %1
sti r11, %:live_again, %1
and r1, %0, r1

live:	live %1

live_again:
		live %1
		zjmp %:live

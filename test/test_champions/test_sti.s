.name "sti_tester"
.comment "TESTING STI"

l2:		sti r1, %:live, %1
		; and r1, %0, r1

live:	live %5
		; zjmp %:live

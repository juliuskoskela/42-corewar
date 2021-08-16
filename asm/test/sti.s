.name "sti_tester"
.comment "TESTING STI"

l2:		sti r1, %2, %2
		; and r1, %0, r1

live:	live %1
		; zjmp %:live

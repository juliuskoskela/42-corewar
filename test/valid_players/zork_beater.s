.name "ZORK BEATER"
.comment "i'm here just to bring that one process down, and to live to see it"

; first, execute a valid live

start:	sti r1, %:live, %1
		and r1, %0, r2
live:	live %1

; fork a process that will only execute the live loop

fork %:fork_beginning

; our basic living loop

store_pid:	sti r1, %:live_loop, %1
			and r1, %0, r2

live_loop:	live %1
			zjmp %:live

fork_beginning:
		sti r1, %:live_2, %1
		and r1, %0, r2

live_2: live %1
		zjmp %:live_2

sti r1, %:live_3, %1
		and r1, %0, r2

live_3: live %1
		zjmp %:live_3

fork %:start
zjmp %:start

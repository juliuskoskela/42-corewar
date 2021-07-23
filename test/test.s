	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 3
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16                     ; =16
	.cfi_def_cfa_offset 16
	str	wzr, [sp, #12]
	mov	w8, #3
	str	w8, [sp, #8]
	ldr	w8, [sp, #8]
	cmp	w8, #5                          ; =5
	b.le	LBB0_2
; %bb.1:
	mov	w8, #10
	str	w8, [sp, #4]
	b	LBB0_3
LBB0_2:
	mov	w8, #20
	str	w8, [sp, #4]
LBB0_3:
	ldr	w8, [sp, #4]
	subs	w8, w8, #2                      ; =2
	str	w8, [sp, #8]
	mov	w8, #0
	mov	x0, x8
	add	sp, sp, #16                     ; =16
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols

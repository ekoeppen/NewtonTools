 	.macro JUMPTABLE name address
        .text
        .align 4
        .global \name
        .type \name, %function
\name:
        ldr pc, [pc, #-4]
        .word \address
        .endm

	JUMPTABLE __xxx_XS001_, 0x01bb2974
	JUMPTABLE setjmp, 0x01bb2974

 	.macro JUMPTABLE name address
        .text
        .align 4
        .global \name
        .type \name, %function
\name:
        ldr pc, [pc, #-4]
        .word \address
        .endm

	JUMPTABLE Debugger, 0x01bb2958

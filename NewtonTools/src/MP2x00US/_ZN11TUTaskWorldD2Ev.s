 	.macro JUMPTABLE name address
        .text
        .align 4
        .global \name
        .type \name, %function
\name:
        ldr pc, [pc, #-4]
        .word \address
        .endm

	JUMPTABLE _ZN11TUTaskWorldD2Ev, undef
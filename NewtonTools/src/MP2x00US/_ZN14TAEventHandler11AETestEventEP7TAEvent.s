 	.macro JUMPTABLE name address
        .text
        .align 4
        .global \name
        .type \name, %function
\name:
        ldr pc, [pc, #-4]
        .word \address
        .endm

	JUMPTABLE _ZN14TAEventHandler11AETestEventEP7TAEvent, undef

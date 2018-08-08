.section .text
.global idt_flush
.type idt_flush, @function
idt_flush:
	mov 4(%esp), %eax 		/* copy the address of IDT to eax */
	lidt (%eax) 			/* Load IDT */
	ret
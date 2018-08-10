.section .text
.global gdt_flush
.type gdt_flush, @function
gdt_flush:
	mov 4(%esp), %eax 		/* copy the address of GDT to eax */
	lgdt (%eax) 			/* Load GDT */
	/* Each GDT entry is 8 bytes */
	/* the data segment is at 0x10 (3rd entry GDT) */
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	/* Do a far jump to set code segment to 0x08 (2nd entry in GDT) */
	jmp $0x08, $.flush
.flush:
	ret
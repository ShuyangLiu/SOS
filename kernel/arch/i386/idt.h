#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H
/*
 * idt.h
 *
 *	The Interrupt Descriptor Table (IDT)
 * 	IDT tells the processor where to find the handler for each interrupt
 *	
 *	It is an array of entries, each one corresponding to an interrupt number
 * 	There are 256 possible interrupt numbers. Therefore, there should be 256 
 *	interrupt entries defined in the IDT (even a NULL entry is fine). 
 *	Otherwise, the processor would panic and reset. 
 * 
 *	The special CPU dedicated interrupts are shown below:
 *		0		- 	Division by zero exception
 *		1		- 	Debug exception
 *		2		- 	Non maskable interrupt
 *		3		- 	Breakpoint exception
 *		4		- 	'Into detected overflow'
 *		5		- 	Out of bounds exception
 *		6		- 	Invalid opcode exception
 *		7		- 	No coprocessor exception
 *		8		- 	Double fault (pushes an error code)
 *		9		- 	Coprocessor segment overrun
 *		10		- 	Bad TSS (pushes an error code)
 *		11		- 	Segment not present (pushes an error code)
 *		12		- 	Stack fault (pushes an error code)
 *		13		- 	General protection fault (pushes an error code)
 *		14		- 	Page Fault (pushes an error code)
 *		15		- 	Unknown interrupt exception
 *		16		- 	Coprocessor fault
 *		17		- 	Alignment check exception
 *		18		- 	Machine check exception
 *		19-31	-	Reserved
 *
 */
#include <stdint.h>
#include <kernel/idt_init.h>
/* 
 * idt_entry_struct
 *
 *	This is a struct describing an interrupt gate
 *
 */
struct idt_entry_struct
{
	// The lower 16 bits of the base address 
	uint16_t base_lo;

	// Kernel segment selector
	uint16_t sel;

	// Always should be zero
	uint8_t always0;

	// Flags
	uint8_t flags;

	// The upper 16 bits of the base address
	uint16_t base_hi;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// Address of IDT
struct idt_ptr_struct
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

// The ISR handlers defined in the assembly code
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif
/*
 * gdt.c
 * 
 *	Initialization of the Global Descriptor Table (GDT)
 *
 */

#include "gdt.h"

/* Global Variables */
gdt_entry_t gdt_entries[5]; // The GDT entries
gdt_ptr_t gdt_ptr; // The location of the GDT

/*
 * gdt_set_gate(index, base, limit, access, granularity)
 *
 * 	A private function used to set GDT entries
 *
 */
static void 
gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

// This is defined in gdt.s
extern void 
gdt_flush(uint32_t);

/* 
 * init_gdt()
 *
 * 	Set up the Global Descriptor Table (GDT)
 *
 * Inputs:
 * 		None
 *
 */
void
init_gdt()
{
	// Size of the GDT, always less one of the true size
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;

	// Starting address of the GDT
	gdt_ptr.base = (uint32_t)&gdt_entries;

	// The Null segment Descriptor
	// 	Index:			0x0
	// 	Base: 			0x00000000		(0000 0000 0000 0000 0000 0000 0000 0000)
	// 	Limit: 			0x00000000 		(0000 0000 0000 0000 0000 0000 0000 0000)
	// 	Access:			0x00			(0000 0000)
	// 	Granularity:	0x00			(0000 0000)
	gdt_set_gate(0, 0, 0, 0, 0);

	// The Code segment Descriptor
	// 	Index:			0x1
	// 	Base: 			0x00000000		(0000 0000 0000 0000 0000 0000 0000 0000)
	// 	Limit: 			0xffffffff 		(1111 1111 1111 1111 1111 1111 1111 1111)
	// 	Access:			0x9A			(1001 1010)
	// 	Granularity:	0xCF			(1100 1111)
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);


	// The Data segment Descriptor
	// 	Index:			0x2
	// 	Base: 			0x00000000		(0000 0000 0000 0000 0000 0000 0000 0000)
	// 	Limit: 			0xffffffff 		(1111 1111 1111 1111 1111 1111 1111 1111)
	// 	Access:			0x92			(1001 0010)
	// 	Granularity:	0xCF			(1100 1111)
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	// The User Mode Code segment Descriptor
	// 	Index:			0x3
	// 	Base: 			0x00000000		(0000 0000 0000 0000 0000 0000 0000 0000)
	// 	Limit: 			0xffffffff 		(1111 1111 1111 1111 1111 1111 1111 1111)
	// 	Access:			0xFA			(1111 1010)
	// 	Granularity:	0xCF			(1100 1111)
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

	// The User Mode Data segment Descriptor
	// 	Index:			0x4
	// 	Base: 			0x00000000		(0000 0000 0000 0000 0000 0000 0000 0000)
	// 	Limit: 			0xffffffff 		(1111 1111 1111 1111 1111 1111 1111 1111)
	// 	Access:			0xF2			(1111 0010)
	// 	Granularity:	0xCF			(1100 1111)
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	// Call gdt_flush from the assembly code
	gdt_flush((uint32_t)&gdt_ptr);
}

/*
 * gdt_set_gate(index, base, limit, access, granularity)
 *
 * 	A private function used to set GDT entries
 *
 * Inputs:
 *		index 		: the index of the entry to be entered
 * 		base 		: the base address of the segment
 *		limit 		: the size of the segment
 *		access 		: access flags
 *		gran 		: granularity flags
 *
 */
static void
gdt_set_gate(int32_t index, uint32_t base, uint32_t limit, 
				uint8_t access, uint8_t gran)
{
	gdt_entries[index].base_low    = (base & 0xFFFF);
    gdt_entries[index].base_middle = (base >> 16) & 0xFF;
    gdt_entries[index].base_high   = (base >> 24) & 0xFF;

    gdt_entries[index].limit_low   = (limit & 0xFFFF);
    gdt_entries[index].granularity = (limit >> 16) & 0x0F;
    
    gdt_entries[index].granularity |= gran & 0xF0;
    gdt_entries[index].access      = access;

}
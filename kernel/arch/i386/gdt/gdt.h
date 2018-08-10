#ifndef ARCH_I386_GDT_H
#define ARCH_I386_GDT_H

/*
 * gdt.h
 *
 * 	GRUB sets a GDT up for us but we don't know the address of it or what's in it
 *  so a better idea is to set up a new GDT on ourselves to avoid overwriting data 
 *  to that unknown GDT
 *
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/gdt_init.h>

/*
 * gdt_entry_struct
 *
 *    This structure contains the value of one GDT entry.
 * 	  We use the attribute 'packed' to tell GCC not to change
 * 	  any of the alignment in the structure.
 */
struct gdt_entry_struct
{
	// The lower 16 bits of the limit.
    uint16_t limit_low;

    // The lower 16 bits of the base.
    uint16_t base_low;

    // The next 8 bits of the base.
    uint8_t  base_middle;

    /* 
     Access flags Format:
       | 7 | 6   5 | 4 | 3 2 1 0 |
       | P |  DPL  | S |  TYPE   |
       P: Is the segment present? (1 = Yes)
       DPL: Descriptor Privilege Level (Ring 0 - 3)
       S: Descriptor Type
       TYPE: Segment Type (code segment, data segment, etc.)
    */
    uint8_t  access;

    /* 
     Granularity byte Format:
       | 7 | 6 | 5 | 4 | 3 2 1 0 |
       | G | D | 0 | A |  limit  |
       G: Granularity (0 = 1 byte, 1 = 1kbyte)
       D: Operand Size (0 = 16 bit, 1 = 32 bit)
       0: Should always be 0
       A: Available for system use (always zero) 
       limit: limit 19:16
    */
    uint8_t  granularity;

	// The last 8 bits of the base.
    uint8_t  base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;


// Address of GDT
struct gdt_ptr_struct
{
	// the upper 16 bits of all selector limits
	uint16_t limit;

	// the address of the first gdt entry
	uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

#endif
/*
 * A very basic interface for kernel to print things to the screen
 * Implementations are architecture specific
 * Therefore it should be implemented in /kernel/arc/<architecture>
 */

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

// Function Declarations
void terminal_initialize(void);
void terminal_writestring(const char* data);
void terminal_write(const char* data, size_t size);

#endif
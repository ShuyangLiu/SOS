#include <kernel/tty.h>
#include "isr.h"

void isr_handler(registers_t regs)
{
	terminal_writestring("RECEIVED INTERRUPT: ");
	terminal_writedec(regs.int_no);
	terminal_writestring("\n");
}
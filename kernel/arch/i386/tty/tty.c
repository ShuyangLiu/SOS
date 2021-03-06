#include "vga.h"

extern void outb(uint16_t port, uint8_t data);

// Function Declarations
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_scroll();
void terminal_move_cursor(uint16_t);

// Global Variables
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, 
										VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	if (c == '\n') {
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();
		terminal_column = 0;
		terminal_move_cursor((terminal_row*VGA_WIDTH+terminal_column));
		return;
	} else {
		terminal_putentryat(c, terminal_color, 
							terminal_column, 
							terminal_row);
	}

	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();
	}
	terminal_move_cursor((terminal_row*VGA_WIDTH+terminal_column));
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void terminal_writedec(int n)
{
	if (n == 0) {
        terminal_putchar('0');
        return;
    }

    int32_t acc = n;
    char c[32];
    int i = 0;
    while (acc > 0) {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0) {
        c2[i--] = c[j++];
    }
    terminal_writestring(c2);
}

void terminal_memcpy(uint16_t * src, uint16_t * dst, size_t size)
{
	// Copies the memory from src to dst
	for(size_t i = 0; i < size; i++){
		dst[i] = src[i];
	}
} 

void terminal_scroll()
{
	// move the whole memory buffer content up a row
	size_t i;
	terminal_memcpy(terminal_buffer+VGA_WIDTH, terminal_buffer, VGA_WIDTH*(VGA_HEIGHT-1));

	// clear the last row
	for (i = 0; i < VGA_WIDTH; ++i){
		terminal_putentryat(' ', terminal_color, i, VGA_HEIGHT-1);
	}
	terminal_column = 0;
	terminal_row = VGA_HEIGHT-1;

	terminal_move_cursor((terminal_row*VGA_WIDTH+terminal_column));
}

void terminal_move_cursor(uint16_t pos)
{
	outb(TERMINAL_COMMAND_PORT, TERMINAL_HIGH_BYTE_COMMAND);
	outb(TERMINAL_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(TERMINAL_COMMAND_PORT, TERMINAL_LOW_BYTE_COMMAND);
	outb(TERMINAL_DATA_PORT, pos & 0x00FF);
}

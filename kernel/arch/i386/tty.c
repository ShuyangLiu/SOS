#include "vga.h"

// Function Declarations
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_scroll();

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
}

/*
#include <stdio.h>
*/

#include <kernel/tty.h>

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

// The welcome message
static const char * OPEN_MSG =
"Welcome to\n"
"             _____ _                                    _      \n"
"            / ____| |                                  ( )     \n"
"           | (___ | |__  _   _ _   _  __ _ _ __   __ _ |/___  \n"
"            \\___ \\| '_ \\| | | | | | |/ _` | '_ \\ / _` | / __| \n"
"            ____) | | | | |_| | |_| | (_| | | | | (_| | \\__ \\ \n"
"           |_____/|_| |_|\\__,_|\\__, |\\__,_|_| |_|\\__, | |___/ \n"
"             ____               __/ |   _   _     __/ |       \n"
"            / __ \\             |___/   | | (_)   |___/        \n"
"           | |  | |_ __   ___ _ __ __ _| |_ _ _ __   __ _     \n"
"           | |  | | '_ \\ / _ \\ '__/ _` | __| | '_ \\ / _` |    \n"
"           | |__| | |_) |  __/ | | (_| | |_| | | | | (_| |    \n"
"            \\____/| .__/ \\___|_|  \\__,_|\\__|_|_| |_|\\__, |    \n"
"                  | |                                __/ |    \n"
"                  |_|                               |___/     \n"
"                   _____           _                          \n"
"                  / ____|         | |                         \n"
"                 | (___  _   _ ___| |_ ___ _ __ ___           \n"
"                  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\          \n"
"                  ____) | |_| \\__ \\ ||  __/ | | | | |         \n"
"                 |_____/ \\__, |___/\\__\\___|_| |_| |_|         \n"
"                          __/ |                               \n"
"                         |___/                                \n"
"\n";


void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	/* Newline support is left as an exercise. */
	terminal_writestring(OPEN_MSG);
}
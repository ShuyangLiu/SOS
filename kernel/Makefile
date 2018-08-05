HOSTARCH=i386
SYSROOT=../sysroot
DESTDIR=$(SYSROOT)

CC:=i686-elf-gcc --sysroot=$(SYSROOT)
AS:=i686-elf-as
LD:=i686-elf-ld

CFLAGS:=-ffreestanding -O2 -g -Wall -Wextra
LDFLAGS?=
LIBS:=-nostdlib -lk -lgcc

PREFIX=/usr
EXEC_PREFIX=$(PREFIX)
BOOTDIR=/boot
INCLUDEDIR=$(PREFIX)/include

# Work around that the elf gcc target does not have a system include directory
# because it was compiled with `--without-headers` rather than `--with-sysroot`
CC+= -isystem=$(INCLUDEDIR)

# Add architecture specific flags
ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS+=$(KERNEL_ARCH_CFLAGS)
LDFLAGS+=$(KERNEL_ARCH_LDFLAGS)
LIBS+=$(KERNEL_ARCH_LIBS)

KERNEL_OBJS=$(KERNEL_ARCH_OBJS) kernel/kernel.o

OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .s

all: sos.kernel

# Link
sos.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot sos.kernel 

# Get crtbegin and crtend from the Compiler
$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

# Compile
.c.o:
	$(CC) -c $< -o $@ -std=gnu99 $(CFLAGS)

.s.o:
	$(AS) $< -o $@

# Clean up routine
clean:
	rm -f sos.kernel 
	rm -f *.o */*.o */*/*.o
	rm -f *.d */*.d */*/*.d

# copies the compiled kernel and headers into the dest directory
install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -Rf --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel:
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp -f sos.kernel $(DESTDIR)$(BOOTDIR)
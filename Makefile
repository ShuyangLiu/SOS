.PHONY: all config kernel clean create-img run

all: config kernel #libc

config:
	mkdir sysroot/
	mkdir -p isodir/boot/grub

kernel:
	cd kernel/ && make install-headers && make && make install-kernel

libc:
	cd libc/ && make install-headers && make

clean:
	rm -rf sysroot/
	cd kernel/ && make clean
	#cd libc/ && make clean

create-img:
	cp sysroot/boot/sos.kernel isodir/boot/sos.kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o sos.iso isodir


run: create-img
	qemu-system-i386 -cdrom sos.iso

.PHONY: all setup kernel libc clean create-img run

all: setup libc kernel

setup:
	mkdir sysroot/
	cd kernel/ && make install-headers
	cd libc/ && make install-headers
	
kernel:
	cd kernel/ && make && make install-kernel

libc:
	cd libc/ && make && make install-libs

clean:
	rm -f sos.iso
	rm -rf sysroot/
	rm -rf isodir/
	cd kernel/ && make clean
	cd libc/ && make clean

create-img:
	mkdir -p isodir/boot/grub
	cp sysroot/boot/sos.kernel isodir/boot/sos.kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o sos.iso isodir


run:
	qemu-system-i386 -s -S -cdrom sos.iso

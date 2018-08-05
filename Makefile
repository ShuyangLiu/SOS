.PHONY: all setup kernel libc clean create-img run

all: setup libc kernel

setup:
	mkdir sysroot/
	
kernel:
	cd kernel/ && make install-headers && make && make install-kernel

libc:
	cd libc/ && make install-headers && make && make install-libs

clean:
	rm -f sos.iso
	rm -rf sysroot/
	rm -rf isodir/
	cd kernel/ && make clean
	cd libc/ && make clean

create-img: all
	mkdir -p isodir/boot/grub
	cp sysroot/boot/sos.kernel isodir/boot/sos.kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o sos.iso isodir


run: create-img
	qemu-system-i386 -cdrom sos.iso

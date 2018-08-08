.PHONY: all setup kernel libc debug clean create-img run

all: setup libc kernel debug

setup:
	mkdir sysroot/
	cd kernel/ && make install-headers
	cd libc/ && make install-headers
	
kernel:
	cd kernel/ && make && make install-kernel

libc:
	cd libc/ && make && make install-libs

debug:
	objcopy --only-keep-debug kernel/sos.kernel sos.sym

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
	qemu-system-i386 -cdrom sos.iso

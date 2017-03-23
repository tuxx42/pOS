all:
	make -C arch

image:
	cp arch/i386/myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir

launch:
	qemu-system-i386 myos.iso -s

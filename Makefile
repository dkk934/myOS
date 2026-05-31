all:
	nasm -f elf32 boot/boot.asm -o boot.o
	nasm -f elf32 interrupts/isr.asm -o isr.o
	nasm -f elf32 cpu/gdt.asm -o gdtasm.o

	i686-elf-gcc -ffreestanding -c kernel/kernel.cpp -o kernel.o
	i686-elf-gcc -ffreestanding -c kernel/screen.cpp -o screen.o
	i686-elf-gcc -ffreestanding -c cpu/gdt.cpp -o gdt.o
	i686-elf-gcc -ffreestanding -c interrupts/idt.cpp -o idt.o
	i686-elf-gcc -ffreestanding -c kernel/keyboard.cpp -o keyboard.o

	i686-elf-ld -m elf_i386 -T linker.ld -o kernel.bin \
	boot.o isr.o kernel.o screen.o gdtasm.o idt.o keyboard.o gdt.o

	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	cp grub.cfg iso/boot/grub/

	grub-mkrescue -o myOS.iso iso

run:
	qemu-system-i386 -cdrom myOS.iso

clean:
	rm *.o kernel.bin
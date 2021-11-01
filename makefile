CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld

all: boot.bin full_kernel.bin zeroes.bin
	cat "bin/boot.bin" "bin/full_kernel.bin" "bin/zeroes.bin"  > "bin/OS.bin"
	


boot.bin: 
	nasm -f bin boot/boot.asm -o bin/boot.bin



full_kernel.bin: kernel.o kernel_entry.o idt_c.o idt_asm.o mem.o
	$(LD) -o "bin/full_kernel.bin" -Ttext 0x1000 "bin/kernel_entry.o" "bin/kernel.o" "bin/idt_c.o" "bin/idt_asm.o" "bin/mem.o" --oformat binary

kernel_entry.o:
	nasm -f elf kernel/kernel_entry.asm -o bin/kernel_entry.o

kernel.o:
	$(CC) -ffreestanding -m32 -g -c "kernel/kernel.c" -o "bin/kernel.o"



idt_asm.o:
	nasm -f elf cpu/idt/idt.asm -o bin/idt_asm.o

idt_c.o:
	$(CC) -ffreestanding -m32 -g -c "cpu/idt/idt.c" -o "bin/idt_c.o"



mem.o:
	$(CC) -ffreestanding -m32 -g -c "memory/mem.c" -o "bin/mem.o"



zeroes.bin:
	nasm "misc/zeroes.asm" -f bin -o "bin/zeroes.bin"



clean:
	rm bin/*



run: all
	qemu-system-x86_64 ./bin/OS.bin
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
CC_FLAGS = -ffreestanding -m32 -g -c -Ttext 0x8000
LD = /usr/local/i386elfgcc/bin/i386-elf-ld

all: boot.bin kernel.bin zeroes.bin
	cat "bin/boot.bin" "bin/kernel.bin" "bin/zeroes.bin"  > "bin/OS.bin"
	


boot.bin: 
	nasm -f bin boot/boot.asm -o bin/boot.bin



kernel.bin: kernel.o kernel_entry.o idt_c.o idt_asm.o mem.o isr_asm.o isr_c.o system.o IO.o
	$(LD) -T"link.ld"

kernel_entry.o:
	nasm -f elf kernel/kernel_entry.asm -o bin/kernel_entry.o

kernel.o:
	$(CC) $(CC_FLAGS) "kernel/kernel.c" -o "bin/kernel.o"



idt_asm.o:
	nasm -f elf cpu/idt/idt.asm -o bin/idt_asm.o

idt_c.o:
	$(CC) $(CC_FLAGS) "cpu/idt/idt.c" -o "bin/idt_c.o"



mem.o:
	$(CC) $(CC_FLAGS) "memory/mem.c" -o "bin/mem.o"


isr_asm.o:
	nasm -f elf cpu/isr/isr.asm -o bin/isr_asm.o

isr_c.o:
	$(CC) $(CC_FLAGS) "cpu/isr/isr.c" -o "bin/isr_c.o"


zeroes.bin:
	nasm "misc/zeroes.asm" -f bin -o "bin/zeroes.bin"


system.o:
	$(CC) $(CC_FLAGS) "system/system.c" -o "bin/system.o"


IO.o:
	$(CC) $(CC_FLAGS) "IO/IO.c" -o "bin/IO.o"


clean:
	rm bin/*



run: all
	qemu-system-x86_64 ./bin/OS.bin
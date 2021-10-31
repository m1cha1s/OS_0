all: boot.bin full_kernel.bin zeroes.bin
	cat "bin/boot.bin" "bin/full_kernel.bin" "bin/zeroes.bin"  > "bin/OS.bin"
	
full_kernel.bin: kernel.o kernel_entry.o
	/usr/local/i386elfgcc/bin/i386-elf-ld -o "bin/full_kernel.bin" -Ttext 0x1000 "bin/kernel_entry.o" "bin/kernel.o" --oformat binary

boot.bin: 
	nasm -f bin boot.asm -o bin/boot.bin

kernel_entry.o:
	nasm -f elf kernel_entry.asm -o bin/kernel_entry.o

kernel.o:
	/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -m32 -g -c "kernel.c" -o "bin/kernel.o"

zeroes.bin:
	nasm "zeroes.asm" -f bin -o "bin/zeroes.bin"

clean:
	rm bin/*
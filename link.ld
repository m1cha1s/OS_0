OUTPUT_FORMAT(binary)

ENTRY (_start)

INPUT
(
    bin/kernel.o
    bin/kernel_entry.o
    bin/idt_c.o
    bin/idt_asm.o
    bin/mem.o
    bin/isr_asm.o
    bin/isr_c.o
    bin/IO.o
    bin/system.o
)

OUTPUT
(
    bin/kernel.bin
)

SECTIONS
{
    . = 0x8000;

    .text : ALIGN(0x1000)
    {
        *(.text)
    }

    .data : ALIGN(0x1000)
    {
        *(.data)
    }

    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
    }

    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
    }
}
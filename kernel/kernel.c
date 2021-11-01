#include "../cpu/idt/idt.h"

extern void main()
{
    *(char*)0xb8000 = 'Q';

    idt_install();

    return;
}
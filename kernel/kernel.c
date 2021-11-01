#include "kernel.h"
#include "../system/system.h"
#include "../cpu/idt/idt.h"

extern void main()
{   
    puts("Welcome to OS_0\n\r->");

    idt_install();

    return;
}
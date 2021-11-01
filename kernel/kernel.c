#include "kernel.h"
#include "../system/system.h"
#include "../cpu/idt/idt.h"

extern void main()
{   
    puts("Welcome to OS_0");

    idt_install();

    return;
}
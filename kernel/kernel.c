#include "kernel.h"
#include "../system/system.h"
#include "../cpu/idt/idt.h"
#include "../CONSTANTS/TextModeColors.h"

extern void main()
{   
    puts("Welcome to OS_0\n\r->");

    idt_install();

    for(;;);
    return;
}
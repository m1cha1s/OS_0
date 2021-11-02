#include "system.h"
#include "TextModeColors.h"

extern void main()
{   
    puts("Welcome to OS_0\n\r->");

    idt_install();
    irq_install();

    timer_install();

    keyboard_install();

    __asm__ __volatile__ ("sti");

    for(;;);
    return;
}
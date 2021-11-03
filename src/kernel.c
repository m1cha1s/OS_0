#include "system.h"
#include "TextModeColors.h"

extern void main()
{  
    SetCursorPosition(PositionFromCords(0, 1)) ;
    puts("Welcome to OS_0!\n\r->");

    idt_install();
    irq_install();

    timer_install();

    keyboard_install();

    __asm__ __volatile__ ("sti");

    for(;;)
    {
        // draw_top_bar();

        // putsat("Welcome to OS\n->", 0, 0);

        // timer_wait(18);
    }
    return;
}
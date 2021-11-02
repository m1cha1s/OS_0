#include "system.h"
#include "TextModeColors.h"

extern void main()
{   
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

void draw_top_bar()
{
    draw_clock();
}

void draw_clock()
{
    struct time t = *get_time();
    // putsat(numToStr(t.houres, 10), 72, 0);
    // putsat(numToStr(t.minutes, 10), 75, 0);
    // putsat(numToStr(t.seconds, 10), 78, 0);

    // putsat(".", 74, 0);
    // putsat(".", 77, 0);
}
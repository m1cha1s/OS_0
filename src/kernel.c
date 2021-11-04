#include "system.h"
#include "TextModeColors.h"

extern unsigned char usable_memory_region_count;
extern struct memory_map_entry* usable_memory_regions[10];


extern void main()
{  
    idt_install();
    irq_install();

    timer_install();

    keyboard_install();

    find_usable_memory_regions();

    putsat(numToStr(usable_memory_region_count, 10), 0, 0);
    SetCursorPosition(PositionFromCords(0, 1)) ;
    puts("Welcome to OS_0!\n\n");

    for(int i = 0; i < usable_memory_region_count; i ++)
    {
        print_memory_map(usable_memory_regions[i]);
        puts("\n");
    }

    __asm__ __volatile__ ("sti");

    for(;;)
    {

    }
    return;
}
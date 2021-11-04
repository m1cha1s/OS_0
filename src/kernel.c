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

    heap_init(0x100000, 0x100000);

    void* test_memory_addr_0 = malloc(0x10);
    void* test_memory_addr_1 = malloc(0x10);
    void* test_memory_addr_2 = malloc(0x10);

    putsat(numToStr(usable_memory_region_count, 10), 0, 0);
    SetCursorPosition(PositionFromCords(0, 1)) ;
    puts("Welcome to OS_0!\n\n");

    puts(numToStr((unsigned long long)test_memory_addr_0, 10));
    puts("\n");
    puts(numToStr((unsigned long long)test_memory_addr_1, 10));
    puts("\n");
    puts(numToStr((unsigned long long)test_memory_addr_2, 10));
    puts("\n");

    __asm__ __volatile__ ("sti");

    for(;;)
    {

    }
    return;
}
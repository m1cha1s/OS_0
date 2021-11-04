#ifndef SYSTEM_H
#define SYSTEM_H

#define VGA_MEMORY (unsigned char*)0xb8000
#define VGA_WIDTH 80

#define memory_region_count (unsigned long)(*(unsigned char*)(0x7DFD))

unsigned short PositionFromCords(unsigned char x, unsigned char y);
void SetCursorPosition(unsigned short position);
void ClearScreen(unsigned char color);

void putch(char ch);
void putch_color(char ch, unsigned char color);
void puts(char *string);
void puts_color(char *string, unsigned char color);

void putsat(char *string, int x, int y);

const char* numToStr(unsigned long val, int base);

struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

void outb(unsigned short port, unsigned char val);
unsigned char inb(unsigned short port);

void* memset(void* dest, unsigned char val, int count);
void* kmalloc(int size);
void memcut(int size);
void memreset();
void memrec();
void memunrec();
int getFreeMem();
void initializeMem();

extern void idt_load();
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void irq_remap();
void irq_install();
void irq_handler(struct regs* r);

void isrs_install();
void fault_handler(struct regs *r);

struct time
{
    unsigned char seconds;
    unsigned char minutes;
    unsigned char houres;
};

struct time* get_time();
void timer_phase(int hz);
void timer_install();
void timer_wait(int ticks);

void keyboard_handler(struct regs *r);
void keyboard_install();

struct memory_map_entry
{
    unsigned long long base_address;
    unsigned long long region_lenght;
    unsigned long region_type;
    unsigned long extended_attributes;
};

void find_usable_memory_regions();
void print_memory_map(struct memory_map_entry *mme);

#endif
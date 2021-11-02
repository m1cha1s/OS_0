#ifndef SYSTEM_H
#define SYSTEM_H

unsigned short PositionFromCords(unsigned char x, unsigned char y);
void SetCursorPosition(unsigned short position);
void ClearScreen(unsigned char color);


void puts_color(char *string, unsigned char color);
void puts(char *string);

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

#endif
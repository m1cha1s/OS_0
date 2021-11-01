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


#endif
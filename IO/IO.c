#include "IO.h"

void outb(unsigned short port, unsigned char val)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN"(port), "a"(val));
}

unsigned char inb(unsigned short port)
{
    unsigned char returnValue;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(returnValue) : "dN"(port));
    return returnValue;
}
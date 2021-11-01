#include "system.h"
#include "../IO/IO.h"

#define VGA_MEMORY (unsigned char*)0xb8000
#define VGA_WIDTH 80

unsigned short CursorPosition;

void SetCursorPosition(unsigned short position)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));

    CursorPosition = position;
}

unsigned short PositionFromCords(unsigned char x, unsigned char y)
{
    return y * VGA_WIDTH + x;
}

void puts(char *string)
{
    char* charPtr = string;
    unsigned short index = CursorPosition;
    while(*charPtr != 0)
    {
        *(VGA_MEMORY + index * 2) = *charPtr;
        index++;
        charPtr++;
    }
    SetCursorPosition(index);
}

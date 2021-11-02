#include "system.h"
#include "TextModeColors.h"
#include "typedefs.h"

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

void ClearScreen(uint8 color)
{
    for(uint8* i = VGA_MEMORY; i < VGA_MEMORY+4000; i+=2)
    {
        *i = 0;
        *(i+1) = color;
    }
    SetCursorPosition(0);
}

void puts_color(char *string, unsigned char color)
{
    char* charPtr = string;
    unsigned short index = CursorPosition;
    while(*charPtr != 0)
    {
        switch (*charPtr)
        {
        case '\n':
            index += VGA_WIDTH;
            break;
        
        case '\r':
            index -= index % VGA_WIDTH;
            break;

        default:
            *(VGA_MEMORY + index * 2) = *charPtr;
            *(VGA_MEMORY + index * 2 + 1) = color;
            index++;
            break;
        }
        charPtr++;
    }
    SetCursorPosition(index);
}

void puts(char *string)
{
    char* charPtr = string;
    unsigned short index = CursorPosition;
    while(*charPtr != 0)
    {
        switch (*charPtr)
        {
        case '\n':
            index += VGA_WIDTH;
            break;
        
        case '\r':
            index -= index % VGA_WIDTH;
            break;

        default:
            *(VGA_MEMORY + index * 2) = *charPtr;
            *(VGA_MEMORY + index * 2 + 1) = DEFAULT_COLOR;
            index++;
            break;
        }
        charPtr++;
    }
    SetCursorPosition(index);
}

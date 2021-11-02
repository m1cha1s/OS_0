#include "system.h"
#include "TextModeColors.h"
#include "typedefs.h"

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
            index -= index % VGA_WIDTH;
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

void putch(char ch)
{
    if(ch == '\n')
    {
        CursorPosition += VGA_WIDTH;
        CursorPosition -= CursorPosition % VGA_WIDTH;
    } 
    else 
    {
        *(VGA_MEMORY + CursorPosition * 2) = ch;
        *(VGA_MEMORY + CursorPosition * 2 + 1) = DEFAULT_COLOR;
        CursorPosition++;
    }
    SetCursorPosition(CursorPosition);
}

void putch_color(char ch, unsigned char color)
{
    *(VGA_MEMORY + CursorPosition * 2) = ch;
    *(VGA_MEMORY + CursorPosition * 2 + 1) = color;
    CursorPosition++;
    SetCursorPosition(CursorPosition);
}

int itoa(int num, unsigned char* str, int len, int base)
{
	int sum = num;
	int i = 0;
	int digit;
	if (len == 0)
		return -1;
	do
	{
		digit = sum % base;
		if (digit < 0xA)
			str[i++] = '0' + digit;
		else
			str[i++] = 'A' + digit - 0xA;
		sum /= base;
	}while (sum && (i < (len - 1)));
	if (i == (len - 1) && sum)
		return -1;
	str[i] = '\0';
	return 0;
}
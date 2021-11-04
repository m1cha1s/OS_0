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

void putsat(char *string, int x, int y)
{
    char* charPtr = string;
    unsigned short index = PositionFromCords(x, y);
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
}

char integerToStringOut[128];
const char* numToStr(unsigned long val, int base)
{
    unsigned char size = 0;
    unsigned long sizeTester = val;
    while(sizeTester / base > 0)
    {
        sizeTester /= base;
        size++;
    }

    unsigned char index = 0;
    while(val / base > 0)
    {
        unsigned char rem = val % base;
        val /= base;
        integerToStringOut[size - index] = rem + 48;
        index++;
    }
    unsigned char rem = val % base;
    integerToStringOut[size - index] = rem + 48;
    integerToStringOut[size+1] = 0;
    return integerToStringOut;
}

struct memory_map_entry* usable_memory_regions[10];
unsigned char usable_memory_region_count = 0;


void print_memory_map(struct memory_map_entry *mme)
{
    puts("Memory base: ");
    puts(numToStr(mme->base_address, 10));
    puts("\n");
    puts("Region lenght: ");
    puts(numToStr(mme->region_lenght, 10));
    puts("\n");
    puts("Memory type: ");
    puts(numToStr(mme->region_type, 10));
    puts("\n");
    puts("Memory attributes: ");
    puts(numToStr(mme->extended_attributes, 10));
    puts("\n");
}

void find_usable_memory_regions()
{
    unsigned char usable_region_index;
    for(unsigned char i = 0; i < memory_region_count; i ++)
    {
        struct memory_map_entry* mme = (struct memory_map_entry*)0x5000;
        mme+=i;
        if(mme->region_type == 1)
        {
            usable_memory_regions[usable_region_index] = mme;
            usable_region_index++;
            usable_memory_region_count++;
        }
    }
}
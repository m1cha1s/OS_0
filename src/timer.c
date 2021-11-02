#include "system.h"

int timer_ticks = 0;

int time_seconds = 0;
int time_minutes = 0;
int time_houres  = 0;

void timer_phase(int hz)
{
    int divisor = 1193180; //Hz
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

void timer_handler(struct regs *r)
{
    timer_ticks++;
    if(timer_ticks % 18 == 0)
    {
        if(time_seconds % 60 == 0)
        {
            time_seconds = 0;
            if(time_minutes % 60 == 0)
            {
                time_minutes = 0;
                if(time_houres % 24 == 0)
                {
                    time_houres = 0;
                }
                time_houres++;
            }
            time_minutes++;
        }
        time_seconds++;

        // unsigned char buf[10];
        // unsigned char *bufPtr = buf;

        // bufPtr++;
        // // itoa(time_houres, buf, 2, 10);
        // bufPtr+=3;
        // // itoa(time_minutes, bufPtr, 2, 10);
        // bufPtr+=3;
        // itoa(time_seconds, bufPtr, 4, 10);

        // buf[2] = '/';
        // buf[5] = '/';

        // for(int i = 0; i < 8; i++)
        //     *(VGA_MEMORY + PositionFromCords(72+i,0) * 2) = buf[i];
    }
}

void timer_install()
{
    irq_install_handler(0, timer_handler);
}

void timer_wait(int ticks)
{
    unsigned long eticks;
    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}
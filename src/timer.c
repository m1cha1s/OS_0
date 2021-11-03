#include "system.h"

int timer_ticks = 0;

struct time t;

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
        if(t.seconds % 60 == 0 && t.seconds != 0)
        {
            t.seconds = 0;
            if(t.minutes % 60 == 0 && t.minutes != 0)
            {
                t.minutes = 0;
                if(t.houres % 24 == 0 && t.houres != 0)
                {
                    t.houres = 0;
                }
                t.houres++;
            }
            t.minutes++;
        }
        t.seconds++;

        putsat(numToStr(t.houres, 10), 35, 0);
        putsat("/", 37, 0);
        putsat(numToStr(t.minutes, 10), 38, 0);
        putsat("/", 40, 0);
        putsat(numToStr(t.seconds, 10), 41, 0);
    }
}

struct time* get_time()
{
    return &t;
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
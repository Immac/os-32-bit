#include "print-string.h"

void Osapi_PrintString(struct regs *r)
{
    puts((char *)r->ebx);
}

void Osapi_PrintInt(struct regs *r)
{
    kprintf("%d",(char *)r->ebx);
}

void Osapi_PrintPointer(struct regs *r)
{
    kprintf("%p",(char *)r->ebx);
}

#include "print-string.h"

void Osapi_PrintString(regs_t *r)
{
    puts((char *)r->ebx);
}

void Osapi_PrintInt(regs_t *r)
{
    kprintf("%d",(char *)r->ebx);
}

void Osapi_PrintPointer(regs_t *r)
{
    kprintf("%p",(char *)r->ebx);
}

#include "print-string.h"

void Osapi_PrintString(struct regs *r)
{
    puts((char *)r->ebx);
}

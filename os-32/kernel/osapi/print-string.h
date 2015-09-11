#ifndef OSAPI_PRINT_STRING_H
#define OSAPI_PRINT_STRING_H
#include "system.h"
#include "screen.h"

void Osapi_PrintString(struct regs *r);
void Osapi_PrintInt(struct regs *r);
void Osapi_PrintPointer(struct regs *r);
#endif // OSAPI_PRINT_STRING_H

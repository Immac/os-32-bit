#ifndef OSAPI_PRINT_STRING_H
#define OSAPI_PRINT_STRING_H
#include "system.h"
#include "screen.h"

void Osapi_PrintString(regs_t *r);
void Osapi_PrintInt(regs_t *r);
void Osapi_PrintPointer(regs_t *r);

#endif // OSAPI_PRINT_STRING_H

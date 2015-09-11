#include "syscall-handler.h"


void (*handlers[OSAPI_HANDLER_COUNT])();




void InitSyscallInterfaceHandlers()
{
    handlers[PrintString] = Osapi_PrintString;
    handlers[ReadString] = Osapi_ReadString;
    handlers[PrintInt] = Osapi_PrintInt;
    handlers[PrintPointer] = Osapi_PrintPointer;
}

void Interrupt0x80Handler(struct regs *r)
{
    unsigned int syscall_code = r->eax;
    handlers[syscall_code](r);
}

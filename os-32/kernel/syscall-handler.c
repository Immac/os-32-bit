#include "syscall-handler.h"


void (*handlers[SyscallCount])();

void InitSyscallInterfaceHandlers()
{
    handlers[PrintString] = Osapi_PrintString;
    handlers[ReadString] = Osapi_ReadString;
    handlers[PrintInt] = Osapi_PrintInt;
    handlers[PrintPointer] = Osapi_PrintPointer;
    handlers[Malloc] = Osapi_Malloc;
    handlers[Free] = Osapi_Free;
    handlers[ListDirectory] = Osapi_ListDirectory;
}

void Interrupt0x80Handler(struct regs *r)
{
    unsigned int syscall_code = r->eax;
    handlers[syscall_code](r);
}

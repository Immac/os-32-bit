#include "syscall-handler.h"


void (*handlers[OSAPI_HANDLER_COUNT])();


void InitSyscallInterfaceHandlers()
{
    handlers[0] = Osapi_PrintString;
    handlers[1] = Osapi_ReadString;

}

void Interrupt0x80Handler(struct regs *r)
{
    unsigned int syscall_code = r->eax;
    handlers[syscall_code](r);
}

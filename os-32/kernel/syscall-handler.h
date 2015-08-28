#ifndef SYSCALL_HANDLER_H
#define SYSCALL_HANDLER_H
#include "system.h"
#include "osapi/print-string.h"
#include "osapi/read-string.h"
#define OSAPI_HANDLER_COUNT 2
void Interrupt0x80Handler(struct regs *r);
void InitSyscallInterfaceHandlers(void);
#endif // SYSCALL_HANDLER_H

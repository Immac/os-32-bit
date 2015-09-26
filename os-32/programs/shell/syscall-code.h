#ifndef SYSCALL_CODE_H
#define SYSCALL_CODE_H

#define OSAPI_HANDLER_COUNT 4

typedef enum SyscallCode
{
    PrintString,
    ReadString,
    PrintInt,
    PrintPointer,
    Malloc,
    Free,
    ListDirectory,
    SyscallCount
} SyscallCode_type;


#endif // SYSCALL_CODE_H

#include "syscall-interface.h"

void Mikos_PrintString(char* string)
{
    int syscall_code = PrintString;
    asm ("int $128"
         :
         : "a"(syscall_code), "b"(string)
         :
         );
}

void Mikos_ReadString(char* outBuffer, int bufferSize)
{
    int syscall_code = ReadString;
    asm ("int $128"
         :
         : "a"(syscall_code), "b"(outBuffer), "c"(bufferSize)
         :
         );
}

void Mikos_PrintInt(int integer)
{
    int syscall_code = PrintInt;
    asm ("int $128"
         :
         : "a"(syscall_code), "b"(integer)
         :
         );
}

void Mikos_PrintPointer(void *pointer)
{
    int syscall_code = PrintPointer;
    asm ("int $128"
         :
         : "a"(syscall_code), "b"(pointer)
         :
         );
}
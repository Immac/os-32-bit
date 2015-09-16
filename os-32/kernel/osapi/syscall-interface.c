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

void *Mikos_Malloc(unsigned int nBytes)
{
    void *output;
    int syscall_code = Malloc;
    asm ("int $128"
         : "=r"(output)
         : "a"(syscall_code), "b"(nBytes)
         :
         );
    return output;
}

void Mikos_Free(void *target)
{
    int syscall_code = Free;
    asm ("int $128"
         :
         : "a"(syscall_code), "b"(target)
         :
         );
}

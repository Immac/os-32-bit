#include "syscall-interface.h"

void Mikos_PrintString(char* string)
{
    int syscall_code = 0;
    asm ("int $128"
         :
         : "a"(syscall_code), "b"(string)
         :
         );
}

void Mikos_ReadString(char* outBuffer, int bufferSize)
{
    int syscall_code = 1;
    asm ("int $128"
         :
         : "a"(syscall_code), "b"(outBuffer), "c"(bufferSize)
         :
         );
}

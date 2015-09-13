#ifndef SYSCALL_INTERFACE_H
#define SYSCALL_INTERFACE_H
#include "syscall-code.h"
void Mikos_PrintString(char* string);
void Mikos_ReadString(char* outBuffer, int bufferSize);
void Mikos_PrintInt(int integer);
void Mikos_PrintPointer(void *pointer);
void *Mikos_Malloc(unsigned int nBytes);
void Mikos_Free(void *target);
#endif // SYSCALL_INTERFACE_H

#include "syscall-interface.h"

int main(char *startAddress)
{
    int size = 50;
    char buffer[size];
    Mikos_ReadString(buffer,size);
    char *str = "\nThis String is on the user Program!\n";
    unsigned int realStringAddress = (unsigned int)startAddress + (unsigned int)str;
    Mikos_PrintString((char*)realStringAddress);
    Mikos_PrintString(buffer);
	while(1);
}

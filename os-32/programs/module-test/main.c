#include "syscall-interface.h"

int main(char *startAddress)
{
    int size = 50;
    char buffer[size];
    Mikos_ReadString(buffer,size);
    char *buff = "algo";
    unsigned int in = (unsigned int)startAddress + (unsigned int)buff;
    Mikos_PrintString((char*)in);
	while(1);
}

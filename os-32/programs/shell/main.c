#include "syscall-interface.h"
#include "shell.h"

int main(char *dataStartAddress)
{
    ShellLoop(dataStartAddress);
	while(1);
}

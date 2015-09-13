#include "syscall-interface.h"
#include "shell.h"

int main(char *dataSegmentAddress)
{
    Shell_Construct(dataSegmentAddress);
    Shell_MainLoop();
	while(1);
}

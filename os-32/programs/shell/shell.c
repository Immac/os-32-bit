#include "shell.h"
#include "lib/string-util/string-util.h"
#include "syscall-interface.h"
int ShellLoop(char *dataStart)
{
    char *exit_command = "exit";
    char user_input[80] = {0};
    while(MikosLib_Util_StringCompare(user_input,exit_command,80) != 0 );
    {
        Mikos_PrintString( (char*)((unsigned int)dataStart + (unsigned int)exit_command));
    }
}

#include "shell.h"

char *Shell_RepairDataSegmentOffset(char *string);
int GetCommand(char *userInput);
#define InputSize 80 // static const int InputSize = 80;

typedef enum Command
{
    Exit,
    CommandCount
} Command_type;

typedef enum ExitCode
{
    Normal,
    Error,
    UserRequest,
    InvalidCommand,
    Continue
} ExitCode_type;

typedef MikosLib_StoI_MapEntry_type Shell_MapEntry;
typedef MikosLib_StoI_Map_type Shell_Map;


int ShellConstructed = 0;
char *DataSegmentAddress;
char *Commands[CommandCount];
Shell_MapEntry CommandEntries[CommandCount];
Shell_Map CommandMap;

ExitCode_type (*Actions[CommandCount])();
ExitCode_type Shell_UserRequest(void);
ExitCode_type PerformAction(char *user_input);

int Shell_Construct(char *dataSegmentAddress)
{
    DataSegmentAddress = dataSegmentAddress;
    Commands[Exit] = Shell_RepairDataSegmentOffset("exit");
    Actions[Exit] = Shell_UserRequest;

    for(int i = 0; i < CommandCount; i++)
    {
        CommandEntries[i].key = Commands[i];
        CommandEntries[i].value = i;
    }
    MikosLib_StoI_Map_Construct(&CommandMap,CommandEntries);

}

int Shell_MainLoop()
{
    char user_input[InputSize] = {0};
    int exit_code = Continue;
    while(exit_code == Continue)
    {
        Mikos_ReadString(user_input,InputSize);
        Mikos_PrintString(user_input);
        exit_code = PerformAction(user_input);
        MikosLib_Util_ArrayClear(user_input,InputSize);
    }
}

ExitCode_type PerformAction(char *user_input)
{

    int command = GetCommand(user_input);
    if (command != -1)
    {
        return Actions[command](user_input);
    }
    Mikos_PrintString(user_input);
    Mikos_PrintString(Shell_RepairDataSegmentOffset(" is not a valid command!\n"));
    return Continue;
}

ExitCode_type Shell_UserRequest()
{
    return UserRequest;
}

int GetCommand(char *userInput)
{
    return MikosLib_StoI_Map_EvaluateKey(&CommandMap,userInput,InputSize);
}

char *Shell_RepairDataSegmentOffset(char *string)
{
    return (char*)((unsigned int)DataSegmentAddress + (unsigned int)string);
}

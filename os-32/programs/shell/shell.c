#include "shell.h"

char *Shell_RepairDataSegmentOffset(char *string);
int GetCommand(char *userInput);
#define InputSize 80 // static const int InputSize = 80;

typedef enum Command
{
    Exit,
    Test,
    CommandCount
} Command_type;

typedef struct
{
    char *WelcomeMessage1;
    char *NewLine;
    char *InvalidCommand;
    char *MikosShell;
} Vocabulary_type;
Vocabulary_type Vocabulary;

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

ExitCode_type (*Actions[CommandCount])(char *userInput);
ExitCode_type Shell_UserRequest(char *userInput);
ExitCode_type Shell_Test(char *userInput);

ExitCode_type PerformAction(char *userInput);
/**
*   This is the constructor for the Shell, should only be called once.
*   \param dataSegmentAddress This parameter is used to offset anything in the .data
*   that does not get offset because of how the program is loaded into memory
*/
int Shell_Construct(char *dataSegmentAddress)
{
    DataSegmentAddress = dataSegmentAddress;
    Commands[Exit] = Shell_RepairDataSegmentOffset("exit");
    Commands[Test] = Shell_RepairDataSegmentOffset("test");

    Vocabulary.WelcomeMessage1 = Shell_RepairDataSegmentOffset("Welcome to MikOS-32!\n");
    Vocabulary.NewLine = Shell_RepairDataSegmentOffset("\n");
    Vocabulary.InvalidCommand = Shell_RepairDataSegmentOffset("The \"Command\" entered was not found, please try again! The command was: ");
    Vocabulary.MikosShell = Shell_RepairDataSegmentOffset("\nMikOS ~>");

    Actions[Exit] = (void *)Shell_RepairDataSegmentOffset((char*)Shell_UserRequest);
    Actions[Test] = (void *)Shell_RepairDataSegmentOffset((char*)Shell_Test);


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
    Mikos_PrintString(Vocabulary.WelcomeMessage1);
    while(exit_code == Continue)
    {
        Mikos_PrintString(Vocabulary.MikosShell);
        Mikos_ReadString(user_input,InputSize);
        Mikos_PrintString(Vocabulary.NewLine);
        exit_code = PerformAction(user_input);
        MikosLib_Util_ArrayClear(user_input,InputSize);
    }

    return 0;
}

ExitCode_type PerformAction(char *user_input)
{
    Vocabulary_type vocab;
    int command = GetCommand(user_input);
    if (command != -1)
    {
        return Actions[command](user_input);
    }
    Mikos_PrintString(Vocabulary.InvalidCommand);
    Mikos_PrintString(user_input);
    return Continue;
}

ExitCode_type Shell_UserRequest(char *userInput)
{
    return UserRequest;
}

int GetCommand(char *userInput)
{
    char *command = MikosLib_Util_StringSubstring(userInput,' ',InputSize,0);
    int output = MikosLib_StoI_Map_EvaluateKey(&CommandMap,command,InputSize);

    Mikos_Free(command);
    return output;
}

char *Shell_RepairDataSegmentOffset(char *string)
{
    return (char*)((unsigned int)DataSegmentAddress + (unsigned int)string);
}

ExitCode_type Shell_Test(char *userInput)
{
    char *command = MikosLib_Util_StringSubstring(userInput,' ',InputSize,0);
    int command_size = MikosLib_StringLength(command);
    char *arg = MikosLib_Util_StringSubstring(userInput,' ',InputSize - command_size,command_size + 1);

    Mikos_PrintString(Shell_RepairDataSegmentOffset("\nThe argument is: "));
    Mikos_PrintString(arg);
    Mikos_PrintString(Vocabulary.NewLine);

    Mikos_Free(command);
    Mikos_Free(arg);

    return Continue;
}

/**
* Free the \return argument once it's no longer needed.
*/
char *GetArgument(char *userInput,int argumentNumber)
{
    if(argumentNumber == 0)
    {
        return 0;
    }
    char *command = MikosLib_Util_StringSubstring(userInput,' ',InputSize,0);
    int command_size = MikosLib_StringLength(command);
    char* arg = command;
    int arg_offset = command_size;
    for(int i =0; i < argumentNumber; i++)
    {
        arg = MikosLib_Util_StringSubstring(userInput,' ',InputSize - arg_offset,arg_offset + 1);
        arg_offset += MikosLib_StringLength(arg);
    }

    Mikos_Free(command);
    return arg;
}
